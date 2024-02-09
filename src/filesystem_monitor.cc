// *************************************
// Modula Replication Engine
// Core
// 'filesystem_monitor.cc'
// Author: jcjuarez
// *************************************

#include "logger.hh"
#include "directory.hh"
#include "filesystem_monitor.hh"

#include <thread>
#include <cstdlib>
#include <unistd.h>
#include <filesystem>
#include <sys/inotify.h>

namespace modula
{

filesystem_monitor::filesystem_monitor(
    std::shared_ptr<replication_manager> p_replication_manager,
    status_code& p_status) :
    m_replication_manager(p_replication_manager)
{
    m_inotify_handle = inotify_init();

    if (!is_file_descriptor_valid(m_inotify_handle))
    {
        p_status = status::inotify_startup_failed;

        logger::log(log_level::critical, std::format("Inotify instance startup failed. Status={:#X}.",
            p_status));

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
            p_status = status::directory_does_not_exist;

            logger::log(log_level::critical, std::format("Directory '{}' does not exist. Status={:#X}.",
                replication_engine_name.c_str(),
                p_status));

            return;
        }

        file_descriptor directory_watch_descriptor = inotify_add_watch(
            m_inotify_handle,
            replication_engine_name.c_str(),
            IN_CREATE | IN_MODIFY | IN_DELETE);
    
        if (!is_file_descriptor_valid(directory_watch_descriptor))
        {
            p_status = status::directory_watch_descriptor_creation_failed;

            logger::log(log_level::critical, std::format("Watch descriptor for directory '{}' could not be created. Status={:#X}.",
                replication_engine_name.c_str(),
                p_status));

            return;
        }

        m_watch_descriptors.emplace_back(directory_watch_descriptor);
    }
}

filesystem_monitor::~filesystem_monitor()
{
    for (const file_descriptor& watch_descriptor : m_watch_descriptors)
    {
        inotify_rm_watch(m_inotify_handle, watch_descriptor);
    }
    
    close(m_inotify_handle);
}

status_code
filesystem_monitor::start_replication_task_dispatcher()
{
    status_code status = status::success;

    //
    // Launch the filesystem monitor thread to handle filesystem events.
    //
    std::thread replication_task_dispatcher_thread(
        &filesystem_monitor::replication_task_dispatcher,
        this);

    if (!replication_task_dispatcher_thread.joinable())
    {
        status = status::launch_thread_failed;
        
        logger::log(log_level::critical, std::format("Replication task dispatcher thread could not be started. Status={:#X}.",
            status));

        return status;
    }

    replication_task_dispatcher_thread.detach();

    //
    // Initialize thread pool for handling dispatcher calls to replication engines.
    //
    m_dispatcher_thread_pool = std::make_unique<thread_pool>(
        c_dispatcher_thread_pool_size);

    return status;
}

void
filesystem_monitor::replication_task_dispatcher()
{
    forever
    {
        uint32 number_bytes_read = read(
            m_inotify_handle,
            m_read_event_buffer,
            c_read_event_buffer_size);

        if (number_bytes_read <= 0)
        {
            continue;
        }

        uint32 number_filesystem_events_processed = 0;
        uint32 number_bytes_processed = 0;

        while (number_bytes_processed < number_bytes_read)
        {
            struct inotify_event* filesystem_event = reinterpret_cast<inotify_event*>(&m_read_event_buffer[number_bytes_processed]);

            if (filesystem_event->len)
            {
                std::string filesystem_event_name(filesystem_event->name);

                switch (filesystem_event->mask)
                {
                    case IN_CREATE:
                    {
                        logger::log(log_level::info, std::format("File created: '{}'.",
                            filesystem_event_name));

                        break;
                    }
                    case IN_MODIFY:
                    {
                        logger::log(log_level::info, std::format("File modified: '{}'.",
                            filesystem_event_name));

                        break;
                    }
                    case IN_DELETE:
                    {
                        logger::log(log_level::info, std::format("File deleted: '{}'.",
                            filesystem_event_name));

                        break;
                    }
                    default:
                    {
                        logger::log(log_level::warning, "Unkwown event type.");

                        break;
                    }
                }
            }
            
            number_bytes_processed += sizeof(struct inotify_event) + filesystem_event->len;
        }
    }
}

} // namespace modula.
