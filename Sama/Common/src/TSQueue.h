#pragma once

#include <deque>
#include <cassert>
#include <thread>
#include <mutex>

template<typename T>
class TSQueue
{
public:
    TSQueue() = default;
    TSQueue(const TSQueue<T>& other) = delete;

    void Push(const T& item)
    {
        m_queue.insert(item);
    }

    const T& Front()
    {
        std::scoped_lock lock(m_queue_mutex);
        return m_queue.front();
    }

    T Pop(const T& item)
    {
        assert(m_queue.size() > 0 && "Cannot pop from empty queue");
        T end = *m_queue.end();

        m_queue.pop();

        return end;
    }

private:
    std::mutex m_queue_mutex;  
    std::deque<T> m_queue;
};