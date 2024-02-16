// *************************************
// Modula Replication Engine
// Core
// 'modula.hh'
// Author: jcjuarez
// *************************************

#ifndef MODULA_
#define MODULA_

#include "filesystem_monitor.hh"
#include "replication_manager.hh"

#include <memory>

namespace modula
{

//
// Modula main system class handle.
//
class modula
{

public:

    //
    // Constructor. Initializes all dependencies of the system.
    //
    modula(
        // system options
        status_code* p_status);

    //
    // Starts the modula replication engine task dispatcher.
    //
    void
    start_engine();

    //
    // External signal handler for graceful termination.
    // All async resources in the modula system are handled by thread pools
    // attached to the main modula handle; once the task dispatcher thread reaches
    // conclusion, all thread pool destructors will lead to a graceful termination.
    //
    static
    void
    signal_system_termination_handler(
        int32 p_signal);

    //
    // Internal signal to stop the system execution.
    //
    static
    bool
    s_stop_execution;

private:

    //
    //  Replication manager handle.
    //
    std::shared_ptr<replication_manager> m_replication_manager;

    //
    //  Filesystem monitor handle.
    //
    std::unique_ptr<filesystem_monitor> m_filesystem_monitor;
    
};

} // namespace modula.

#endif