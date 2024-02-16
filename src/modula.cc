// *************************************
// Modula Replication Engine
// Core
// 'modula.cc'
// Author: jcjuarez
// *************************************

#include "logger.hh"
#include "modula.hh"
#include "directory.hh"

namespace modula
{

//
// Initial state for the stop execution member.
//
bool modula::s_stop_execution = false;

modula::modula(
    status_code* p_status)
{
    //
    // Initializes all system dependencies.
    //

    // first initialize the replica manager for:
    // Parsing config file and bringing directories into memory.
    // Veifying rules: no multiple source directories, no multiple target directories and no subdirectories in target directories.
    // replication_manager = make(status) => inspect status
    m_replication_manager = std::make_shared<replication_manager>(
        "/home/jcjuarez/mockfile.txt",
        p_status);

    return_if_failed(*p_status)

    m_filesystem_monitor = std::make_unique<filesystem_monitor>(
        m_replication_manager,
        p_status);

    return_if_failed(*p_status)

    logger::log(log_level::info, "Modula replication engine has been successfully initialized.");
}

void
modula::start_engine()
{
    logger::log(log_level::info, "Starting replication task dispatcher thread.");

    m_filesystem_monitor->start_replication_task_dispatcher();
}

void
modula::signal_system_termination_handler(
    int32 p_signal)
{
    logger::log(log_level::info, std::format("Received termination signal '{}'. Stopping system execution.",
        p_signal));

    s_stop_execution = true;
}

} // namespace modula.
