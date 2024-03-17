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

    //
    // Number of bytes synchronized and transferred.
    //
    single_precision m_bytes_per_second;

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
    execute_synchronization_task(
        const character* p_target_directory_path,
        std::unique_ptr<replication_task>& p_replication_task);

private:

    //
    // Max size for the reading buffer for the rysnc IPC result.
    //
    static constexpr uint16 c_rsync_result_buffer_size = 4096u;

    //
    // Regex rsync data pattern for synchronization information.
    //
    static constexpr const character* c_rsync_data_pattern = R"(sent (\d+) bytes.*?(\d+(\.\d+)?) bytes/sec)";
    
};

} // namespace modula.

#endif
