// *************************************
// Modula Replication Engine
// Core
// 'replication_manager.hh'
// Author: jcjuarez
// *************************************

#ifndef REPLICATION_MANAGER_
#define REPLICATION_MANAGER_

#include "status.hh"
#include "thread_pool.hh"
#include "replication_engine.hh"

#include <unordered_map>

namespace modula
{

//
// Replication manager class to manage replication engines.
//
class replication_manager
{

public:

    //
    // Constructor. Initializes the replication manager.
    //
    replication_manager(
        const std::string& p_initial_configuration_file,
        status_code* p_status);

    //
    // Returns a non-mutable reference to the list of replication engines.
    //
    const std::vector<replication_engine>&
    get_replication_engines();

    //
    // Executes a full sync on all replication engines.
    //
    status_code
    execute_full_sync();

    //
    // Appends an entry to the replication engines router.
    // Must be called only from the filesystem monitor side.
    //
    void
    append_entry_to_replication_engines_router(
        file_descriptor p_watch_descriptor,
        uint32 p_replication_engine_index);

    //
    // Replication entry point for replication tasks. Resources
    // ownership is transfered from the filesystem monitor to this method.
    //
    void
    replication_tasks_entry_point(
        const std::string& p_activity_id,
        file_descriptor p_watch_descriptor,
        std::unique_ptr<replication_task>&& p_replication_task);

private:

    //
    // Parses the initial configuration file into memory
    // and creates the replication engines for the system.
    //
    status_code
    parse_initial_configuration_file_into_memory(
        const std::string& p_configuration_file);

    //
    // Sends a replication task to its corresponding replication engine for execution.
    //
    status_code
    send_replication_task(
        file_descriptor p_watch_descriptor,
        std::unique_ptr<replication_task>& p_replication_task);

    //
    // Container for holding replication engines.
    //
    std::vector<replication_engine> m_replication_engines;

    //
    // Map router for replication engines. Maps a watch descriptor to the replication engine index.
    //
    std::unordered_map<file_descriptor, uint32> m_replication_engines_router;

    //
    // Thread pool for executing concurrent replication tasks by replication engines.
    // This is shared across all instances of replication engines present in the system.
    //
    std::shared_ptr<thread_pool> m_replication_tasks_thread_pool;

    //
    // Number of threads to be used by the replication tasks thread pool.
    //
    static constexpr uint16 c_replication_tasks_thread_pool_size = 500u;
    
};

} // namespace modula.

#endif
