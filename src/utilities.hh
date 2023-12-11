// *************************************
// Modula Replication Engine
// Utilities
// 'utilities.hh'
// Author: jcjuarez
// *************************************

#ifndef UTILITIES_
#define UTILITIES_

#include <string>

namespace modula
{

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
// File descriptor alias.
//
using file_descriptor = int;

//
// Determines whether a file descriptor is valid.
//
bool
is_file_descriptor_valid(
    const file_descriptor& p_file_descriptor);

//
// Throws an standard exception with the specified string.
//
void
throw_exception(
    const std::string&& p_string);

//
// Infinite repetition macro.
//
#define forever while (true)

} // namespace modula.

#endif
