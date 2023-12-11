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
    status_code& p_status)
{
    p_status = parse_initial_configuration_file_into_memory(
        p_initial_configuration_file);

    if (status::failed(p_status))
    {
        logger::get_logger().log(log_level::critical, std::format("Initial configuration file '{}' parsing failed. Status={:#X}.",
            p_initial_configuration_file.c_str(),
            p_status));

        return;
    }

    m_replication_tasks_thread_pool = std::make_shared<thread_pool>(
        c_replication_tasks_thread_pool_size);

    //
    // Initiate an initial full sync on all directories on startup.
    //
    p_status = execute_full_sync();

    if (status::failed(p_status))
    {
        logger::get_logger().log(log_level::critical, std::format("Initial full sync on startup failed. Status={:#X}.",
            p_status));

        return;
    }
}

bool
replication_manager::replication_engine_exists(
    const std::string& p_directory_name)
{
    return m_replication_engines.count(p_directory_name);
}

replication_engine&
replication_manager::get_replication_engine(
    const std::string& p_directory_name)
{
    return m_replication_engines[p_directory_name];
}

std::unordered_map<std::string, replication_engine>&
replication_manager::get_replication_engines()
{
    return m_replication_engines;
}

status_code
replication_manager::execute_full_sync()
{
    status_code status = status::success;

    for (auto& [replication_engine_name, replication_engine] : m_replication_engines)
    {
        status = replication_engine.execute_full_sync();

        if (status::failed(status))
        {
            logger::get_logger().log(log_level::error, std::format("Full sync for directory '{}' failed. Status={:#X}.",
                replication_engine_name,
                status));

            return status;
        }
    }

    return status;
}

status_code
replication_manager::parse_initial_configuration_file_into_memory(
    const std::string& p_initial_configuration_file)
{
    // Mock for now.
    
    directory source_directory("/home/jcjuarez/mock10");

    std::vector<directory> target_directories {directory("/home/jcjuarez/mock2"), directory("/home/jcjuarez/mock3")};

    replication_engine replication_engine(
        std::move(source_directory),
        std::move(target_directories),
        m_replication_tasks_thread_pool);

    // Create move constuctor for replication engine as well.
    m_replication_engines.emplace(replication_engine.get_name(), std::move(replication_engine));

    return status::success;
}

} // namespace modula.
