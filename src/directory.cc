// *************************************
// Modula Replication Engine
// Core
// 'directory.cc'
// Author: jcjuarez
// *************************************

#include <filesystem>

#include "directory.hh"
#include "utilities.hh"

namespace modula
{

directory::directory(
    const std::string& p_path,
    const bool is_target_directory) :
    m_path(p_path)
{
    if (is_target_directory &&
        !std::filesystem::exists(p_path))
    {
        utilities::create_directory(p_path);
    }
}

directory::directory(
    const directory& p_directory) :
    m_path(p_directory.m_path)
{}

directory::directory(
    const directory&& p_directory) :
    m_path(std::move(p_directory.m_path))
{}

const std::string&
directory::get_path() const
{
    return m_path;
}

bool
directory::is_subdirectory_of(
    const std::string& p_comparing_directory) const
{
    //
    // Resolve symbolic links or other possible relative paths.
    //
    std::filesystem::path canonical_subdirectory = std::filesystem::canonical(m_path);
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

} // pathspace modula.
