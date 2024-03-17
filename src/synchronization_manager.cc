// *************************************
// Modula Replication Engine
// Core
// 'synchronization_manager.cc'
// Author: jcjuarez
// *************************************

#include "logger.hh"
#include "synchronization_manager.hh"

#include <cstring>

namespace modula
{

synchronization_result::synchronization_result()
    : m_status(status::success),
      m_start_timestamp(timestamp::generate_invalid_timestamp()),
      m_end_timestamp(timestamp::generate_invalid_timestamp()),
      m_bytes_transferred(0)
{}

synchronization_result
synchronization_manager::execute_synchronization_action(
    const character* p_filesystem_object_path,
    const character* p_target_directory_path)
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
        "rsync -avz {} {}",
        p_filesystem_object_path,
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
        filesytem_object_synchronization_result.m_status = status::rsync_pipe_connection_failed;
        filesytem_object_synchronization_result.m_end_timestamp = timestamp::get_current_time();

        logger::log(log_level::error, std::format("Failed to open an IPC connection for the rsync process. "
            "FilesystemObjectPath={}, TargetDirectoryPath={}, {} (errno {}), Status={:#X}.",
            p_filesystem_object_path,
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
    int32 exit_status = pclose(rsync_pipe.get());

    //
    // Release internal file handle for avoiding calling the pipe wrapper destructor.
    //
    rsync_pipe.release();

    if (!WIFEXITED(exit_status) ||
        status::failed(exit_status))
    {
        //
        // Failed to open rsync IPC pipe.
        //
        filesytem_object_synchronization_result.m_status = status::rsync_pipe_connection_failed;
        filesytem_object_synchronization_result.m_end_timestamp = timestamp::get_current_time();

        logger::log(log_level::error, std::format("Failed to open an IPC connection for the rsync process. "
            "FilesystemObjectPath={}, TargetDirectoryPath={}, {} (errno {}), Status={:#X}.",
            p_filesystem_object_path,
            p_target_directory_path,
            std::strerror(errno),
            errno,
            filesytem_object_synchronization_result.m_status));

        return filesytem_object_synchronization_result;
    }

    if (WIFEXITED(exit_status))
    {
        exit_status = WEXITSTATUS(exit_status);
        logger::log(log_level::info, std::format("new Good: {}", exit_status));
    }
    else
    {
        // Handle cases where rsync exited abnormally
        exit_status = -1;
        logger::log(log_level::info, std::format("new Bad: {}", exit_status));
    }

    //
    // Successful synchronization; result is finalized.
    //
    filesytem_object_synchronization_result.m_end_timestamp = timestamp::get_current_time();

    return filesytem_object_synchronization_result;
}

} // namespace modula.
