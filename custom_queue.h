#pragma once
#include "custom_vector.h"


template <typename T>
class CustomQueue
{
private:
    CustomVector<T> data;

public:
    CustomQueue() = default;

    ~CustomQueue() = default;

    void push(const T& value)
    {
        data.push_back(value);
    }

    void pop()
    {
        if (!empty())
        {
            data.pop_front();
        }
    }

    T& front()
    {
        if (empty())
        {
            throw std::out_of_range("Queue is empty");
        }
        return data[0];
    }

    const T& front() const
    {
        if (empty())
        {
            throw std::out_of_range("Queue is empty");
        }
        return data[0];
    }

    bool empty() const
    {
        return data.getSize() == 0;
    }

    size_t size() const
    {
        return data.getSize();
    }
};
