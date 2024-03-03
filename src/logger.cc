// *************************************
// Modula Replication Engine
// Utilities
// 'logger.cc'
// Author: jcjuarez
// *************************************

#include "logger.hh"
#include "timestamp.hh"
#include "system_configuration.hh"

#include <ctime>
#include <limits>
#include <iostream>
#include <syslog.h>
#include <sys/syscall.h>

namespace modula
{

bool logger::s_initialized = false;

logger::logger(
    status_code* p_status,
    std::string* p_initial_message,
    const logger_configuration* p_logger_configuration)
    : m_random_number_distribution(0, std::numeric_limits<uint64>::max()),
      m_logs_files_count(0),
      m_process_id(getpid())
{
    //
    // The logger is agnostic to the default configurations given by the
    // configurations provider; if none are given, abort the system execution.
    //
    if (p_logger_configuration == nullptr)
    {
        *p_status = status::incorrect_parameters;
        
        log_error_fallback(std::format("<!> Modula replication engine logger has received incorrect initialization configuration parameters.\n").c_str());

        return;
    }

    m_debug_mode_enabled = p_logger_configuration->m_debug_mode_enabled;
    const std::filesystem::path logs_directory_path = std::filesystem::absolute(p_logger_configuration->m_logs_directory_path);

    //
    // Initialize the random number generator.
    //
    try
    {
        m_random_number_generator.seed(std::random_device{}());
    }
    catch (const std::exception& exception)
    {
        m_random_number_generator.seed(static_cast<uint32>(std::time(nullptr)));
    }

    //
    // Set the session ID after the random number generator has been
    // initialized and ensure that the session ID does not already exist.
    //
    std::string session_id;
    std::filesystem::path session_logs_directory_path;

    do
    {
        session_id = generate_unique_identifier();
        session_logs_directory_path = logs_directory_path;
        session_logs_directory_path.append(c_session_logs_directory_prefix + session_id);
    }
    while (std::filesystem::exists(session_logs_directory_path));

    m_session_id = session_id;

    std::string exception;
    *p_status = utilities::create_directory(
        session_logs_directory_path.string(),
        &exception);

    if (status::failed(*p_status))
    {
        log_error_fallback(std::format("<!> Modula replication engine logger failed to create session logs directory '{}'. Exception: '{}'.\n",
            session_logs_directory_path.string().c_str(),
            exception.c_str()).c_str());

        return;
    }

    m_session_logs_directory_path = session_logs_directory_path;

    p_initial_message->append("Logs will be stored at '" + m_session_logs_directory_path.string() + "'.");

    //
    // Set the initially pointed logs file after successful initialization.
    //
    m_current_logs_file_path = get_current_logs_file_path();
}

status_code
logger::initialize(
    const logger_configuration& p_logger_configuration)
{
    if (s_initialized)
    {
        log_error_fallback(std::format("<!> Modula replication engine logger has not been yet initialized.\n").c_str());

        return status::logger_not_initialized;
    }

    s_initialized = true;

    status_code status = status::success;

    log(log_level::info,
        "Modula replication engine logger has been initialized. ",
        &status,
        &p_logger_configuration);

    return status;
}

void
logger::log(
    const log_level& p_log_level,
    std::string&& p_message,
    status_code* p_status,
    const logger_configuration* p_logger_configuration)
{
    if (!s_initialized)
    {
        log_error_fallback(std::format("<!> Modula replication engine logger has not been yet initialized.\n",
            status::logger_not_initialized).c_str());

        return;
    }

    //
    // Forceful lazy initialization for the
    // singleton through the initialize method.
    //
    static logger logger_singleton_instance(
        p_status,
        &p_message,
        p_logger_configuration);

    if (p_status != nullptr &&
        status::failed(*p_status))
    {
        return;
    }

    logger_singleton_instance.log_message(
        p_log_level,
        p_message.c_str());
}

void
logger::log_error_fallback(
    const character* p_message)
{
    log_to_syslog(p_message);
    log_error_to_console(p_message);
}

void
logger::log_message(
    const log_level& p_log_level,
    const character* p_message)
{
    const std::string formatted_log_message = create_formatted_log_message(
        p_log_level,
        p_message);

    {
        std::scoped_lock<std::mutex> lock(m_lock);

        if (m_debug_mode_enabled)
        {
            log_message_to_console(formatted_log_message.c_str());
        }

        status_code status = log_to_file(formatted_log_message.c_str());

        //
        // Syslog retains errors and lost messages if any problem occurs.
        //
        if (status::failed(status))
        {
            log_to_syslog(std::format(
                "Status={}, Message={}",
                status,
                formatted_log_message.c_str()).c_str()); 
        }
    }
}

std::string
logger::generate_unique_identifier()
{
    return std::format(
        "{}-{}",
        generate_random_number(),
        generate_random_number());
}

uint64
logger::generate_random_number()
{
    return m_random_number_distribution(m_random_number_generator);
}

std::string
logger::create_formatted_log_message(
    const log_level& p_log_level,
    const character* p_message) const
{
    const character* level = nullptr;

    switch (static_cast<uint8>(p_log_level))
    {
        case static_cast<uint8>(log_level::info):
        {
            level = c_info_log_level;

            break;
        }
        case static_cast<uint8>(log_level::warning):
        {
            level = c_warning_log_level;

            break;
        }
        case static_cast<uint8>(log_level::error):
        {
            level = c_error_log_level;

            break;
        }
        case static_cast<uint8>(log_level::critical):
        {
            level = c_critical_log_level;

            break;
        }
        default:
        {
            level = c_default_log_level;

            break;
        }
    }

    return std::format(
        "[{}] ({}) PID={}, TID={}. <{}> {}\n",
        timestamp::get_current_time().to_string().c_str(),
        m_session_id.c_str(),
        m_process_id,
        syscall(SYS_gettid),
        level,
        p_message);
}

status_code
logger::log_to_file(
    const character* p_message)
{
    status_code status = status::success;

    //
    // Idemponent logging even if the directory is not present.
    //
    if (!std::filesystem::exists(m_session_logs_directory_path))
    {
        status = utilities::create_directory(m_session_logs_directory_path);

        return_status_if_failed(status)
    }

    //
    // Incremental search for determining the file on which to log the message. Performance of
    // this logging mechanism can be impacted if other processes interfere with the directory.
    // In case of continuous errors that exceed a retry limit, the operation is considered failed.
    //
    std::filesystem::path current_logs_file;

    for (uint16 incremental_search_retry_count = 1; incremental_search_retry_count <= c_max_incremental_search_retry_count; ++incremental_search_retry_count)
    {
        //
        // If the file exists ensure that it has not exceeded the size limit; if it 
        // has, rollover the logs file count and switch the currently pointed logs file.
        //
        if (!std::filesystem::exists(m_current_logs_file_path) ||
            utilities::get_file_size(m_current_logs_file_path.string()) < c_max_logs_file_size_mib)
        {
            for (uint16 logs_writing_attempts_retry_count = 1; logs_writing_attempts_retry_count <= c_max_logs_writing_attempts_retry_count; ++logs_writing_attempts_retry_count)
            {
                status = utilities::append_content_to_file(
                    m_current_logs_file_path,
                    p_message);

                return_status_if_succeeded(status)
            }
        }

        if (incremental_search_retry_count == c_max_incremental_search_retry_count)
        {
            return status::logging_incremental_search_failed;
        }

        ++m_logs_files_count;
        m_current_logs_file_path = get_current_logs_file_path();
    }

    return status;
}

std::filesystem::path
logger::get_current_logs_file_path() const
{
    std::string current_logs_file_name = std::format(
        "log_{}_{}.{}",
        m_session_id,
        m_logs_files_count,
        c_logs_files_extension);

    return m_session_logs_directory_path / current_logs_file_name;
}

void
logger::log_message_to_console(
    const character* p_message)
{
    std::cout << p_message;
}

void
logger::log_error_to_console(
    const character* p_message)
{
    std::cerr << p_message;
}

void
logger::log_to_syslog(
    const character* p_message)
{
    openlog(c_modula, LOG_PID | LOG_CONS, LOG_USER);
    syslog(LOG_ERR, "%s", p_message);
    closelog();
}

} // namespace modula.
