#include "semaphore.h"

namespace scuff {

    Semaphore::Semaphore(size_t _count) : count(_count)
    {

    }

    void Semaphore::setThreads(size_t threads)
    {
        count = threads;
    }

    size_t Semaphore::getCount() const
    {
        return count;
    }

    void Semaphore::lock()
    {
        std::unique_lock<std::mutex> lock(mutex);
        condition_variable.wait(lock, [this]{
            if (count != 0) { return true; }
            return false;
        });
        --count;
    }

    void Semaphore::unlock()
    {
        std::unique_lock<std::mutex> lock(mutex);
        ++count;
        condition_variable.notify_one();
    }

}
