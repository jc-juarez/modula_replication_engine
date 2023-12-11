// *************************************
// Modula Replication Engine
// Utilities
// 'directory.cc'
// Author: jcjuarez
// *************************************

#include <filesystem>

#include "directory.hh"

namespace modula
{

directory::directory(
    const std::string& p_name,
    const bool is_target_directory) :
    m_name(p_name)
{
    if (is_target_directory &&
        !std::filesystem::exists(p_name))
    {
        std::filesystem::create_directory(p_name);
    }
}

directory::directory(
    const directory& p_directory) :
    m_name(p_directory.m_name)
{}

directory::directory(
    const directory&& p_directory) :
    m_name(std::move(p_directory.m_name))
{}

std::string
directory::get_name() const
{
    return m_name;
}

bool
directory::is_subdirectory_of(
    const std::string& p_comparing_directory)
{
    //
    // Resolve symbolic links or other possible relative paths.
    //
    std::filesystem::path canonical_subdirectory = std::filesystem::canonical(m_name);
    std::filesystem::path canonical_comparing_directory = std::filesystem::canonical(p_comparing_directory);

    std::filesystem::path::iterator canonical_subdirectory_iterator = canonical_subdirectory.begin();
    std::filesystem::path::iterator canonical_comparing_directory_iterator = canonical_comparing_directory.begin();

    while (canonical_comparing_directory_iterator != canonical_comparing_directory.end() &&
        canonical_subdirectory_iterator != canonical_subdirectory.end())
    {
        if (*canonical_subdirectory_iterator != *canonical_comparing_directory_iterator)
        {
            //
            // They differ in their path components, not a subdirectory.
            //
            return false;
        }

        ++canonical_comparing_directory_iterator;
        ++canonical_subdirectory_iterator;
    }

    //
    // If the comparing directory is out of bounds, then it is a subdirectory.
    //
    return canonical_comparing_directory_iterator == canonical_comparing_directory.end();
}

} // namespace modula.
