// *************************************
// Modula Replication Engine
// Utilities
// 'replication_task.hh'
// Author: jcjuarez
// *************************************

#ifndef REPLICATION_TASK_
#define REPLICATION_TASK_

#include "utilities.hh"
#include "timestamp.hh"

#include <string>
#include <memory>

namespace modula
{

//
// Replication action enum class.
//
enum class replication_action : uint8
{

    //
    // File needs to be created.
    //
    create = 0,

    //
    // File needs to be modified.
    //
    update = 1,

    //
    // File needs to be removed.
    //
    remove = 2,

    //
    // Full sync needs to be performed over the specified replication engines.
    //
    full_sync = 3,

    //
    // Invalid replication action.
    //
    invalid = 4
    
};

//
// Replication task class for filesystem events generated by the filesystem monitor.
//
class replication_task
{

public:

    //
    // Constructor. Initializes a replication task.
    //
    replication_task(
        const replication_action p_replication_action,
        const std::string& p_filesystem_object_name,
        const std::string& p_activity_id);

    //
    // Gets the replication action of the replication task.
    //
    replication_action
    get_replication_action() const;

    //
    // Gets the filesystem object name.
    //
    const character*
    get_filesystem_object_name() const;

    //
    // Gets the creation time of the replication task.
    //
    timestamp
    get_creation_time() const;

    //
    // Timestamp for the end of the replication task.
    //
    timestamp m_end_timestamp;

    //
    // Timestamp for last encountered error.
    //
    timestamp m_last_error_timestamp;

    //
    // Filesystem object to replicate path.
    //
    std::string m_filesystem_object_path;

    //
    // Activity ID corresponding to the replication task.
    //
    std::string m_activity_id;

private:

    //
    // Replication action of the task.
    //
    replication_action m_replication_action;

    //
    // Name of the filesystem object tied to the task.
    //
    std::string m_filesystem_object_name;

    //
    // Timestamp for the creation of the replication task.
    //
    timestamp m_creation_timestamp;
    
};

} // namespace modula.

#endif
