// *************************************
// Modula Replication Engine
// Utilities
// 'logger.cc'
// Author: jcjuarez
// *************************************

#include "logger.hh"
#include "system_configuration.hh"

#include <iostream>

namespace modula
{

bool logger::s_initialized = false;

logger::logger(
    const logger_configuration* p_logger_configuration)
{
    if (p_logger_configuration != nullptr)
    {
        m_debug_mode_enabled = p_logger_configuration->m_debug_mode_enabled;
        m_logs_directory = p_logger_configuration->m_logs_directory;
    }
}

void
logger::log_message(
    const log_level& p_log_level,
    const std::string&& p_string)
{
    std::lock_guard<std::mutex> lock(m_lock);

    std::cout << p_string.c_str() << std::endl;
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
    const std::string&& p_string,
    const logger_configuration* p_logger_configuration)
{
    if (!s_initialized)
    {
        throw_exception(std::format("<!> Modula Replication Engine logger has not been yet initialized. Status={:#X}.",
            status::logger_not_initialized));
    }

    static logger logger_singleton_instance(
        p_logger_configuration);

    logger_singleton_instance.log_message(
        p_log_level,
        std::move(p_string));
}

} // namespace modula.
