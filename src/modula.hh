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
    // Destructor.
    //
    ~modula();

    //
    // Starts the modula replication engine events offloader.
    //
    void
    start_engine();

    //
    // Alerts all system components the need for stopping execution.
    //
    static
    void
    invoke_system_termination_handler();

    //
    // Getter for the internal stop system execution configuration.
    //
    static
    bool
    stop_system_execution();

private:

    //
    // External signals handler generator for graceful termination. Must be called before
    // spawning any other threads in the system. Async resources in the modula system are handled by  
    // thread pools attached to the main modula handle or detached threads; once the events offloader
    // thread reaches conclusion, all thread pool destructors will lead to a graceful system termination.
    //
    static
    std::tuple<status_code, file_descriptor>
    create_termination_signals_handle();

    //
    // Replication manager handle.
    //
    std::shared_ptr<replication_manager> m_replication_manager;

    //
    // Filesystem monitor handle.
    //
    std::unique_ptr<filesystem_monitor> m_filesystem_monitor;

    //
    // Internal signal to stop the system execution. All indefinitely
    // running system components must listen to this configuration setting.
    //
    static
    std::atomic<bool>
    s_stop_system_execution;
    
};

} // namespace modula.

#endif