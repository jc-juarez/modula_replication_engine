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
        const std::vector<directory>&& m_target_directories);

    //
    // Move constructor. Transfers instance ownership.
    //
    replication_engine(
        replication_engine&& p_replication_engine);

    //
    // Attaches the initialized replication tasks thread pool.
    //
    void
    attach_replication_tasks_thread_pool(
        std::shared_ptr<thread_pool> p_replication_tasks_thread_pool);

    //
    // Performs a directory-level full sync.
    //
    status_code
    execute_full_sync();

    //
    // Executes a replication task.
    //
    status_code
    execute_replication_task(
        std::unique_ptr<replication_task>&& p_replication_task);

    //
    // Returns the path for the source directory of the replication engine.
    //
    std::string
    get_source_directory_path() const;

private:

    //
    // Thread pool for handling concurrent directory replication.
    // This is shared among all replication engines in the system.
    //
    std::shared_ptr<thread_pool> m_replication_tasks_thread_pool;

    //
    // Directory component of the replication engine.
    // Replication engines are uniquely identified by their source directory name.
    //
    directory m_source_directory;

    //
    // Container for all target directories associated to the replication engine.
    //
    std::vector<directory> m_target_directories;
    
};

} // namespace modula.

#endif
