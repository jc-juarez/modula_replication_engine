// *************************************
// Modula Replication Engine
// Utilities
// 'filesystem_monitor.hh'
// Author: jcjuarez
// *************************************

#ifndef FILESYSTEM_MONITOR_
#define FILESYSTEM_MONITOR_

namespace modula
{

//
// Filesystem monitor class for managing filesystem events.
//
class filesystem_monitor
{

public:

    //
    // Constructor. Initializes the filesystem monitor class.
    //
    filesystem_monitor();

    //
    // Starts the filesystem monitor thread.
    //
    void
    start();
    
};

} // namespace modula.

#endif
