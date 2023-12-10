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
    replication_action p_replication_action,
    const std::string& p_file_name) :
    m_replication_action(p_replication_action),
    m_file_name(p_file_name)
{}

replication_action
replication_task::get_replication_action() const
{
    return m_replication_action;
}

std::string
replication_task::get_file_name() const
{
    return m_file_name;
}

} // namespace modula.
