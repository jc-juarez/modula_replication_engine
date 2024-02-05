// *************************************
// Modula Replication Engine
// Utilities
// 'system_configuration.hh'
// Author: jcjuarez
// *************************************

#ifndef SYSTEM_CONFIGURATION_
#define SYSTEM_CONFIGURATION_

#include "status.hh"

#include <string>
#include <vector>

namespace modula
{

//
// Logger configuration container for storing logger options.
//
struct logger_configuration
{

    //
    // Constructor. Defaults the values for the logger configuration.
    //
    logger_configuration();

    //
    // Flag for determining whether debug mode is enabled for the logger instance.
    //
    bool m_debug_mode_enabled;

    //
    // Path to the directory for storing logs files.
    //
    std::string m_logs_directory_path;

    //
    // Default debug mode enabled option.
    //
    static constexpr bool c_default_debug_mode_enabled = true;

    //
    // Default logs directory path.
    //
    static constexpr character* c_default_logs_directory_path = "/var/log/modula";
    
};

//
// System configuration container class for storing system-wide preferences.
//
class system_configuration
{

public:

    //
    // Default constructor.
    //
    system_configuration() = default;

    //
    // Parses the command line arguments for filling the system configuration class.
    //
    status_code
    parse_command_line_arguments(
        const std::vector<std::string>& p_command_line_arguments);

private:

    //
    // Container for the logger configuration.
    //
    logger_configuration m_logger_configuration;
    
};

} // namespace modula.

#endif
