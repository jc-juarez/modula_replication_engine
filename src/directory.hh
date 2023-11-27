// *************************************
// Modula Replication Engine
// Utilities
// 'directory.hh'
// Author: jcjuarez
// *************************************

#ifndef DIRECTORY_
#define DIRECTORY_

#include <string>

namespace modula
{

//
// Directory class for high-level representation of the filesystem component.
//
class directory
{

public:

    //
    // Constructor. Initializes directory class.
    //
    directory(
        const std::wstring& p_name);

    //
    // Checks if the directory is a subdirectory of another directory.
    //
    bool
    is_subdirectory_of(
        const std::wstring& p_comparing_directory);

private:

    //
    // Name of the directory.
    //
    std::wstring m_name;
    
};

} // namespace modula.

#endif
