// *************************************
// Modula Replication Engine
// Utilities
// 'system_configuration.cc'
// Author: jcjuarez
// *************************************

#include "system_configuration.hh"

#include <cstdlib>

namespace modula
{

logger_configuration::logger_configuration()
    : m_debug_mode_enabled(c_default_debug_mode_enabled)
{
    const character* home_environment_variable = std::getenv("HOME");

    if (home_environment_variable == nullptr)
    {
        throw_exception(std::format("<!> Modula replication engine failed to retrieve the HOME environment variables for the logger initialization. Status={:#X}.",
            status::environment_variable_access_failed));
    }

    m_logs_directory_path = std::string(home_environment_variable) + "/" + std::string(c_default_logs_directory_name);
}

status_code
system_configuration::parse_command_line_arguments(
    const std::vector<std::string>& p_command_line_arguments)
{




    return status::success;
}

} // namespace modula.
