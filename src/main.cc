// *************************************
// Modula Replication Engine
// Engine
// 'main.cc'
// Author: jcjuarez
// *************************************

#include <iostream>
#include <chrono>

#include "thread_pool.hh"

class my_class
{
public:

    my_class() :
        m_num(100) {}

    int foo()
    {
        std::cout << "foo." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return m_num;
    }

    int m_num;
};

status_code main()
{
    my_class my_class;

    modula::thread_pool thread_pool(10);

    std::optional<std::future<int>> result;

    result = thread_pool.enqueue_task(&my_class::foo, &my_class);

    if (!result.has_value())
    {
        std::cerr << "Task was not enqueued." << std::endl;
        return status::fail;
    }

    std::cout << "Waiting for result." << std::endl;
    std::cout << result.value().get() << std::endl;

    return status::success;
}
