// *************************************
// Modula Replication Engine
// Utilities
// 'replication_task.cc'
// Author: jcjuarez
// *************************************

#include "replication_task.hh"

namespace modula
{

replication_task::replication_task(
    const replication_action p_replication_action,
    const std::string& p_filesystem_object_name) :
    m_replication_action(p_replication_action),
    m_filesystem_object_name(p_filesystem_object_name),
    m_creation_timestamp(timestamp::get_current_time()),
    m_end_timestamp(timestamp::generate_invalid_timestamp()),
    m_last_error_timestamp(timestamp::generate_invalid_timestamp()),
    m_filesystem_object_path("")
{}

replication_action
replication_task::get_replication_action() const
{
    return m_replication_action;
}

const character*
replication_task::get_filesystem_object_name() const
{
    return m_filesystem_object_name.c_str();
}

timestamp
replication_task::get_creation_time() const
{
    return m_creation_timestamp;
}

} // namespace modula.
