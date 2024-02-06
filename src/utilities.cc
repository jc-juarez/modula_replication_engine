// *************************************
// Modula Replication Engine
// Utilities
// 'utilities.cc'
// Author: jcjuarez
// *************************************

#include "utilities.hh"

#include <stdexcept>
#include <filesystem>

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
    const std::string&& p_message)
{
    throw std::runtime_error(p_message.c_str());
}

status_code
create_directory(
    const std::string& p_directory_name,
    std::string* p_exception)
{
    try
    {
        std::filesystem::create_directories(p_directory_name);
    }
    catch (const std::filesystem::filesystem_error& exception)
    {
        if (p_exception != nullptr)
        {
            *p_exception = exception.what();
        }

        return status::directory_creation_failed;
    }

    return status::success;
}

} // namespace modula.
