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
    // Default constructor for container compatibility.
    //
    directory() = default;

    //
    // Constructor. Initializes directory class.
    //
    directory(
        const std::string& p_name,
        const bool is_target_directory = false);

    //
    // Copy constructor.
    //
    directory(
        const directory& p_directory);

    //
    // Move constructor. Transfers instance ownership.
    // 
    directory(
        const directory&& p_directory);

    //
    // Returns the directory name.
    //
    std::string
    get_name() const;

    //
    // Checks if the directory is a subdirectory of another directory.
    //
    bool
    is_subdirectory_of(
        const std::string& p_comparing_directory);

private:

    //
    // Name of the directory.
    //
    std::string m_name;
    
};

} // namespace modula.

#endif
