// *************************************
// Modula Replication Engine
// Utilities
// 'thread_pool.cc'
// Author: jcjuarez
// *************************************

#include <memory>

#include "thread_pool.hh"

namespace modula
{

thread_pool::thread_pool(
    status_code* p_status,
    const uint16 p_number_threads) :
    m_number_threads(p_number_threads),
    m_stop(false)
{
    //
    // Spawn threads for the thread pool.
    //
    try
    {
        for (uint16 thread_index = 0; thread_index < m_number_threads; ++thread_index)
        {
            m_worker_threads.emplace_back(&thread_pool::task_handler, this);

            if (!m_worker_threads.back().joinable())
            {
                *p_status = status::launch_thread_failed;

                return;
            }
        }
    }
    catch (const std::system_error& exception)
    {
        *p_status = status::launch_thread_failed;

        return;
    }
}

thread_pool::~thread_pool()
{
    {
        std::unique_lock<std::mutex> lock(m_lock);
        m_stop = true;
    }

    //
    // Awake all threads and finish them.
    //
    m_condition.notify_all();

    for (std::thread& worker_thread : m_worker_threads)
    {
        worker_thread.join();
    }
}

uint16
thread_pool::get_number_threads() const
{
    return m_number_threads;
}

void
thread_pool::task_handler()
{
    forever
    {
        std::function<void()> task;

        {
            std::unique_lock<std::mutex> lock(m_lock);

            m_condition.wait(lock,
                [this]
                {
                    return this->m_stop ||
                        !this->m_tasks.empty();
                });

            //
            // If the destructor has been invoked, wait for finishing
            // all pending tasks and then terminate the invoked thread.
            //
            if (this->m_stop &&
                this->m_tasks.empty())
            {
                return;
            }

            //
            //  Retrieve and move task from the queue for non-blocking execution.
            //
            task = std::move(this->m_tasks.front());
            this->m_tasks.pop();
        }

        task();
    }      
}

} // namespace modula.
