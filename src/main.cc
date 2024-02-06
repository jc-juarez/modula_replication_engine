// *************************************
// Modula Replication Engine
// Core
// 'main.cc'
// Author: jcjuarez
// *************************************

#include "logger.hh"
#include "modula.hh"
#include "utilities.hh"
#include "system_configuration.hh"

int main(int argc, char** argv)
{
    using namespace modula;

    status_code status = status::success;

    // Command-line arguments for system startup override
    // debug={Debug mode enabled: on} logs={Logs files enabled: on}  directory={Logs files directory: var/log/modula}
    std::vector<std::string> args(argv, argv + argc);
    
    system_configuration modula_system_configuration;

    //
    // Initialize singleton logger for the system.
    //
    logger::initialize(&(modula_system_configuration.m_logger_configuration));

    std::unique_ptr<modula::modula> modula_replication_engine = std::make_unique<modula::modula>(
        status);

    if (status::failed(status))
    {
        throw_exception(std::format("<!> Modula replication engine initialization failed. Status={:#X}.",
            status));
    }

    forever {}
}
