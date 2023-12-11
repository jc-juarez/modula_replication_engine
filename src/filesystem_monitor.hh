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

#include <string>
#include <vector>

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
        // Reference to the replication manager
        const std::vector<directory>& p_source_directories,
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
    // Replication manager handle.
    //
    // replication_manager& m_replication_manager;

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
    // Read event buffer of the inotify instance.
    //
    byte m_read_event_buffer[c_read_event_buffer_size];
    
};

} // namespace modula.

#endif
