// *************************************
// Modula Replication Engine
// Utilities
// 'utilities.hh'
// Author: jcjuarez
// *************************************

#ifndef UTILITIES_
#define UTILITIES_

#include "status.hh"

#include <string>

namespace modula
{

//
// Infinite repetition macro.
//
#define forever while (true)

//
// Return if failed macro.
//
#define return_if_failed(p_status) if (status::failed(p_status)) { return; }

//
// Return status if failed macro.
//
#define return_status_if_failed(p_status) if (status::failed(p_status)) { return p_status; }

//
// Return status if succeeded macro.
//
#define return_status_if_succeeded(p_status) if (status::succeeded(p_status)) { return p_status; }

//
// Unsigned 1 byte.
//
using byte = unsigned char;
using uint8 = unsigned char;

//
// Unsigned 2 bytes.
//
using uint16 = unsigned short;

//
// Unsigned 4 bytes.
//
using uint32 = unsigned int;

//
// Unsigned 8 bytes.
//
using uint64 = unsigned long long;

//
// Signed 1 byte.
//
using int8 = char;
using character = char;

//
// Signed 2 bytes.
//
using int16 = short;

//
// Signed 4 bytes.
//
using int32 = int;

//
// Signed 8 bytes.
//
using int64 = long long;

//
// Single-precision 4 bytes floating point.
//
using single_precision = float;

//
// Double-precision 8 bytes floating point.
//
using double_precision = double;

//
// File descriptor alias.
//
using file_descriptor = int;

//
// Invalid file descriptor.
//
static constexpr file_descriptor c_invalid_file_descriptor = -1;

//
// Utility functions.
//
namespace utilities
{

//
// Determines whether a file descriptor is valid.
//
bool
is_file_descriptor_valid(
    const file_descriptor& p_file_descriptor);

//
// Determines whether a system call failed.
//
bool
system_call_failed(
    const int32 p_result);

//
// Creates the specified directory recursively.
//
status_code
create_directory(
    const std::string& p_directory_name,
    std::string* p_exception = nullptr);

//
// Creates and/or appends data to the specified file.
//
status_code
append_content_to_file(
    const std::string& p_file_path,
    const character* p_content);

//
// Gets the size of a file in MiB
//
uint32
get_file_size(
    const std::string& p_file_path);

} // namespace utilities.

} // namespace modula.

#endif
