// *************************************
// Modula Replication Engine
// Utilities
// 'thread_pool.hh'
// Author: jcjuarez
// *************************************

#ifndef THREAD_POOL_
#define THREAD_POOL_

#include "utilities.hh"

#include <queue>
#include <mutex>
#include <vector>
#include <thread>
#include <future>
#include <optional>
#include <functional>
#include <condition_variable>

namespace modula
{

//
// Thread pool class for handling concurrent tasks through preallocated threads.
//
class thread_pool
{

public:

    //
    // Constructor. Initializes the thread pool.
    //
    thread_pool(
        const uint16 p_number_threads);

    //
    // Destructor. Ensures all threads are finished properly.
    //
    ~thread_pool();

    //
    // Returns the number of threads used by the pool.
    //
    uint16
    get_number_threads() const;

    //
    //  Enqueues a task into the queue.
    //
    template<typename Function, typename... Args>
    std::optional<std::future<typename std::result_of<Function(Args...)>::type>>
    enqueue_task(
        Function&& p_function, Args&&... p_args)
    {
        using return_type = typename std::result_of<Function(Args...)>::type;

        //
        // Package destination function and arguments into a simple task wrapper pointer.
        //
        std::shared_ptr<std::packaged_task<return_type()>> packaged_task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<Function>(p_function), std::forward<Args>(p_args)...));
        
        std::future<return_type> packaged_task_result = packaged_task->get_future();

        {
            std::unique_lock<std::mutex> lock(m_lock);

            //
            // If thread pool is in destruction process fail the enqueue request.
            //
            if (m_stop)
            {
                return std::nullopt;
            }

            m_tasks.emplace(
                [packaged_task]()
                {
                    (*packaged_task)();
                });
        }

        //
        // Notify the task handler of a new task to be executed.
        //
        m_condition.notify_one();
        return std::make_optional<std::future<return_type>>(std::move(packaged_task_result));
    }

private:

    //
    // Handles and executes tasks from the queue.
    //
    void
    task_handler();

    //
    // Worker threads to execute tasks in the pool.
    //
    std::vector<std::thread> m_worker_threads;

    //
    // Queue of packaged tasks to be executed.
    //
    std::queue<std::function<void()>> m_tasks;
    
    //
    // Exclusive lock for synchronizing access to the tasks queue.
    //
    std::mutex m_lock;

    //
    // Condition for awakening worker threads.
    //
    std::condition_variable m_condition;

    //
    // Number of threads to be spawned for the pool.
    //
    uint16 m_number_threads;

    //
    // Flag for stopping worker threads.
    //
    bool m_stop;
    
};

} // namespace modula.

#endif
