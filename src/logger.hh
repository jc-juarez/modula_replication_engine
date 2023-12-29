// *************************************
// Modula Replication Engine
// Utilities
// 'logger.hh'
// Author: jcjuarez
// *************************************

#include "status.hh"
#include "utilities.hh"

#include <mutex>
#include <format>

#ifndef LOGGER_
#define LOGGER_

namespace modula
{

struct logger_initialization_data
{
    //
    // Flag for determining whether debug mode is enabled for the logger instance.
    //
    bool m_debug_mode_enabled;

    //
    // Path for storing the logger files.
    //
    std::string m_logs_directory;
};

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
    // Default constructor for the singleton instance.
    //
    logger(
        const logger_initialization_data* p_logger_initialization_data);

    //
    // Logging internal method.
    //
    void
    log_internal(
        const log_level& p_log_level,
        const std::string&& p_string);

public:

    //
    // Initialize singleton logger instance. Must be called only once.
    //
    static
    void
    initialize(
        const logger_initialization_data* p_logger_initialization_data);

    //
    // Logging external method.
    //
    static
    void
    log(
        const log_level& p_log_level,
        const std::string&& p_string,
        const logger_initialization_data* p_logger_initialization_data = nullptr);

private:

    //
    // Flag for determining is the singleton instance is initialized.
    //
    static bool s_initialized;

    //
    // Lock for synchronizing access across threads.
    //
    std::mutex m_lock;

    //
    // Flag for determining whether debug mode is enabled.
    //
    bool m_debug_mode_enabled;

    //
    // Path where system logs will be stored.
    //
    std::string m_logs_directory;
    
};

} // namespace modula.

#endif
