#pragma once
#include <iostream>
#include "custom_vector.h"

template <typename T>
class CustomPriorityQueue
{
private:
    CustomVector<T> data;

public:
    CustomPriorityQueue() {}

    bool empty() const
    {
        return data.getSize() == 0;
    }

    size_t size() const
    {
        return data.getSize();
    }

    const T& top() const
    {
        if (empty())
        {
            throw std::out_of_range("Priority queue is empty");
        }
        return data[0];
    }

    void push(const T& value)
    {
        data.push_back(value);
        siftUp(data.getSize() - 1);
    }

    void pop()
    {
        if (empty())
        {
            throw std::out_of_range("Priority queue is empty");
        }

        std::swap(data[0], data[data.getSize() - 1]);
        data.pop_back();
        siftDown(0);
    }

private:
    void siftUp(size_t index)
    {
        while (index > 0)
        {
            size_t parentIndex = (index - 1) / 2;
            if (data[index] < data[parentIndex])
            {
                std::swap(data[index], data[parentIndex]);
                index = parentIndex;
            }
            else
            {
                break;
            }
        }
    }

    void siftDown(size_t index)
    {
        size_t leftChildIndex = 2 * index + 1;
        size_t rightChildIndex = 2 * index + 2;
        size_t smallestIndex = index;

        if (leftChildIndex < data.getSize() && data[leftChildIndex] < data[smallestIndex])
        {
            smallestIndex = leftChildIndex;
        }

        if (rightChildIndex < data.getSize() && data[rightChildIndex] < data[smallestIndex])
        {
            smallestIndex = rightChildIndex;
        }

        if (smallestIndex != index)
        {
            std::swap(data[index], data[smallestIndex]);
            siftDown(smallestIndex);
        }
    }
};
