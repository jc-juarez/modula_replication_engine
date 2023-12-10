// *************************************
// Modula Replication Engine
// Utilities
// 'logger.hh'
// Author: jcjuarez
// *************************************

#include "constants.hh"

#include <mutex>
#include <format>

#ifndef LOGGER_
#define LOGGER_

namespace modula
{

enum class log_level : uint8
{
    info = 0,
    warning = 1,
    error = 2,
    critical = 3
};

//
// Logger singleton class for managing logging in the system.
//
class logger
{

private:

    //
    // Constructor for the singleton instance. Initializes logger configuration.
    //
    logger(
        /* logger options struct -> will hold the status of initialization. */);

public:

    //
    // Log function.
    //
    void
    log(
        const log_level& p_log_level,
        const std::string&& p_string);

    //
    // Retrieves the singleton logger instance.
    //
    static
    logger&
    get_logger(
        /* optional logger options struct -> will hold the status of initialization. */);

private:

    //
    // Lock for synchronizing access across threads.
    //
    std::mutex m_lock;
    
};

} // namespace modula.

#endif
