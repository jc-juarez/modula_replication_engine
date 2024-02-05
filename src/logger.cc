// *************************************
// Modula Replication Engine
// Utilities
// 'logger.cc'
// Author: jcjuarez
// *************************************

#include "logger.hh"
#include "timestamp.hh"
#include "system_configuration.hh"

#include <iostream>

namespace modula
{

bool logger::s_initialized = false;

logger::logger(
    const logger_configuration* p_logger_configuration)
{
    //
    // The logger is agnostic to the default configurations given by the
    // configurations provider; if none are given, abort the system execution.
    //
    if (p_logger_configuration == nullptr)
    {
        throw_exception(std::format("<!> Modula Replication Engine logger has received incorrect initialization configuration parameters. Status={:#X}.",
            status::incorrect_parameters));
    }

    m_debug_mode_enabled = p_logger_configuration->m_debug_mode_enabled;
    m_logs_directory_path = p_logger_configuration->m_logs_directory_path;
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
        throw_exception(std::format("<!> Modula Replication Engine logger has not been yet initialized. Status={:#X}.",
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
            std::cout << p_message.c_str() << std::endl;
        }
    }
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

    std::string formatted_log_message;

    formatted_log_message.append(
        "[" + timestamp::get_current_time().to_string() + "] <" + level + "> " + p_message);

    return formatted_log_message;
}

} // namespace modula.
