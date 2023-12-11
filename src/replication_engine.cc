// *************************************
// Modula Replication Engine
// Utilities
// 'replication_engine.cc'
// Author: jcjuarez
// *************************************

#include "replication_engine.hh"

namespace modula
{

replication_engine::replication_engine(
    directory p_source_directory,
    const std::vector<directory>&& p_target_directories,
    const std::shared_ptr<thread_pool> p_replication_tasks_thread_pool) :
    m_source_directory(p_source_directory),
    m_target_directories(std::move(p_target_directories)),
    m_replication_tasks_thread_pool(p_replication_tasks_thread_pool)
{}

status_code
replication_engine::execute_full_sync()
{
    // Mock for now.
    return status::success;
}

status_code
replication_engine::enqueue_replication_task(
    std::unique_ptr<replication_task>&& p_replication_task)
{
    // Mock for now.
    return status::success;
}

status_code
replication_engine::execute_replication_task(
    std::unique_ptr<replication_task>&& p_replication_task)
{
    // Mock for now.
    return status::success;
}

std::string
replication_engine::get_name() const
{
    return m_source_directory.get_name();
}

} // namespace modula.
