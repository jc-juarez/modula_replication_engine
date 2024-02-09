// *************************************
// Modula Replication Engine
// Core
// 'modula.cc'
// Author: jcjuarez
// *************************************

#include "modula.hh"
#include "directory.hh"

namespace modula
{

modula::modula(
    status_code* p_status)
{
    *p_status = initialize_dependencies();
}

//
// Initializes all system dependencies.
//
status_code
modula::initialize_dependencies()
{
    status_code status = status::success;

    // first initialize the replica manager for:
    // Parsing config file and bringing directories into memory.
    // Veifying rules: no multiple source directories, no multiple target directories and no subdirectories in target directories.
    // replication_manager = make(status) => inspect status
    m_replication_manager = std::make_shared<replication_manager>(
        "/home/jcjuarez/mockfile.txt",
        status);

    return_status_if_failed(status)

    m_filesystem_monitor = std::make_unique<filesystem_monitor>(
        m_replication_manager,
        status);

    return_status_if_failed(status)

    m_filesystem_monitor->start_replication_task_dispatcher();

    return status;
}   

} // namespace modula.
