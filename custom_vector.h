#pragma once
#include <iostream>

template <typename T>
class JakDojadeVector
{
private:
    T *data;
    size_t vectorCapacity;
    size_t vectorSize;

public:
    JakDojadeVector() : data(nullptr), vectorCapacity(0), vectorSize(0) {}

    void pushToVector(const T &value)
    {
        if (vectorSize >= vectorCapacity)
        {
            size_t newCapacity = vectorCapacity == 0 ? 1 : vectorCapacity * 2;
            reserveCapacity(newCapacity);
        }

        data[vectorSize++] = value;
    }

    void popBackVector()
    {
        if (vectorSize > 0)
        {
            --vectorSize;
        }
    }
//
    T &operator[](size_t index)
    {
        return data[index];
    }

    const T &operator[](size_t index) const
    {
        return data[index];
    }

    size_t getSize() const
    {
        return vectorSize;
    }

    size_t getCapacity() const
    {
        return vectorCapacity;
    }

    void reserveCapacity(size_t newCapacity)
    {
        if (newCapacity <= vectorCapacity)
        {
            return;
        }

        T *newData = new T[newCapacity];
        for (size_t i = 0; i < vectorSize; ++i)
        {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        vectorCapacity = newCapacity;
    }

    T* getData() {
        return this->data;
    }

    void popFrontVector()
    {
        if (vectorSize > 0)
        {
            for (size_t i = 0; i < vectorSize - 1; ++i)
            {
                data[i] = data[i + 1];
            }

            // Decrement vector size
            --vectorSize;
        }
    }

    void resizeVector(size_t newSize)
    {
        if (newSize < vectorSize)
        {
            vectorSize = newSize;
        }
        else if (newSize > vectorSize)
        {
            if (newSize > vectorCapacity)
            {
                size_t newCapacity = newSize;
                reserveCapacity(newCapacity);
            }
            for (size_t i = vectorSize; i < newSize; ++i)
            {
                data[i] = T();
            }
            vectorSize = newSize;
        }
    }
};
