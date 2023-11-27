// *************************************
// Modula Replication Engine
// Engine
// 'main.cc'
// Author: jcjuarez
// *************************************

/*
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
*/

#include <iostream>
#include <string>
#include <sys/inotify.h>
#include <unistd.h>
#include <cstdlib>

int main() {
    int fd = inotify_init();
    if (fd < 0) {
        perror("inotify_init");
        return 1;
    }

    // Watch for creation, modification, and deletion in the directory
    int wd = inotify_add_watch(fd, "/home/jcjuarez/source", IN_CREATE | IN_MODIFY | IN_DELETE);
    if (wd == -1) {
        perror("inotify_add_watch");
        return 1;
    }

    const int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];

    while (true) {
        int length = read(fd, buffer, BUFFER_SIZE);
        if (length < 0) {
            perror("read");
            break;
        }

        int i = 0;
        while (i < length) {
            struct inotify_event *event = (struct inotify_event *)&buffer[i];
            if (event->len) {
                if (event->mask & IN_CREATE) {
                    std::cout << "File created: " << event->name << std::endl;
                } else if (event->mask & IN_MODIFY) {
                    std::cout << "File modified: " << event->name << std::endl;
                } else if (event->mask & IN_DELETE) {
                    std::cout << "File deleted: " << event->name << std::endl;
                }

                // Execute rsync for any of these events
                std::string command = "rsync -avz --delete /home/jcjuarez/source/ /home/jcjuarez/destination";
                system(command.c_str());
            }
            i += sizeof(struct inotify_event) + event->len;
        }
    }

    inotify_rm_watch(fd, wd);
    close(fd);
    return 0;
}


