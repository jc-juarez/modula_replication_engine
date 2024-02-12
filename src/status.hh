// *************************************
// Modula Replication Engine
// Utilities
// 'status.hh'
// Author: jcjuarez
// *************************************

#ifndef STATUS_
#define STATUS_

namespace modula
{

//
// Status code type alias.
//
using status_code = unsigned int;

//
// Status class for indicating errors across the system.
//
class status
{

    //
    // Static class.
    //
    status() = delete;

public:

    //
    // Determines whether a given status is considered as failure.
    //
    inline static
    bool
    failed(
        const status_code p_status_code)
    {
        return static_cast<int>(p_status_code) < 0;
    }

    //
    // Determines whether a given status is considered as success.
    //
    inline static
    bool
    succeeded(
        const status_code& p_status_code)
    {
        return p_status_code == success;
    }

    //
    // Determines whether a given status is the same as another status.
    //
    inline static
    bool
    is_same(
        const status_code& p_status_code_left,
        const status_code& p_status_code_right)
    {
        return p_status_code_left == p_status_code_right;
    }

    //
    // Determines whether a given status is not the same as another status.
    //
    inline static
    bool
    is_not_same(
        const status_code& p_status_code_left,
        const status_code& p_status_code_right)
    {
        return p_status_code_left != p_status_code_right;
    }

    //
    // Operation succeeded.
    //
    static constexpr status_code success = 0x0'0000000;

    //
    // Generic operation failed.
    //
    static constexpr status_code fail = 0x8'0000000;

    //
    // Failure to start the inotify instance.
    //
    static constexpr status_code inotify_startup_failed = 0x8'0000001;

    //
    // Failure to create a watch descriptor for a directory.
    //
    static constexpr status_code directory_watch_descriptor_creation_failed = 0x8'0000002;

    //
    // Failure to launch a thread.
    //
    static constexpr status_code launch_thread_failed = 0x8'0000003;

    //
    // Specified directory does not exist.
    //
    static constexpr status_code directory_does_not_exist = 0x8'0000004;

    //
    // Logger is not yet initialized.
    //
    static constexpr status_code logger_not_initialized = 0x8'0000005;

    //
    // Incorrect parameters.
    //
    static constexpr status_code incorrect_parameters = 0x8'0000006;

    //
    // Failure to create a directory.
    //
    static constexpr status_code directory_creation_failed = 0x8'0000007;

    //
    // Failure to retrieve an environment variable.
    //
    static constexpr status_code environment_variable_access_failed = 0x8'0000008;

    //
    // Malformed commmand line arguments provided.
    //
    static constexpr status_code malformed_command_line_arguments = 0x8'0000009;

    //
    // Provided configuration flag does not exist.
    //
    static constexpr status_code configuration_flag_not_recognized = 0x8'0000010;

    //
    // Logger is already initialized.
    //
    static constexpr status_code logger_already_initialized = 0x8'0000011;

    //
    // Failed to write to a file.
    //
    static constexpr status_code file_write_failed = 0x8'0000012;

    //
    // Failed to log to a file because incremental search reached its retry limit.
    //
    static constexpr status_code logging_incremental_search_failed = 0x8'0000013;

};

} // namespace modula.

#endif
