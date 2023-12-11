// *************************************
// Modula Replication Engine
// Utilities
// 'replication_engine.hh'
// Author: jcjuarez
// *************************************

#ifndef REPLICATION_ENGINE_
#define REPLICATION_ENGINE_

#include "status.hh"

namespace modula
{

//
// Replication engine class for managing directory-level filesystem replication.
//
class directory;
class thread_pool;
class replication_engine
{

public:

    //
    // Constructor. Initializes the replication engine class.
    //
    replication_engine(
        const directory&& p_directory,
        thread_pool& p_thread_pool);

    //
    // Initial directory full sync.
    //
    status_code
    initial_sync();

private:

    //
    // Directory-level queue of replication tasks for execution.
    //
    // std::queue<replication_task> m_replication_tasks;

    //
    // Thread pool for handling concurrent directory replication.
    // This is shared among all replication engines in the system.
    //
    thread_pool m_thread_pool;

    //
    // Directory component of the replication engine.
    //
    directory m_directory;
    
};

} // namespace modula.

#endif
