// *************************************
// Modula Replication Engine
// Core
// 'synchronization_manager.cc'
// Author: jcjuarez
// *************************************

#include "logger.hh"
#include "replication_task.hh"
#include "synchronization_manager.hh"

#include <regex>
#include <cstring>

namespace modula
{

synchronization_result::synchronization_result()
    : m_status(status::success),
      m_start_timestamp(timestamp::generate_invalid_timestamp()),
      m_end_timestamp(timestamp::generate_invalid_timestamp()),
      m_bytes_transferred(0),
      m_bytes_per_second(0.0)
{}

synchronization_result
synchronization_manager::execute_synchronization_task(
    const character* p_target_directory_path,
    std::unique_ptr<replication_task>& p_replication_task)
{
    static thread_local character rsync_result_buffer[c_rsync_result_buffer_size];

    std::string rsync_result;
    synchronization_result filesytem_object_synchronization_result;

    //
    // Set synchronozation start time.
    //
    filesytem_object_synchronization_result.m_start_timestamp = timestamp::get_current_time();

    //
    // Construct synchronization command to be executed.
    //
    std::string rsync_command = std::format(
        "rsync -avz {} {} 2>&1",
        p_replication_task->m_filesystem_object_path,
        p_target_directory_path);

    //
    // The pipe wrapper will only invoke the destructor in case of a midway
    // processing error; the internal file handle will be released if possible.
    //
    std::unique_ptr<FILE, decltype(&pclose)> rsync_pipe(
        popen(rsync_command.c_str(), "r"),
        pclose);

    if (!rsync_pipe)
    {
        //
        // Failed to open rsync IPC pipe.
        //
        const timestamp failure_time = timestamp::get_current_time();
        filesytem_object_synchronization_result.m_status = status::rsync_pipe_connection_failed;
        filesytem_object_synchronization_result.m_end_timestamp = failure_time;
        p_replication_task->set_last_error_timestamp(failure_time);

        logger::log(log_level::error, std::format("Failed to open an IPC connection for the rsync process. "
            "FilesystemObjectPath={}, TargetDirectoryPath={}, {} (errno {}), Status={:#X}.",
            p_replication_task->m_filesystem_object_path,
            p_target_directory_path,
            std::strerror(errno),
            errno,
            filesytem_object_synchronization_result.m_status));

        return filesytem_object_synchronization_result;
    }

    while (fgets(rsync_result_buffer, sizeof(rsync_result_buffer), rsync_pipe.get()) != nullptr)
    {
        rsync_result += rsync_result_buffer;
    }

    //
    // Obtain detached process exit code before releasing internal file handle.
    //
    int32 rsync_process_exit_status = pclose(rsync_pipe.get());

    //
    // Release internal file handle for avoiding calling the pipe wrapper destructor.
    //
    rsync_pipe.release();

    if (!WIFEXITED(rsync_process_exit_status) ||
        status::failed(rsync_process_exit_status))
    {
        //
        // The spawned rsync process exited with an error code; the synchronization task failed.
        //
        const timestamp failure_time = timestamp::get_current_time();
        filesytem_object_synchronization_result.m_status = status::rsync_spawned_process_failed;
        filesytem_object_synchronization_result.m_end_timestamp = failure_time;
        p_replication_task->set_last_error_timestamp(failure_time);

        logger::log(log_level::error, std::format("The spawned rsync process failed the synchronization task. "
            "FilesystemObjectPath={}, TargetDirectoryPath={}, RsyncProcessExitStatus={}, Status={:#X}.",
            p_replication_task->m_filesystem_object_path,
            p_target_directory_path,
            rsync_process_exit_status,
            filesytem_object_synchronization_result.m_status));

        return filesytem_object_synchronization_result;
    }

    //
    // Successful synchronization completed; result is parsed and finalized.
    //
    filesytem_object_synchronization_result.m_end_timestamp = timestamp::get_current_time();

    std::smatch data_matches;
    std::regex data_pattern(c_rsync_data_pattern);

    if (std::regex_search(rsync_result, data_matches, data_pattern))
    {
        //
        // Parse bytes transferred, if possible.
        //
        if (data_matches.size() >= 2)
        {
            filesytem_object_synchronization_result.m_bytes_transferred = std::stoi(data_matches[1].str());
        }

        //
        // Parse bytes per second transferred, if possible.
        //
        if (data_matches.size() >= 3)
        {
            filesytem_object_synchronization_result.m_bytes_per_second = std::stod(data_matches[2].str());
        }
    }

    return filesytem_object_synchronization_result;
}

} // namespace modula.
