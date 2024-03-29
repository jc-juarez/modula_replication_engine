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
#include "replication_task.hh"
#include "replication_manager.hh"
#include "random_identifier_generator.hh"

#include <mutex>
#include <string>
#include <vector>
#include <thread>
#include <memory>
#include <limits>
#include <sys/inotify.h>

namespace modula
{

//
// Lightweight filesystem event interface for deep copies of inotify events
// needed for copying from the internal kernel queue to the user-space queue.
//
struct filesystem_event
{

    //
    // Default constructor.
    //
    filesystem_event();

    //
    // Watch descriptor for the directory associated with the filesystem object to replicate.
    //
    file_descriptor m_watch_descriptor;

    //
    // Replication action to be performed.
    //
    replication_action m_replication_action;

    //
    // Dynamic-size name field for the filesystem object of the event.
    //
    std::string m_filesystem_object_name;

};

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
        const file_descriptor p_termination_signals_handle,
        std::shared_ptr<replication_manager> p_replication_manager,
        status_code* p_status);

    //
    // Destructor. Closes all epoll related file descriptors and general cleanup.
    //
    ~filesystem_monitor();

    //
    // Starts the filesystem monitor kernel events offloader thread.
    //
    void
    start_kernel_events_offloader();

private:

    //
    // Filesystem monitor thread that dispatches replication tasks based
    // on the filesystem events received from the kernel events offloader.
    // Polling-and-batching mechanism is used to avoid contention from mutual exclusion.
    //
    void
    replication_tasks_dispatcher();

    //
    // Thread pool for replication task dispatcher threads.
    //
    std::unique_ptr<thread_pool> m_dispatcher_thread_pool;

    //
    // Replication manager handle.
    //
    std::shared_ptr<replication_manager> m_replication_manager;

    //
    // Filesystem events queue for holding offloaded events.
    //
    std::queue<filesystem_event> m_filesystem_events_queue;

    //
    // Lock for synchronizing access to the filesystem events queue.
    //
    std::mutex m_filesystem_events_queue_lock;

    //
    // Random identifier generator for the replication tasks dispatcher.
    //
    random_identifier_generator m_random_identifier_generator;

    //
    // File descriptor handle for the epoll instance.
    //
    file_descriptor m_epoll_handle;

    //
    // File descriptor handle for the inotify instance.
    //
    file_descriptor m_inotify_handle;

    //
    // Termination signals handle for graceful termination.
    //
    file_descriptor m_termination_signals_handle;

    //
    // Watch descriptors for the watch directories.
    //
    std::vector<file_descriptor> m_watch_descriptors;

    //
    // Replication tasks dispatcher thread handle.
    //
    std::thread m_replication_tasks_dispatcher_thread;

    //
    // Max size for the event buffer of the epoll instance.
    //
    static constexpr uint16 c_epoll_event_buffer_size = 1024u;

    //
    // Number of threads to be used by the dispatcher thread pool.
    //
    static constexpr uint16 c_dispatcher_thread_pool_size = 200u;

    //
    // Max size in bytes for the read event buffer of the inotify instance.
    //
    static constexpr uint16 c_read_event_buffer_size = 8192u;

    //
    // Max number of fetched filesystem events for batch-processing.
    //
    static constexpr uint16 c_max_number_fetched_filesystem_events = std::numeric_limits<uint16>::max();

    //
    // Replication tasks dispatcher polling sleep duration in milliseconds.
    //
    static constexpr uint8 c_replication_tasks_dispatcher_polling_sleep_ms = 1u;
    
};

} // namespace modula.

#endif
