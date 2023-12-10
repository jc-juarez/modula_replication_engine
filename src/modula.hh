// *************************************
// Modula Replication Engine
// Core
// 'modula.hh'
// Author: jcjuarez
// *************************************

#include "filesystem_monitor.hh"

#include <memory>

#ifndef MODULA_
#define MODULA_

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
        status_code& p_status);

    //
    // Initializes all system dependencies.
    //
    status_code
    initialize_dependencies();

private:

    //
    //  Replication manager handle.
    //
    // std::unique_ptr<replication_manager> m_replication_manager;

    //
    //  Filesystem monitor handle.
    //
    std::unique_ptr<filesystem_monitor> m_filesystem_monitor;
    
};

} // namespace modula.

#endif