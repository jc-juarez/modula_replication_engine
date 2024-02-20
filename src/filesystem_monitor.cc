// *************************************
// Modula Replication Engine
// Core
// 'filesystem_monitor.cc'
// Author: jcjuarez
// *************************************

#include "logger.hh"
#include "modula.hh"
#include "directory.hh"
#include "filesystem_monitor.hh"

#include <tuple>
#include <thread>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <filesystem>
#include <sys/epoll.h>

namespace modula
{

filesystem_event::filesystem_event()
    : m_replication_action(replication_action::invalid),
      m_name("")
{}

filesystem_monitor::filesystem_monitor(
    const file_descriptor p_termination_signals_handle,
    std::shared_ptr<replication_manager> p_replication_manager,
    status_code* p_status) :
    m_termination_signals_handle(p_termination_signals_handle),
    m_replication_manager(p_replication_manager)
{
    //
    // Start the inotify instance in non-blocking mode.
    //
    m_inotify_handle = inotify_init1(IN_NONBLOCK);

    if (!utilities::is_file_descriptor_valid(m_inotify_handle))
    {
        *p_status = status::inotify_startup_failed;

        logger::log(log_level::critical, std::format("Inotify instance startup failed. Status={:#X}.",
            *p_status));

        return;
    }

    //
    // Start all watch descriptors for the specified directories.
    //
    for (std::pair<const std::string, replication_engine>& replication_engine_entry : m_replication_manager->get_replication_engines())
    {
        const std::string& replication_engine_name = replication_engine_entry.first;

        if (!std::filesystem::exists(replication_engine_name))
        {
            *p_status = status::directory_does_not_exist;

            logger::log(log_level::critical, std::format("Directory '{}' does not exist. Status={:#X}.",
                replication_engine_name.c_str(),
                *p_status));

            return;
        }

        file_descriptor directory_watch_descriptor = inotify_add_watch(
            m_inotify_handle,
            replication_engine_name.c_str(),
            IN_CREATE | IN_MODIFY | IN_DELETE);
    
        if (!utilities::is_file_descriptor_valid(directory_watch_descriptor))
        {
            *p_status = status::directory_watch_descriptor_creation_failed;

            logger::log(log_level::critical, std::format("Watch descriptor for directory '{}' could not be created. Status={:#X}.",
                replication_engine_name.c_str(),
                *p_status));

            return;
        }

        m_watch_descriptors.emplace_back(directory_watch_descriptor);
    }

    //
    // Create an epoll instance used for monitoring the kernel inotify
    // filesystem events along with external system termination signals.
    //
    m_epoll_handle = epoll_create1(0);

    if (!utilities::is_file_descriptor_valid(m_epoll_handle))
    {
        *p_status = status::epoll_startup_failed;

        logger::log(log_level::critical, std::format("Epoll instance startup failed. Status={:#X}.",
            *p_status));

        return;
    }

    //
    // Setup the epoll events for system termination and filesystem monitoring.
    //
    epoll_event event;
    event.events = EPOLLIN;

    event.data.fd = m_termination_signals_handle;

    if (utilities::system_call_failed(epoll_ctl(
        m_epoll_handle,
        EPOLL_CTL_ADD,
        m_termination_signals_handle,
        &event)))
    {
        *p_status = status::epoll_startup_failed;

        logger::log(log_level::critical, std::format("Failed to attach the termination signals handle to the epoll instance. {} (errno {}), Status={:#X}.",
            std::strerror(errno),
            errno,
            *p_status));

        return;
    }

    event.data.fd = m_inotify_handle;

    if (utilities::system_call_failed(epoll_ctl(
        m_epoll_handle,
        EPOLL_CTL_ADD,
        m_inotify_handle,
        &event)))
    {
        *p_status = status::epoll_startup_failed;

        logger::log(log_level::critical, std::format("Failed to attach the inotify handle to the epoll instance. {} (errno {}), Status={:#X}.",
            std::strerror(errno),
            errno,
            *p_status));

        return;
    }

    //
    // Initialize thread pool for handling dispatcher calls to replication engines.
    //
    m_dispatcher_thread_pool = std::make_unique<thread_pool>(
        p_status,
        c_dispatcher_thread_pool_size);

    if (status::failed(*p_status))
    {
        logger::log(log_level::critical, std::format("Replication task dispatcher thread pool could not be started. Status={:#X}.",
            *p_status));
    }
}

filesystem_monitor::~filesystem_monitor()
{
    for (const file_descriptor& watch_descriptor : m_watch_descriptors)
    {
        inotify_rm_watch(m_inotify_handle, watch_descriptor);
    }
    
    close(m_termination_signals_handle);
    close(m_inotify_handle);
    close(m_epoll_handle);
}

void
filesystem_monitor::start_kernel_events_offloader()
{
    forever
    {
        //
        // Offload the filesystem inotify events from the internal
        // kernel queue onto a user-space managed dynamic size queue.
        //
        epoll_event epoll_events[c_epoll_event_buffer_size];

        uint16 number_epoll_events = epoll_wait(
            m_epoll_handle,
            epoll_events,
            c_epoll_event_buffer_size,
            -1 /* No timeout for the epoll events. */);

        for (uint16 epoll_event_index = 0; epoll_event_index < number_epoll_events; ++epoll_event_index)
        {
            epoll_event event = epoll_events[epoll_event_index];

            if (event.data.fd == m_termination_signals_handle)
            {
                //
                // The system has been instructed to be terminated.
                //
                modula::invoke_system_termination_handler();

                return;
            }

            //
            // Read event buffer of the inotify instance.
            //
            static byte read_event_buffer[c_read_event_buffer_size] __attribute__ ((aligned(__alignof__(inotify_event))));

            uint32 number_bytes_read = read(
                m_inotify_handle,
                read_event_buffer,
                c_read_event_buffer_size);

            if (number_bytes_read <= 0)
            {
                //
                // Unknown behavior.
                //
                continue;
            }

            uint32 number_bytes_processed = 0;
            uint32 number_filesystem_events_processed = 0;

            while (number_bytes_processed < number_bytes_read)
            {
                inotify_event* inotify_filesystem_event = reinterpret_cast<inotify_event*>(&read_event_buffer[number_bytes_processed]);

                if (inotify_filesystem_event->len)
                {
                    filesystem_event event;

                    event.m_name = inotify_filesystem_event->name;

                    if (!event.m_name.empty())
                    {
                        //
                        // Logging is handled by the replication tasks dispatcher.
                        //
                        switch (inotify_filesystem_event->mask)
                        {
                            case IN_CREATE:
                            {
                                event.m_replication_action = replication_action::create;

                                break;
                            }
                            case IN_MODIFY:
                            {
                                event.m_replication_action = replication_action::update;

                                break;
                            }
                            case IN_DELETE:
                            {
                                event.m_replication_action = replication_action::remove;

                                break;
                            }
                        }

                        if (event.m_replication_action != replication_action::invalid)
                        {
                            //
                            // Append recorded filesystem event to the events queue.
                            //
                            {
                                std::scoped_lock<std::mutex> lock(m_filesystem_events_queue_lock);

                                m_filesystem_events_queue.push(event);
                            }
                        }
                    }
                }
                
                number_bytes_processed += sizeof(inotify_event) + inotify_filesystem_event->len;
            }
        }
    }
}

} // namespace modula.
