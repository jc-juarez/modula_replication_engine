// *************************************
// Modula Replication Engine
// Utilities
// 'logger.hh'
// Author: jcjuarez
// *************************************

#include "status.hh"
#include "utilities.hh"

#include <mutex>
#include <random>
#include <format> // Added in header file for global access by including it.
#include <unistd.h>
#include <filesystem>

#ifndef LOGGER_ 
#define LOGGER_

namespace modula
{

enum class log_level : uint8
{
    //
    // Information level logs.
    // Used for debugging actions occurring in the system.
    //
    info = 0,

    //
    // Warning level logs.
    // Used for non-error-related events that require attention.
    //
    warning = 1,

    //
    // Error level logs.
    // Used for error-related events that indicate a failed action.
    //
    error = 2,

    //
    // Critical level logs.
    // Used for critical error-related events that may provoke a system shutdown.
    //
    critical = 3
};

struct logger_configuration;

//
// Logger singleton class for managing logging in the system.
//
class logger
{

private:

    //
    // Private constructor for the singleton instance.
    //
    logger(
        std::string* p_initial_message,
        const logger_configuration* p_logger_configuration);

public:

    //
    // Initialize singleton logger instance. Must be called only once.
    //
    static
    void
    initialize(
        const logger_configuration& p_logger_configuration);

    //
    // Logging external method.
    //
    static
    void
    log(
        const log_level& p_log_level,
        std::string&& p_message,
        const logger_configuration* p_logger_configuration = nullptr);

private:

    //
    // Logging internal method.
    //
    void
    log_message(
        const log_level& p_log_level,
        const character* p_message);

    //
    // Generates a random <8 bytes>-<8 bytes> unique identifier. 
    //
    std::string
    generate_unique_identifier();

    //
    // Generates a random 8 bytes number.
    //
    uint64
    generate_random_number();

    //
    // Constructs the log message with formatting.
    //
    std::string
    create_formatted_log_message(
        const log_level& p_log_level,
        const character* p_message);

    //
    // Logs a message to a log file.
    //
    status_code
    log_to_file(
        const character* p_message);

    //
    // Generates the curently pointed logs file path.
    //
    std::filesystem::path
    get_current_logs_file_path();

    //
    // Logs a message to the console.
    //
    static
    void
    log_to_console(
        const character* p_message);

    //
    // Flag for determining is the singleton instance is initialized.
    //
    static bool s_initialized;

    //
    // Text for info level logs.
    //
    static constexpr const character* c_info_log_level = "Info";

    //
    // Text for warning level logs.
    //
    static constexpr const character* c_warning_log_level = "Warning";

    //
    // Text for error level logs.
    //
    static constexpr const character* c_error_log_level = "Error";

    //
    // Text for critical level logs.
    //
    static constexpr const character* c_critical_log_level = "Critical";

    //
    // Text for default level logs.
    //
    static constexpr const character* c_default_log_level = "Unknown";

    //
    // Session logs directory prefix.
    //
    static constexpr const character* c_session_logs_directory_prefix = "modula-logs-";

    //
    // Logs files extension.
    //
    static constexpr const character* c_logs_files_extension = "log";

    //
    // Modula executable name.
    //
    static constexpr const character* c_modula = "modula";

    //
    // Max size in MiB for individual logs files.
    //
    static constexpr uint8 c_max_logs_file_size_mib = 10u;

    //
    // Max retries count for incremental search for logging.
    //
    static constexpr uint8 c_max_incremental_search_retry_count = 100u;

    //
    // Lock for synchronizing access across threads.
    //
    std::mutex m_lock;

    //
    // Random number generator for unique identifiers.
    //
    std::mt19937 m_random_number_generator;

    //
    // Distribution for random numbers generation.
    //
    std::uniform_int_distribution<uint64> m_random_number_distribution;

    //
    // Flag for determining whether debug mode is enabled.
    //
    bool m_debug_mode_enabled;

    //
    // Path to the directory where system logs will be stored for the session.
    //
    std::filesystem::path m_session_logs_directory_path;

    //
    // Logger session ID.
    //
    std::string m_session_id;

    //
    // Logs files count.  
    //
    uint64 m_logs_files_count;

    //
    // Path to the currently pointed logs file.
    //
    std::filesystem::path m_current_logs_file_path;

    //
    // Process ID for the session.
    //
    pid_t m_process_id;
    
};

} // namespace modula.

#endif
