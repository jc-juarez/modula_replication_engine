// *************************************
// Modula Replication Engine
// Utilities
// 'system_configuration.hh'
// Author: jcjuarez
// *************************************

#ifndef SYSTEM_CONFIGURATION_
#define SYSTEM_CONFIGURATION_

#include "status.hh"
#include "utilities.hh"

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
    // Sets the logs directory path in runtime.
    //
    status_code
    set_logs_directory_path(
        const std::string& p_logs_directory_path);

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
    // Default logs directory name.
    //
    static constexpr character* c_default_logs_directory_name = "modula-logs";

    //
    // Default environment variable used for default logs directory path resolution.
    //
    static constexpr character* c_default_logs_directory_environment_variable = "HOME";

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
    system_configuration(
        const std::vector<std::string>& p_command_line_arguments,
        status_code* p_status);

    //
    // Container for the logger configuration.
    //
    logger_configuration m_logger_configuration;

private:

    //
    // Parses an on/off value into a boolean.
    //
    status_code
    parse_on_off_to_bool(
        const std::string& p_value,
        bool* p_bool);

    //
    // Parses the command line arguments for filling the system configuration class.
    //
    status_code
    parse_command_line_arguments(
        const std::vector<std::string>& p_command_line_arguments,
        std::string* p_logs_directory_path);

    //
    // Sudo text representation for ignoring possible appearance in command line execution.
    //
    static constexpr character* c_sudo = "sudo";

    //
    // Flag indicator symbol.
    //
    static constexpr character c_flag_indicator = '-';

    //
    // Flag assignment symbol.
    //
    static constexpr character c_flag_assignment = '=';

    //
    // Turn on value.
    //
    static constexpr character* c_on_value = "on";

    //
    // Turn off value.
    //
    static constexpr character* c_off_value = "off";

    //
    // Debug mode enabled flag name.
    //
    static constexpr character c_debug_mode_enabled_flag = 'd';

    //
    // Logs directory flag name.
    //
    static constexpr character c_logs_directory_flag = 'l';
    
};

} // namespace modula.

#endif
