// *************************************
// Modula Replication Engine
// Core
// 'synchronization_manager.hh'
// Author: jcjuarez
// *************************************

#ifndef SYNCHRONIZATION_MANAGER_
#define SYNCHRONIZATION_MANAGER_

#include "status.hh"
#include "timestamp.hh"

namespace modula
{

struct synchronization_result
{

    //
    // Default constructor.
    //
    synchronization_result();

    //
    // Status of the synchronization action.
    //
    status_code m_status;

    //
    // Timestamp for the synchronization action start time.
    //
    timestamp m_start_timestamp;

    //
    // Timestamp for the synchronization action end time.
    //
    timestamp m_end_timestamp;

    //
    // Number of bytes synchronized and transferred.
    //
    uint32 m_bytes_transferred;

};

//
// Synchronization manager static class to handle filesystem object synchronization.
//
class synchronization_manager
{

    //
    // Static class.
    //
    synchronization_manager() = delete;

public:

    //
    // Executes a filesytem object synchronization through rsync.
    //
    static
    synchronization_result
    execute_synchronization_action(
        const character* p_filesystem_object_path,
        const character* p_target_directory_path);

private:

    //
    // Max size for the reading buffer for the rysnc IPC result.
    //
    static constexpr uint16 c_rsync_result_buffer_size = 4096u;
    
};

} // namespace modula.

#endif
