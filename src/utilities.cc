// *************************************
// Modula Replication Engine
// Utilities
// 'utilities.cc'
// Author: jcjuarez
// *************************************

#include "utilities.hh"

#include <fstream>
#include <stdexcept>
#include <filesystem>

namespace modula
{

namespace utilities
{

bool
is_file_descriptor_valid(
    const file_descriptor& p_file_descriptor)
{
    return p_file_descriptor != -1;
}

bool
system_call_failed(
    const int32 p_result)
{
    return p_result == -1;
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

status_code
append_content_to_file(
    const std::string& p_file_path,
    const character* p_content)
{
    std::ofstream file;

    file.open(p_file_path, std::ios_base::app);

    if (!file)
    {
        return status::file_write_failed;
    }

    file << p_content;

    return status::success;
}

uint32
get_file_size(
    const std::string& p_file_path)
{
    uint32 file_size_mib = 0;

    try
    {
        uintmax_t file_size_bytes = std::filesystem::file_size(p_file_path);
        file_size_mib = static_cast<uint32>(file_size_bytes) / (1024u * 1024u);
    }
    catch (const std::filesystem::filesystem_error& exception)
    {
        //
        // Consider a failed retrieval as size of 0 MiB.
        //
    }

    return file_size_mib;
}

} // namespace utilities.

} // namespace modula.
