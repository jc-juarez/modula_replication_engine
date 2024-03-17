// *************************************
// Modula Replication Engine
// Core
// 'replication_manager.cc'
// Author: jcjuarez
// *************************************

#include "logger.hh"
#include "replication_manager.hh"

namespace modula
{

replication_manager::replication_manager(
    const std::string& p_initial_configuration_file,
    status_code* p_status)
{
    *p_status = parse_initial_configuration_file_into_memory(
        p_initial_configuration_file);

    if (status::failed(*p_status))
    {
        logger::log(log_level::critical, std::format("Initial configuration file '{}' parsing failed. Status={:#X}.",
            p_initial_configuration_file.c_str(),
            *p_status));

        return;
    }

    // NOTE: This has to be taken out from here and moved to the initialization segment after the initialization of the filesystem monitor.
    //
    // Initiate an initial full sync on all directories on startup.
    //
    *p_status = execute_full_sync();

    if (status::failed(*p_status))
    {
        logger::log(log_level::critical, std::format("Initial full sync on startup failed. Status={:#X}.",
            *p_status));

        return;
    }

    //
    // Attach the replication tasks thread pool after the replication
    // engines have been correctly parsed and booted for the system.
    //
    m_replication_tasks_thread_pool = std::make_shared<thread_pool>(
        p_status,
        c_replication_tasks_thread_pool_size);

    if (status::failed(*p_status))
    {
        logger::log(log_level::critical, std::format("Replication tasks shared thread pool could not be started. Status={:#X}.",
            *p_status));

        return;
    }

    for (replication_engine& replication_engine : m_replication_engines)
    {
        replication_engine.attach_replication_tasks_thread_pool(
            m_replication_tasks_thread_pool);
    }
}

const std::vector<replication_engine>&
replication_manager::get_replication_engines()
{
    return m_replication_engines;
}

status_code
replication_manager::execute_full_sync()
{
    status_code status = status::success;

    for (replication_engine& replication_engine : m_replication_engines)
    {
        status = replication_engine.execute_full_sync();

        if (status::failed(status))
        {
            logger::log(log_level::error, std::format("Full sync for directory '{}' failed. Status={:#X}.",
                replication_engine.get_source_directory_path().c_str(),
                status));

            return status;
        }
    }

    return status;
}

void
replication_manager::append_entry_to_replication_engines_router(
    file_descriptor p_watch_descriptor,
    uint32 p_replication_engine_index)
{
    m_replication_engines_router.emplace(
        p_watch_descriptor,
        p_replication_engine_index);
}

void
replication_manager::replication_tasks_entry_point(
    file_descriptor p_watch_descriptor,
    std::unique_ptr<replication_task>&& p_replication_task)
{
    logger::set_activity_id(p_replication_task->m_activity_id);

    logger::log(log_level::info, std::format("Received replication task to process. FilesystemObjectName={}.",
        p_replication_task->get_filesystem_object_name()));

    status_code status = send_replication_task(
        p_watch_descriptor,
        p_replication_task);

    p_replication_task->m_end_timestamp = timestamp::get_current_time();

    if (status::succeeded(status))
    {

    }
    else
    {

    }
}

status_code
replication_manager::parse_initial_configuration_file_into_memory(
    const std::string& p_initial_configuration_file)
{
    // Mock for now.
    
    directory source_directory("/home/jcjuarez/mock1");

    std::vector<directory> target_directories {directory("/home/jcjuarez/mock2"), directory("/home/jcjuarez/mock3")};

    replication_engine replication_engine(
        std::move(source_directory),
        std::move(target_directories));

    // Create move constuctor for replication engine as well.
    m_replication_engines.emplace_back(std::move(replication_engine));

    return status::success;
}

status_code
replication_manager::send_replication_task(
    file_descriptor p_watch_descriptor,
    std::unique_ptr<replication_task>& p_replication_task)
{
    status_code status = status::success;

    //
    // Ensure that the provided watch descriptor can be routed to a replication engine.
    //
    if (m_replication_engines_router.find(p_watch_descriptor) == m_replication_engines_router.end())
    {
        status = status::unknown_watch_descriptor;

        p_replication_task->set_last_error_timestamp(timestamp::get_current_time());

        logger::log(log_level::error, std::format("Watch descriptor is not present in the replication engines router. "
            "FilesystemObjectName={}, WatchDescriptor={}, Status={:#X}.",
            p_replication_task->get_filesystem_object_name(),
            p_watch_descriptor,
            status));

        return status;
    }

    replication_engine& replication_engine = m_replication_engines[m_replication_engines_router[p_watch_descriptor]];
    
    return replication_engine.execute_replication_task(p_replication_task);
}

} // namespace modula.
