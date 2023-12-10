// *************************************
// Modula Replication Engine
// Utilities
// 'logger.cc'
// Author: jcjuarez
// *************************************

#include "logger.hh"

#include <iostream>

namespace modula
{

//
// Constructor for the singleton instance. Initializes logger configuration.
//
logger::logger(
    /* logger options struct -> will hold the status of initialization. */)
{

}

void
logger::log(
    const log_level& p_log_level,
    const std::string&& p_string)
{
    std::lock_guard<std::mutex> lock(m_lock);

    std::cout << p_string.c_str() << std::endl;
}

logger&
logger::get_logger(
    /* optional logger options struct -> will hold the status of initialization. */)
{
    static logger logger_singleton;

    return logger_singleton;
}

} // namespace modula.
