// *************************************
// Modula Replication Engine
// Utilities
// 'utilities.cc'
// Author: jcjuarez
// *************************************

#include "utilities.hh"

#include <stdexcept>

namespace modula
{

bool
is_file_descriptor_valid(
    const file_descriptor& p_file_descriptor)
{
    return p_file_descriptor != -1;
}

void
throw_exception(
    const std::string&& p_string)
{
    throw std::runtime_error(p_string.c_str());
}

} // namespace modula.
