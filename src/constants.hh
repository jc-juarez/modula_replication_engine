// *************************************
// Modula Replication Engine
// Utilities
// 'constants.hh'
// Author: jcjuarez
// *************************************

#ifndef CONSTANTS_
#define CONSTANTS_

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
// Status code alias.
//
using status_code = int;

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
    // Validates whether a given status is considered as failure.
    //
    inline static
    bool
    failed(
        const status_code p_status_code)
    {
        return p_status_code < 0;
    }

    //
    // Validates whether a given status is considered as success.
    //
    inline static
    bool
    succeeded(
        const status_code p_status_code)
    {
        return p_status_code == success;
    }

    //
    // Validates whether a given status is the same as another status.
    //
    inline static
    bool
    is_same(
        const status_code p_status_code_left,
        const status_code p_status_code_right)
    {
        return p_status_code_left == p_status_code_right;
    }

    //
    // Validates whether a given status is not the same as another status.
    //
    inline static
    bool
    is_not_same(
        const status_code p_status_code_left,
        const status_code p_status_code_right)
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

};

#endif
