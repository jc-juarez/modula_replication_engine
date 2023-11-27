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
    const std::wstring& p_name)
{
    if (!std::filesystem::exists(p_name))
    {
        std::filesystem::create_directory(p_name);
    }
}

//
// Checks if the directory is a subdirectory of another directory.
//
bool
directory::is_subdirectory_of(
    const std::wstring& p_comparing_directory)
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
