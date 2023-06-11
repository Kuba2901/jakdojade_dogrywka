#pragma once
#include <iostream>
#include "custom_vector.h"
#include "dijkstra_kv.h"

class CustomPriorityQueue
{
private:
    JakDojadeVector<KVPair<int, int>> data;

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

    const KVPair<int, int>& top() const
    {
        if (empty())
        {
            throw std::out_of_range("Priority queue is queueEmpty");
        }
        return data[0];
    }

    void push(const KVPair<int, int>& value)
    {
        data.pushToVector(value);
        siftUp(data.getSize() - 1);
    }

    void pop()
    {
        if (empty())
        {
            throw std::out_of_range("Priority queue is queueEmpty");
        }

        std::swap(data[0], data[data.getSize() - 1]);
        data.popBackVector();
        siftDown(0);
    }

private:
    void siftUp(size_t index)
    {
        while (index > 0)
        {
            size_t parentIndex = (index - 1) / 2;
            if (data[index].second < data[parentIndex].second)
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

        if (leftChildIndex < data.getSize() && data[leftChildIndex].second < data[smallestIndex].second)
        {
            smallestIndex = leftChildIndex;
        }

        if (rightChildIndex < data.getSize() && data[rightChildIndex].second < data[smallestIndex].second)
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
