#pragma once

#include "ints.h"
#include "result.h"

template<typename T, usize QueueSize>
class StackQueue {
public:
    StackQueue() = default;
    StackQueue(const StackQueue&) = default;

    bool Push(const T& elem) {
        if (m_count >= QueueSize) {
            return false;
        }

        m_buffer[m_tail++] = elem;
        if (m_tail == QueueSize) m_tail = 0;
        m_count++;
        return true;
    }
    Result<T> Pop() {
        if (m_count == 0)
            return Error("Queue is empty.");
        m_count--;

        T retval = m_buffer[m_head++];
        if (m_head == QueueSize) m_head = 0;
        return retval;
    }
    Result<T> Peek() const {
        if (m_count == 0)
            return Error("Not enough elements in queue");
        return m_buffer[m_head];
    }
    usize Size() const {
        return QueueSize;
    }
private:
    T m_buffer[QueueSize];
    i32 m_head  = 0;
    i32 m_tail  = 0;
    i32 m_count = 0;
};

