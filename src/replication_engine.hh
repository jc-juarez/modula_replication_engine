// *************************************
// Modula Replication Engine
// Utilities
// 'replication_engine.hh'
// Author: jcjuarez
// *************************************

#ifndef REPLICATION_ENGINE_
#define REPLICATION_ENGINE_

#include "status.hh"
#include "directory.hh"
#include "thread_pool.hh"
#include "replication_task.hh"

namespace modula
{

//
// Replication engine class for managing directory-level filesystem replication.
//
class replication_engine
{

public:

    //
    // Default constructor for container compatibility.
    //
    replication_engine() = default;

    //
    // Constructor. Initializes the replication engine class.
    //
    replication_engine(
        const directory&& p_source_directory,
        const std::vector<directory>&& m_target_directories,
        std::shared_ptr<thread_pool> p_replication_tasks_thread_pool);

    //
    // Move constructor. Transfers instance ownership.
    //
    replication_engine(
        replication_engine&& p_replication_engine);

    //
    // Directory-level full sync.
    //
    status_code
    execute_full_sync();

    //
    // Enqueues a replication task into the queue for execution.
    //
    status_code
    enqueue_replication_task(
        std::unique_ptr<replication_task>&& p_replication_task);

    //
    // Executes a replication task.
    //
    status_code
    execute_replication_task(
        std::unique_ptr<replication_task>&& p_replication_task);

    //
    // Returns the name of the replication engine, which is the directory name.
    //
    std::string
    get_name() const;

private:

    //
    // Directory-level queue of replication tasks for execution.
    //
    std::queue<std::unique_ptr<replication_task>> m_replication_tasks;

    //
    // Thread pool for handling concurrent directory replication.
    // This is shared among all replication engines in the system.
    //
    std::shared_ptr<thread_pool> m_replication_tasks_thread_pool;

    //
    // Directory component of the replication engine.
    // Replication engines are uniquely identified by their source directory names.
    //
    directory m_source_directory;

    //
    // Container for all target directories associated to the replication engine.
    //
    std::vector<directory> m_target_directories;
    
};

} // namespace modula.

#endif
