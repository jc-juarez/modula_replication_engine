// *************************************
// Modula Replication Engine
// Utilities
// 'system_configuration.cc'
// Author: jcjuarez
// *************************************

#include "logger.hh"
#include "system_configuration.hh"

#include <unordered_set>

namespace modula
{

logger_configuration::logger_configuration()
    : m_debug_mode_enabled(system_configuration::c_default_debug_mode_enabled),
      m_logs_directory_path("")
{}

status_code
system_configuration::set_logs_directory_path(
    const std::string& p_logs_directory_path)
{
    if (!p_logs_directory_path.empty())
    {
        m_logger_configuration.m_logs_directory_path = p_logs_directory_path;

        return status::success;
    }

    const character* home_environment_variable = std::getenv(c_default_logs_directory_environment_variable);

    if (home_environment_variable == nullptr)
    {
        logger::log_error_fallback(std::format("<!> Modula replication engine system configuration could not access the '{}' environment variable.\n",
            c_default_logs_directory_environment_variable).c_str());
        
        return status::environment_variable_access_failed;
    }

    m_logger_configuration.m_logs_directory_path = std::string(home_environment_variable) + "/" + std::string(c_default_logs_directory_name);

    return status::success;
}

system_configuration::system_configuration(
    status_code* p_status,
    const std::vector<std::string>& p_command_line_arguments)
{
    std::string logs_directory_path;

    if (!p_command_line_arguments.empty())
    {
        *p_status = parse_command_line_arguments(
            p_command_line_arguments,
            &logs_directory_path);

        return_if_failed(*p_status)
    }

    //
    // Initialize runtime defined configurations.
    //
    set_logs_directory_path(logs_directory_path);
}

status_code
system_configuration::parse_command_line_arguments(
    const std::vector<std::string>& p_command_line_arguments,
    std::string* p_logs_directory_path)
{
    std::string modula_executable_name = p_command_line_arguments.front();

    //
    // Configurations override is based on flags.
    //
    uint8 flag_indicator_symbol_index = 0;
    uint8 flag_name_index = 1;
    uint8 flag_assignment_symbol_index = 2;
    uint8 flag_value_index = 3;
    uint8 minimum_flag_size = 4;

    const std::unordered_set<character> available_flags
    {
        c_debug_mode_enabled_flag,
        c_logs_directory_flag
    };

    for (const std::string& flag : p_command_line_arguments)
    {
        if (flag == modula_executable_name ||
            flag == c_sudo)
        {
            continue;
        }

        //
        // Care for malformed flags.
        //
        if (flag.size() < minimum_flag_size ||
            flag[flag_indicator_symbol_index] != c_flag_indicator ||
            flag[flag_assignment_symbol_index] != c_flag_assignment)
        {            
            logger::log_error_fallback(std::format("<!> Modula replication engine could not parse the '{}' flag.\n",
                flag.c_str()).c_str());

            return status::malformed_command_line_arguments;
        }

        character flag_name = flag[flag_name_index];

        //
        // Ensure that the provided configuration flag is valid.
        //
        if (available_flags.find(flag_name) == available_flags.end())
        {
            logger::log_error_fallback(std::format("<!> Modula replication engine could not recognize the '{}' flag name.\n",
                flag_name).c_str());

            return status::configuration_flag_not_recognized;
        }

        std::string flag_value = flag.substr(flag_value_index);

        switch (flag_name)
        {
            case c_debug_mode_enabled_flag:
            {
                status_code status = parse_on_off_to_bool(
                    flag_value,
                    &(m_logger_configuration.m_debug_mode_enabled));

                if (status::failed(status))
                {
                    logger::log_error_fallback(std::format("<!> Modula replication engine could not parse the '{}' flag value.\n",
                        flag_value).c_str());

                    return status;
                }

                break;
            }
            case c_logs_directory_flag:
            {
                *p_logs_directory_path = flag_value;

                break;
            }
            default:
            {
                return status::configuration_flag_not_recognized;
            }
        }
    }

    return status::success;
}

status_code
system_configuration::parse_on_off_to_bool(
    const std::string& p_value,
    bool* p_bool)
{
    if (p_value == c_on_value)
    {
        *p_bool = true;

        return status::success;
    }
    else if (p_value == c_off_value)
    {
        *p_bool = false;

        return status::success;
    }

    return status::incorrect_parameters;
}

} // namespace modula.
