#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <chrono>       // IWYU pragma: export
#include <thread>       // IWYU pragma: export
#include <mutex>
#include <condition_variable>

namespace scuff {

    class Semaphore {

    private:
        std::mutex mutex;
        std::condition_variable condition_variable;
        size_t count;

    public:
        Semaphore(size_t _count);
        Semaphore(){};

        void setThreads(size_t threads);
        size_t getCount() const;
        void lock();
        void unlock();
    };
}

#endif // SEMAPHORE_H
