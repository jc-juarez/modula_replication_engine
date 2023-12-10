// *************************************
// Modula Replication Engine
// Utilities
// 'constants.hh'
// Author: jcjuarez
// *************************************

#ifndef CONSTANTS_
#define CONSTANTS_

#include <string>
#include <stdexcept>

//
//  Unsigned 1 byte.
//
using byte = unsigned char;
using uint8 = unsigned char;

//
//  Unsigned 2 bytes.
//
using uint16 = unsigned short;

//
//  Unsigned 4 bytes.
//
using uint32 = unsigned int;

//
//  Unsigned 8 bytes.
//
using uint64 = unsigned long long;

//
//  Signed 1 byte.
//
using int8 = char;

//
//  Signed 2 bytes.
//
using int16 = short;

//
//  Signed 4 bytes.
//
using int32 = int;

//
//  Signed 8 bytes.
//
using int64 = long long;

//
// Status code type alias.
//
using status_code = uint32;

//
// File descriptor alias.
//
using file_descriptor = int;

//
// Determines whether a file descriptor is valid.
//
inline
bool
is_file_descriptor_valid(
    const file_descriptor& p_file_descriptor)
{
    return p_file_descriptor != -1;
}

//
// Throws an standard exception with the specified string.
//
inline
void
throw_exception(
    const std::string&& p_string)
{
    throw std::runtime_error(p_string.c_str());
}

//
// Infinite repetition macro.
//
#define forever while (true)

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
        return static_cast<int32>(p_status_code) < 0;
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

};

#endif
