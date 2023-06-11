#pragma once
#include "custom_vector.h"


template <typename T>
class JakDojadeQueue
{
private:
    JakDojadeVector<T> data;

public:
    void pushToQueue(const T& value)
    {
        data.pushToVector(value);
    }

    void popFromTheQueue()
    {
        if (!queueEmpty())
        {
            data.popFrontVector();
        }
    }

    T& getFront()
    {
        return data[0];
    }

    bool queueEmpty() const
    {
        return data.getSize() == 0;
    }

    size_t getSize() const
    {
        return data.getSize();
    }
};
