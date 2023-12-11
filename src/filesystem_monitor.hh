// *************************************
// Modula Replication Engine
// Core
// 'filesystem_monitor.hh'
// Author: jcjuarez
// *************************************

#ifndef FILESYSTEM_MONITOR_
#define FILESYSTEM_MONITOR_

#include "status.hh"
#include "utilities.hh"
#include "thread_pool.hh"
#include "replication_manager.hh"

#include <string>
#include <vector>
#include <memory>

namespace modula
{

class directory;

//
// Filesystem monitor class for managing filesystem events.
//
class filesystem_monitor
{

public:

    //
    // Constructor. Initializes the filesystem monitor class.
    //
    filesystem_monitor(
        std::shared_ptr<replication_manager> p_replication_manager,
        status_code& p_status);

    //
    // Destructor. Closes inotify related file descriptors.
    //
    ~filesystem_monitor();

    //
    // Starts the filesystem monitor dispatcher thread.
    //
    status_code
    start_replication_task_dispatcher();

    //
    // Filesystem monitor thread that dispatches filesystem events.
    //
    void
    replication_task_dispatcher();

private:

    //
    // Thread pool for replication task dispatcher threads.
    //
    std::unique_ptr<thread_pool> m_dispatcher_thread_pool;

    //
    // Replication manager handle.
    //
    std::shared_ptr<replication_manager> m_replication_manager;

    //
    // File descriptor handle for the inotify instance.
    //
    file_descriptor m_inotify_handle;

    //
    // Watch descriptors for the watch directories.
    //
    std::vector<file_descriptor> m_watch_descriptors;

    //
    // Max size for the read event buffer of the inotify instance.
    //
    static constexpr uint16 c_read_event_buffer_size = 8192u;

    //
    // Number of threads to be used by the dispatcher thread pool.
    //
    static constexpr uint16 c_dispatcher_thread_pool_size = 200u;

    //
    // Read event buffer of the inotify instance.
    //
    byte m_read_event_buffer[c_read_event_buffer_size];
    
};

} // namespace modula.

#endif
