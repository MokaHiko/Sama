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

    ~TSQueue()
    {
        Clear();
    }

    void Push(const T& item)
    {
        std::scoped_lock lock(m_queue_mutex);
        m_queue.push(item);
    }

    const T& Front()
    {
        std::scoped_lock lock(m_queue_mutex);

        return m_queue.front();
    }

    const T& Back()
    {
        std::scoped_lock lock(m_queue_mutex);
        return m_queue.back();
    }

    void PushBack(const T& item)
    {
        std::scoped_lock lock(m_queue_mutex);

        return m_queue.push_back(std::move(item));
    }

    void PushFront(const T& item)
    {
        std::scoped_lock lock(m_queue_mutex);

        return m_queue.push_front(std::move(item));
    }

    T PopFront(const T& item)
    {
        std::scoped_lock lock(m_queue_mutex);

        assert(m_queue.size() > 0 && "Cannot pop from empty queue");
        T end = std::move(m_queue.front());

        m_queue.pop_front();

        return end;
    }

    T PopBack(const T& item)
    {
        std::scoped_lock lock(m_queue_mutex);

        assert(m_queue.size() > 0 && "Cannot pop from empty queue");
        T end = std::move(m_queue.back());

        m_queue.pop_back();

        return end;
    }

    bool Empty()
    {
        std::scoped_lock lock(m_queue_mutex);
        return m_queue.empty();
    }

    size_t Size()
    {
        std::scoped_lock lock(m_queue_mutex);
        return m_queue.size();
    }

    void Clear()
    {
        std::scoped_lock lock(m_queue_mutex);
        return m_queue.clear();
    }

private:
    std::mutex m_queue_mutex;  
    std::deque<T> m_queue;
};