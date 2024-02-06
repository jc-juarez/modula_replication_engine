// *************************************
// Modula Replication Engine
// Utilities
// 'timestamp.hh'
// Author: jcjuarez
// *************************************

#include "utilities.hh"

#include <chrono>

#ifndef TIMESTAMP_
#define TIMESTAMP_

namespace modula
{

//
// Timestamp class for capturing the system time in UTC.
//
class timestamp
{

private:

    //
    // Private default constructor for the timestamp class.
    // Only used internally for assigning an initial time value.
    //
    timestamp();

public:

    //
    // Constructor for the timestamp class.
    //
    timestamp(
        const timestamp& p_timestamp);

    //
    // Returns the timestamp as a string.
    //
    std::string
    to_string();

    //
    // Retrieves the current time as a timestamp.
    //
    static
    timestamp
    get_current_time();

private:

    //
    // System clock time point.
    //
    std::chrono::time_point<std::chrono::system_clock> m_time_point;

    //
    // Timestamp format.
    //
    static constexpr character* c_timestamp_format = "%Y-%m-%dT%H:%M:%SZ";
    
};

} // namespace modula.

#endif
