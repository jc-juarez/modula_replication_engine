// *************************************
// Modula Replication Engine
// Utilities
// 'timestamp.cc'
// Author: jcjuarez
// *************************************

#include "timestamp.hh"

#include <ctime>
#include <sstream>
#include <iomanip>

namespace modula
{

timestamp::timestamp()
    : m_time_point(std::chrono::system_clock::now())
{}

timestamp::timestamp(
    const timestamp& p_timestamp)
    : m_time_point(p_timestamp.m_time_point)
{}

std::string
timestamp::to_string()
{
    time_t current_time = std::chrono::system_clock::to_time_t(m_time_point);

    //
    // Always convert to UTC representation.
    //
    std::tm current_time_utc;
    gmtime_r(&current_time, &current_time_utc);

    std::ostringstream current_time_utc_stream;
    current_time_utc_stream << std::put_time(&current_time_utc, c_timestamp_format);

    return current_time_utc_stream.str();
}

timestamp
timestamp::get_current_time()
{
    return timestamp();
}

} // namespace modula.
