// *************************************
// Modula Replication Engine
// Utilities
// 'replication_engine.cc'
// Author: jcjuarez
// *************************************

#include "logger.hh"
#include "replication_engine.hh"
#include "synchronization_manager.hh"

#include <filesystem>

namespace modula
{

replication_engine::replication_engine(
    const directory&& p_source_directory,
    const std::vector<directory>&& p_target_directories) :
    m_source_directory(std::move(p_source_directory)),
    m_target_directories(std::move(p_target_directories))
{}

replication_engine::replication_engine(
    replication_engine&& p_replication_engine) :
    m_replication_tasks_thread_pool(std::move(p_replication_engine.m_replication_tasks_thread_pool)),
    m_source_directory(std::move(p_replication_engine.m_source_directory)),
    m_target_directories(std::move(p_replication_engine.m_target_directories))
{}

void
replication_engine::attach_replication_tasks_thread_pool(
    std::shared_ptr<thread_pool> p_replication_tasks_thread_pool)
{
    m_replication_tasks_thread_pool = p_replication_tasks_thread_pool;
}

status_code
replication_engine::execute_full_sync()
{
    // Mock for now.
    return status::success;
}

status_code
replication_engine::execute_replication_task(
    std::unique_ptr<replication_task>& p_replication_task)
{
    std::scoped_lock<std::mutex> lock(m_replication_engine_lock);

    status_code status = status::success;

    p_replication_task->m_filesystem_object_path = get_source_directory_path() + "/" + p_replication_task->get_filesystem_object_name();

    //
    // Current existence validation check should only be performed for non-remove
    // actions since a remove action has already deleted the object from the filesystem.
    //
    if (p_replication_task->get_replication_action() != replication_action::remove)
    {
        if (!std::filesystem::exists(p_replication_task->m_filesystem_object_path))
        {
            status = status::filesystem_object_does_not_exist;

            p_replication_task->set_last_error_timestamp(timestamp::get_current_time());

            logger::log(log_level::error, std::format("Filesystem object to replicate does not exist. "
                "FilesystemObjectPath={}, Status={:#X}.",
                p_replication_task->m_filesystem_object_path.c_str(),
                status));

            return status;
        }
    }

    return enqueue_distributed_replication_tasks(p_replication_task);
}

const std::string&
replication_engine::get_source_directory_path() const
{
    return m_source_directory.get_path();
}

status_code
replication_engine::enqueue_distributed_replication_tasks(
    std::unique_ptr<replication_task>& p_replication_task)
{
    status_code status = status::success;

    std::unordered_map<std::string, std::optional<std::future<status_code>>> enqueue_status_responses;

    for (const directory& target_directory : m_target_directories)
    {
        const std::string& target_directory_path = target_directory.get_path(); 

        std::optional<std::future<status_code>> enqueue_status = m_replication_tasks_thread_pool->enqueue_task(
            [this, &target_directory_path, &p_replication_task]()
            {
                return this->replicate_filesystem_object(
                    target_directory_path.c_str(),
                    p_replication_task);
            }
        );

        enqueue_status_responses.emplace(
            target_directory_path,
            std::move(enqueue_status));
    }

    for (std::pair<const std::string, std::optional<std::future<status_code>>>& enqueue_status_response : enqueue_status_responses)
    {
        if (enqueue_status_response.second == std::nullopt)
        {
            //
            // Even if the enqueue process failed, the system must wait for all pending tasks to complete.
            //
            status = status::thread_pool_enqueue_process_failed;

            logger::log(log_level::error, std::format("Replication tasks distribution thread pool blocked replication task enqueue process. "
                "Replication task may become partial or corrupted midway. Status={:#X}.",
                status));
        }
        else
        {
            enqueue_status_response.second.value().wait();
        }
    }

    return status;
}

status_code
replication_engine::replicate_filesystem_object(
    const character* p_target_directory_path,
    std::unique_ptr<replication_task>& p_replication_task)
{
    logger::set_activity_id(p_replication_task->m_activity_id);

    logger::log(log_level::info, std::format("Starting filesystem object replication. "
        "FilesystemObjectPath={}, TargetDirectoryPath={}.",
        p_replication_task->m_filesystem_object_path.c_str(),
        p_target_directory_path));

    //
    // Send an rsync synchronization command for handling replications.
    //
    synchronization_result filesytem_object_synchronization_result = synchronization_manager::execute_synchronization_task(
        p_target_directory_path,
        p_replication_task);

    status_code& status = filesytem_object_synchronization_result.m_status;

    if (status::succeeded(status))
    {
        logger::log(log_level::info, std::format("Filesystem object replication succeeded. "
            "FilesystemObjectPath={}, TargetDirectoryPath={}, StartTime={}, EndTime={}, BytesTransferred={}, BytesPerSecond={:.2f}.",
            p_replication_task->m_filesystem_object_path.c_str(),
            p_target_directory_path,
            filesytem_object_synchronization_result.m_start_timestamp.to_string(),
            filesytem_object_synchronization_result.m_end_timestamp.to_string(),
            filesytem_object_synchronization_result.m_bytes_transferred,
            filesytem_object_synchronization_result.m_bytes_per_second));
    }
    else
    {
        logger::log(log_level::error, std::format("Filesystem object replication failed. "
            "FilesystemObjectPath={}, TargetDirectoryPath={}, StartTime={}, EndTime={}. Status={:#X}.",
            p_replication_task->m_filesystem_object_path.c_str(),
            p_target_directory_path,
            filesytem_object_synchronization_result.m_start_timestamp.to_string(),
            filesytem_object_synchronization_result.m_end_timestamp.to_string(),
            status));
    }

    return status;
}

} // namespace modula.
