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

timestamp::timestamp(
    const bool p_invalid_timestamp)
{
    m_time_point = p_invalid_timestamp ? std::chrono::time_point<std::chrono::system_clock>::min() :
        m_time_point = std::chrono::system_clock::now();
}

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

    std::chrono::milliseconds milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(m_time_point.time_since_epoch()) % 1000;
    current_time_utc_stream << '.' << std::setfill('0') << std::setw(3) << milliseconds.count() << 'Z';

    return current_time_utc_stream.str();
}

timestamp
timestamp::get_current_time()
{
    return timestamp(false /* Valid timestamp. */);
}

timestamp
timestamp::generate_invalid_timestamp()
{
    return timestamp(true /* Invalid timestamp. */);
}

} // namespace modula.
