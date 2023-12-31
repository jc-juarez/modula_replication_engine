// *************************************
// Modula Replication Engine
// Utilities
// 'system_configuration.hh'
// Author: jcjuarez
// *************************************

#ifndef SYSTEM_CONFIGURATION_
#define SYSTEM_CONFIGURATION_

namespace modula
{

//
// Logger configuration container for storing logger options.
//
struct logger_configuration
{

    //
    // Default constructor.
    //
    logger_configuration() = default;

    //
    // Flag for determining whether debug mode is enabled for the logger instance.
    //
    bool m_debug_mode_enabled;

    //
    // Path to the directory for storing logs files.
    //
    std::string m_logs_directory;
    
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

private:

    //
    // Container for the logger configuration
    //
    logger_configuration m_logger_configuration;
    
};

} // namespace modula.

#endif
