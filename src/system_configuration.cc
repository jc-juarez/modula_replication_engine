// *************************************
// Modula Replication Engine
// Utilities
// 'system_configuration.cc'
// Author: jcjuarez
// *************************************

#include "system_configuration.hh"

namespace modula
{

logger_configuration::logger_configuration()
    : m_debug_mode_enabled(c_default_debug_mode_enabled),
      m_logs_directory_path(c_default_logs_directory_path)
{}

status_code
system_configuration::parse_command_line_arguments(
    const std::vector<std::string>& p_command_line_arguments)
{




    return status::success;
}

} // namespace modula.
