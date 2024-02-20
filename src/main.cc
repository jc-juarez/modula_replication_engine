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

    std::vector<std::string> command_line_arguments(argv, argv + argc);

    //
    // Initialize the system configuration for all components.
    //
    system_configuration modula_system_configuration(
        &status,
        command_line_arguments);

    if (status::failed(status))
    {
        logger::log_error_fallback(std::format("<!> Modula replication engine initial system configuration failed. Status={:#X}.\n",
            status).c_str());

        return EXIT_FAILURE;
    }

    //
    // Initialize singleton logger for the system.
    //
    status = logger::initialize(modula_system_configuration.m_logger_configuration);

    if (status::failed(status))
    {
        logger::log_error_fallback(std::format("<!> Modula replication engine initial system configuration failed. Status={:#X}.\n",
            status).c_str());

        return EXIT_FAILURE;
    }

    //
    // Initialize the modula replication engine.
    //
    std::unique_ptr<modula::modula> modula_replication_engine = std::make_unique<modula::modula>(
        &status);

    if (status::failed(status))
    {
        logger::log(log_level::critical, std::format("<!> Modula replication engine startup failed. Status={:#X}.",
            status));

        return EXIT_FAILURE;
    }

    //
    // Start the modula replication engine system upon successful initialization.
    //
    modula_replication_engine->start_engine();

    return EXIT_SUCCESS;
}
