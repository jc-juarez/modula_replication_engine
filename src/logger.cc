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
#include <sstream>
#include <iostream>
#include <filesystem>

namespace modula
{

bool logger::s_initialized = false;

logger::logger(
    const logger_configuration* p_logger_configuration)
    : m_random_number_distribution(0, std::numeric_limits<uint64>::max())
{
    //
    // The logger is agnostic to the default configurations given by the
    // configurations provider; if none are given, abort the system execution.
    //
    if (p_logger_configuration == nullptr)
    {
        throw_exception(std::format("<!> Modula replication engine logger has received incorrect initialization configuration parameters. Status={:#X}.",
            status::incorrect_parameters));
    }

    m_debug_mode_enabled = p_logger_configuration->m_debug_mode_enabled;
    m_logs_directory_path = p_logger_configuration->m_logs_directory_path;

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
        session_logs_directory_path = m_logs_directory_path;
        session_logs_directory_path.append(c_session_logs_directory_prefix + session_id);
    }
    while (std::filesystem::exists(session_logs_directory_path));

    m_session_id = session_id;

    std::string exception;
    status_code status = create_directory(
        session_logs_directory_path.string(),
        &exception);

    if (status::failed(status))
    {
        throw_exception(std::format("<!> Modula replication engine logger failed to create session logs directory '{}'. Exception: '{}', Status={:#X}.",
            session_logs_directory_path.string().c_str(),
            exception.c_str(),
            status));
    }
}

void
logger::initialize(
    const logger_configuration* p_logger_configuration)
{
    s_initialized = true;

    log(log_level::info,
        "Modula Replication Engine logger has been initialized.",
        p_logger_configuration);
}

void
logger::log(
    const log_level& p_log_level,
    const std::string&& p_message,
    const logger_configuration* p_logger_configuration)
{
    if (!s_initialized)
    {
        throw_exception(std::format("<!> Modula replication engine logger has not been yet initialized. Status={:#X}.",
            status::logger_not_initialized));
    }

    //
    // Forceful lazy initialization for the
    // singleton through the initialize method.
    //
    static logger logger_singleton_instance(
        p_logger_configuration);

    logger_singleton_instance.log_message(
        p_log_level,
        std::move(p_message));
}

void
logger::log_message(
    const log_level& p_log_level,
    const std::string&& p_message)
{
    const std::string formatted_log_message = create_formatted_log_message(
        p_log_level,
        std::move(p_message));

    {
        std::scoped_lock<std::mutex> lock(m_lock);

        if (m_debug_mode_enabled)
        {
            // Create a wrapper function around this.
            std::cout << p_message.c_str() << std::endl;
        }

        // Create a function to append the current log to a file.
        // This function should first check if the session-id subdirectory is empty; if so, it must create a new file. (Files are: log_{session-id}_{logs_file_count}.log)
        // If not empty, it must be able to grab the last file (can be identified by the logs_file_count in its name, if fails then create a new file). Be sure to never overwrite existing files.
        // This must be able to determine the size in MiB of the previous file: if it exceeds a threshold it needs a new file, if not write to that prev file.
        // append_log_to_file(std::move(formatted_log_message));
    }
}

std::string
logger::generate_unique_identifier()
{
    std::stringstream unique_identifier_stream;

    unique_identifier_stream
        << std::to_string(generate_random_number())
        << "-"
        << std::to_string(generate_random_number());

    return unique_identifier_stream.str();
}

uint64
logger::generate_random_number()
{
    return m_random_number_distribution(m_random_number_generator);
}

std::string
logger::create_formatted_log_message(
    const log_level& p_log_level,
    const std::string&& p_message)
{
    character* level = nullptr;

    switch (static_cast<uint8>(p_log_level))
    {
        case static_cast<uint8>(log_level::info):

            level = c_info_log_level;
            break;

        case static_cast<uint8>(log_level::warning):

            level = c_warning_log_level;
            break;

        case static_cast<uint8>(log_level::error):

            level = c_error_log_level;
            break;

        case static_cast<uint8>(log_level::critical):

            level = c_critical_log_level;
            break;

        default:

            level = c_default_log_level;
            break;
    }

    std::stringstream formatted_log_message;

    // Also log the m_session_id.
    formatted_log_message
        << "["
        << timestamp::get_current_time().to_string()
        << "] <"
        << level
        << "> "
        << p_message;

    return formatted_log_message.str();
}

} // namespace modula.
