// *************************************
// Modula Replication Engine
// Core
// 'modula.cc'
// Author: jcjuarez
// *************************************

#include "logger.hh"
#include "modula.hh"
#include "directory.hh"

#include <cstring>
#include <csignal>
#include <sys/signalfd.h>

namespace modula
{

//
// Initial state for the stop system execution configuration.
//
bool modula::s_stop_system_execution = false;

modula::modula(
    status_code* p_status)
{
    //
    // Initializes all system dependencies.
    //
    file_descriptor termination_signals_handle;
    std::tie(*p_status, termination_signals_handle) = create_termination_signals_handle();

    return_if_failed(*p_status)

    // first initialize the replica manager for:
    // Parsing config file and bringing directories into memory.
    // Veifying rules: no multiple source directories, no multiple target directories and no subdirectories in target directories.
    // replication_manager = make(status) => inspect status
    m_replication_manager = std::make_shared<replication_manager>(
        "/home/jcjuarez/mockfile.txt",
        p_status);

    return_if_failed(*p_status)

    m_filesystem_monitor = std::make_unique<filesystem_monitor>(
        termination_signals_handle,
        m_replication_manager,
        p_status);

    return_if_failed(*p_status)

    logger::log(log_level::info, "Modula replication engine has been successfully initialized.");
}

void
modula::start_engine()
{
    logger::log(log_level::info, "Starting kernel events offloader thread.");

    m_filesystem_monitor->start_kernel_events_offloader();

    logger::log(log_level::info, "Finishing kernel events offloader thread.");
}

void
modula::invoke_system_termination_handler()
{
    if (s_stop_system_execution)
    {
        return;
    }

    logger::log(log_level::info, "Received termination signal. Stopping system execution.");

    s_stop_system_execution = true;
}

bool
modula::stop_system_execution()
{
    return s_stop_system_execution;
}

std::tuple<status_code, file_descriptor>
modula::create_termination_signals_handle()
{
    status_code status = status::success;
    sigset_t termination_signals_mask;
    sigemptyset(&termination_signals_mask);

    //
    // The system handles 'Ctrl-C' and 'kill' commands by itself.
    //
    sigaddset(&termination_signals_mask, SIGINT);
    sigaddset(&termination_signals_mask, SIGTERM);

    if (utilities::system_call_failed(sigprocmask(
        SIG_BLOCK,
        &termination_signals_mask,
        nullptr)))
    {
        status = status::termination_signals_blockage_failed;

        logger::log(log_level::critical, std::format("Blockage for termination signals failed. {} (errno {}), Status={:#X}.",
            std::strerror(errno),
            errno,
            status));

        return std::make_tuple(
            status,
            c_invalid_file_descriptor);
    }

    file_descriptor termination_signals_handle = signalfd(
        -1,
        &termination_signals_mask,
        0);

    if (!utilities::is_file_descriptor_valid(termination_signals_handle))
    {
        status = status::file_descriptor_creation_failed;

        logger::log(log_level::critical, std::format("Termination signals file descriptor could not be created. {} (errno {}), Status={:#X}.",
            std::strerror(errno),
            errno,
            status));

        return std::make_tuple(
            status,
            c_invalid_file_descriptor);
    }

    return std::make_tuple(
        status,
        termination_signals_handle);
}

} // namespace modula.
