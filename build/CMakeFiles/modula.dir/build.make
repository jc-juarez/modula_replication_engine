# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jcjuarez/modula

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jcjuarez/modula/build

# Include any dependencies generated for this target.
include CMakeFiles/modula.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/modula.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/modula.dir/flags.make

CMakeFiles/modula.dir/src/main.cc.o: CMakeFiles/modula.dir/flags.make
CMakeFiles/modula.dir/src/main.cc.o: ../src/main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jcjuarez/modula/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/modula.dir/src/main.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/modula.dir/src/main.cc.o -c /home/jcjuarez/modula/src/main.cc

CMakeFiles/modula.dir/src/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/modula.dir/src/main.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jcjuarez/modula/src/main.cc > CMakeFiles/modula.dir/src/main.cc.i

CMakeFiles/modula.dir/src/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/modula.dir/src/main.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jcjuarez/modula/src/main.cc -o CMakeFiles/modula.dir/src/main.cc.s

CMakeFiles/modula.dir/src/modula.cc.o: CMakeFiles/modula.dir/flags.make
CMakeFiles/modula.dir/src/modula.cc.o: ../src/modula.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jcjuarez/modula/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/modula.dir/src/modula.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/modula.dir/src/modula.cc.o -c /home/jcjuarez/modula/src/modula.cc

CMakeFiles/modula.dir/src/modula.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/modula.dir/src/modula.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jcjuarez/modula/src/modula.cc > CMakeFiles/modula.dir/src/modula.cc.i

CMakeFiles/modula.dir/src/modula.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/modula.dir/src/modula.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jcjuarez/modula/src/modula.cc -o CMakeFiles/modula.dir/src/modula.cc.s

CMakeFiles/modula.dir/src/filesystem_monitor.cc.o: CMakeFiles/modula.dir/flags.make
CMakeFiles/modula.dir/src/filesystem_monitor.cc.o: ../src/filesystem_monitor.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jcjuarez/modula/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/modula.dir/src/filesystem_monitor.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/modula.dir/src/filesystem_monitor.cc.o -c /home/jcjuarez/modula/src/filesystem_monitor.cc

CMakeFiles/modula.dir/src/filesystem_monitor.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/modula.dir/src/filesystem_monitor.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jcjuarez/modula/src/filesystem_monitor.cc > CMakeFiles/modula.dir/src/filesystem_monitor.cc.i

CMakeFiles/modula.dir/src/filesystem_monitor.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/modula.dir/src/filesystem_monitor.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jcjuarez/modula/src/filesystem_monitor.cc -o CMakeFiles/modula.dir/src/filesystem_monitor.cc.s

CMakeFiles/modula.dir/src/directory.cc.o: CMakeFiles/modula.dir/flags.make
CMakeFiles/modula.dir/src/directory.cc.o: ../src/directory.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jcjuarez/modula/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/modula.dir/src/directory.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/modula.dir/src/directory.cc.o -c /home/jcjuarez/modula/src/directory.cc

CMakeFiles/modula.dir/src/directory.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/modula.dir/src/directory.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jcjuarez/modula/src/directory.cc > CMakeFiles/modula.dir/src/directory.cc.i

CMakeFiles/modula.dir/src/directory.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/modula.dir/src/directory.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jcjuarez/modula/src/directory.cc -o CMakeFiles/modula.dir/src/directory.cc.s

CMakeFiles/modula.dir/src/logger.cc.o: CMakeFiles/modula.dir/flags.make
CMakeFiles/modula.dir/src/logger.cc.o: ../src/logger.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jcjuarez/modula/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/modula.dir/src/logger.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/modula.dir/src/logger.cc.o -c /home/jcjuarez/modula/src/logger.cc

CMakeFiles/modula.dir/src/logger.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/modula.dir/src/logger.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jcjuarez/modula/src/logger.cc > CMakeFiles/modula.dir/src/logger.cc.i

CMakeFiles/modula.dir/src/logger.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/modula.dir/src/logger.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jcjuarez/modula/src/logger.cc -o CMakeFiles/modula.dir/src/logger.cc.s

CMakeFiles/modula.dir/src/utilities.cc.o: CMakeFiles/modula.dir/flags.make
CMakeFiles/modula.dir/src/utilities.cc.o: ../src/utilities.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jcjuarez/modula/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/modula.dir/src/utilities.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/modula.dir/src/utilities.cc.o -c /home/jcjuarez/modula/src/utilities.cc

CMakeFiles/modula.dir/src/utilities.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/modula.dir/src/utilities.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jcjuarez/modula/src/utilities.cc > CMakeFiles/modula.dir/src/utilities.cc.i

CMakeFiles/modula.dir/src/utilities.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/modula.dir/src/utilities.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jcjuarez/modula/src/utilities.cc -o CMakeFiles/modula.dir/src/utilities.cc.s

CMakeFiles/modula.dir/src/thread_pool.cc.o: CMakeFiles/modula.dir/flags.make
CMakeFiles/modula.dir/src/thread_pool.cc.o: ../src/thread_pool.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jcjuarez/modula/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/modula.dir/src/thread_pool.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/modula.dir/src/thread_pool.cc.o -c /home/jcjuarez/modula/src/thread_pool.cc

CMakeFiles/modula.dir/src/thread_pool.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/modula.dir/src/thread_pool.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jcjuarez/modula/src/thread_pool.cc > CMakeFiles/modula.dir/src/thread_pool.cc.i

CMakeFiles/modula.dir/src/thread_pool.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/modula.dir/src/thread_pool.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jcjuarez/modula/src/thread_pool.cc -o CMakeFiles/modula.dir/src/thread_pool.cc.s

CMakeFiles/modula.dir/src/replication_task.cc.o: CMakeFiles/modula.dir/flags.make
CMakeFiles/modula.dir/src/replication_task.cc.o: ../src/replication_task.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jcjuarez/modula/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/modula.dir/src/replication_task.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/modula.dir/src/replication_task.cc.o -c /home/jcjuarez/modula/src/replication_task.cc

CMakeFiles/modula.dir/src/replication_task.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/modula.dir/src/replication_task.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jcjuarez/modula/src/replication_task.cc > CMakeFiles/modula.dir/src/replication_task.cc.i

CMakeFiles/modula.dir/src/replication_task.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/modula.dir/src/replication_task.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jcjuarez/modula/src/replication_task.cc -o CMakeFiles/modula.dir/src/replication_task.cc.s

CMakeFiles/modula.dir/src/replication_engine.cc.o: CMakeFiles/modula.dir/flags.make
CMakeFiles/modula.dir/src/replication_engine.cc.o: ../src/replication_engine.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jcjuarez/modula/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/modula.dir/src/replication_engine.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/modula.dir/src/replication_engine.cc.o -c /home/jcjuarez/modula/src/replication_engine.cc

CMakeFiles/modula.dir/src/replication_engine.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/modula.dir/src/replication_engine.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jcjuarez/modula/src/replication_engine.cc > CMakeFiles/modula.dir/src/replication_engine.cc.i

CMakeFiles/modula.dir/src/replication_engine.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/modula.dir/src/replication_engine.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jcjuarez/modula/src/replication_engine.cc -o CMakeFiles/modula.dir/src/replication_engine.cc.s

CMakeFiles/modula.dir/src/replication_manager.cc.o: CMakeFiles/modula.dir/flags.make
CMakeFiles/modula.dir/src/replication_manager.cc.o: ../src/replication_manager.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jcjuarez/modula/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/modula.dir/src/replication_manager.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/modula.dir/src/replication_manager.cc.o -c /home/jcjuarez/modula/src/replication_manager.cc

CMakeFiles/modula.dir/src/replication_manager.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/modula.dir/src/replication_manager.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jcjuarez/modula/src/replication_manager.cc > CMakeFiles/modula.dir/src/replication_manager.cc.i

CMakeFiles/modula.dir/src/replication_manager.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/modula.dir/src/replication_manager.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jcjuarez/modula/src/replication_manager.cc -o CMakeFiles/modula.dir/src/replication_manager.cc.s

CMakeFiles/modula.dir/src/system_configuration.cc.o: CMakeFiles/modula.dir/flags.make
CMakeFiles/modula.dir/src/system_configuration.cc.o: ../src/system_configuration.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jcjuarez/modula/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/modula.dir/src/system_configuration.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/modula.dir/src/system_configuration.cc.o -c /home/jcjuarez/modula/src/system_configuration.cc

CMakeFiles/modula.dir/src/system_configuration.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/modula.dir/src/system_configuration.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jcjuarez/modula/src/system_configuration.cc > CMakeFiles/modula.dir/src/system_configuration.cc.i

CMakeFiles/modula.dir/src/system_configuration.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/modula.dir/src/system_configuration.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jcjuarez/modula/src/system_configuration.cc -o CMakeFiles/modula.dir/src/system_configuration.cc.s

CMakeFiles/modula.dir/src/timestamp.cc.o: CMakeFiles/modula.dir/flags.make
CMakeFiles/modula.dir/src/timestamp.cc.o: ../src/timestamp.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jcjuarez/modula/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/modula.dir/src/timestamp.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/modula.dir/src/timestamp.cc.o -c /home/jcjuarez/modula/src/timestamp.cc

CMakeFiles/modula.dir/src/timestamp.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/modula.dir/src/timestamp.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jcjuarez/modula/src/timestamp.cc > CMakeFiles/modula.dir/src/timestamp.cc.i

CMakeFiles/modula.dir/src/timestamp.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/modula.dir/src/timestamp.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jcjuarez/modula/src/timestamp.cc -o CMakeFiles/modula.dir/src/timestamp.cc.s

# Object files for target modula
modula_OBJECTS = \
"CMakeFiles/modula.dir/src/main.cc.o" \
"CMakeFiles/modula.dir/src/modula.cc.o" \
"CMakeFiles/modula.dir/src/filesystem_monitor.cc.o" \
"CMakeFiles/modula.dir/src/directory.cc.o" \
"CMakeFiles/modula.dir/src/logger.cc.o" \
"CMakeFiles/modula.dir/src/utilities.cc.o" \
"CMakeFiles/modula.dir/src/thread_pool.cc.o" \
"CMakeFiles/modula.dir/src/replication_task.cc.o" \
"CMakeFiles/modula.dir/src/replication_engine.cc.o" \
"CMakeFiles/modula.dir/src/replication_manager.cc.o" \
"CMakeFiles/modula.dir/src/system_configuration.cc.o" \
"CMakeFiles/modula.dir/src/timestamp.cc.o"

# External object files for target modula
modula_EXTERNAL_OBJECTS =

modula: CMakeFiles/modula.dir/src/main.cc.o
modula: CMakeFiles/modula.dir/src/modula.cc.o
modula: CMakeFiles/modula.dir/src/filesystem_monitor.cc.o
modula: CMakeFiles/modula.dir/src/directory.cc.o
modula: CMakeFiles/modula.dir/src/logger.cc.o
modula: CMakeFiles/modula.dir/src/utilities.cc.o
modula: CMakeFiles/modula.dir/src/thread_pool.cc.o
modula: CMakeFiles/modula.dir/src/replication_task.cc.o
modula: CMakeFiles/modula.dir/src/replication_engine.cc.o
modula: CMakeFiles/modula.dir/src/replication_manager.cc.o
modula: CMakeFiles/modula.dir/src/system_configuration.cc.o
modula: CMakeFiles/modula.dir/src/timestamp.cc.o
modula: CMakeFiles/modula.dir/build.make
modula: CMakeFiles/modula.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jcjuarez/modula/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX executable modula"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/modula.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/modula.dir/build: modula

.PHONY : CMakeFiles/modula.dir/build

CMakeFiles/modula.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/modula.dir/cmake_clean.cmake
.PHONY : CMakeFiles/modula.dir/clean

CMakeFiles/modula.dir/depend:
	cd /home/jcjuarez/modula/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jcjuarez/modula /home/jcjuarez/modula /home/jcjuarez/modula/build /home/jcjuarez/modula/build /home/jcjuarez/modula/build/CMakeFiles/modula.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/modula.dir/depend

