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
    // Determines whether a replication engine exists.
    //
    bool
    replication_engine_exists(
        const std::string& p_directory_name);

    //
    // Returns a reference to a replication engine.
    //
    replication_engine&
    get_replication_engine(
        const std::string& p_directory_name);

    //
    // Returns a reference to the list of replication engines.
    //
    std::unordered_map<std::string, replication_engine>&
    get_replication_engines();

    //
    // Executes a full sync on all replication engines.
    //
    status_code
    execute_full_sync();

private:

    //
    // Parses the initial configuration file into memory
    // and creates the replication engines for the system.
    //
    status_code
    parse_initial_configuration_file_into_memory(
        const std::string& p_configuration_file);

    //
    // Container for holding replication engines. Static for the lifetime of the system.
    //
    //std::unique_ptr<replication_engine[]> m_replication_engines;
    std::unordered_map<std::string, replication_engine> m_replication_engines;

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
