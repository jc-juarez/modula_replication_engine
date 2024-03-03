# *************************************
# Modula Replication Engine
# Build
# 'CMakeLists.txt'
# Author: jcjuarez
# *************************************

cmake_minimum_required(VERSION 3.0)

project(ModulaReplicationEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pthread")

set(SOURCE_FILES
    src/main.cc
    src/modula.cc
    src/filesystem_monitor.cc
    src/directory.cc
    src/logger.cc
    src/utilities.cc
    src/thread_pool.cc
    src/replication_task.cc
    src/replication_engine.cc
    src/replication_manager.cc
    src/system_configuration.cc
    src/timestamp.cc
    src/random_identifier_generator)

add_executable(modula ${SOURCE_FILES})
