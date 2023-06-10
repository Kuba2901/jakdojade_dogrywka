#pragma once
#include <iostream>

template <typename T>
class CustomVector
{
private:
    T *data;
    size_t capacity;
    size_t size;

public:
    CustomVector() : data(nullptr), capacity(0), size(0) {}

    ~CustomVector()
    {
    }

    void push_back(const T &value)
    {
        if (size >= capacity)
        {
            size_t newCapacity = capacity == 0 ? 1 : capacity * 2;
            reserve(newCapacity);
        }
        data[size++] = value;
    }

    void pop_back()
    {
        if (size > 0)
        {
            --size;
        }
    }

    T &operator[](size_t index)
    {
        if (index >= size)
        {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T &operator[](size_t index) const
    {
        if (index >= size)
        {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    size_t getSize() const
    {
        return size;
    }

    size_t getCapacity() const
    {
        return capacity;
    }

    void reserve(size_t newCapacity)
    {
        if (newCapacity <= capacity)
        {
            return;
        }

        T *newData = new T[newCapacity];
        for (size_t i = 0; i < size; ++i)
        {
            newData[i] = data[i];
        }

//        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

    T* getData() {
        return this->data;
    }

    void pop_front()
    {
        if (size > 0)
        {
            for (size_t i = 0; i < size - 1; ++i)
            {
                data[i] = data[i + 1];
            }
            --size;
        }
    }

    void resize(size_t newSize)
    {
        if (newSize < size)
        {
            size = newSize;
        }
        else if (newSize > size)
        {
            if (newSize > capacity)
            {
                size_t newCapacity = newSize;
                reserve(newCapacity);
            }
            for (size_t i = size; i < newSize; ++i)
            {
                data[i] = T(); // Initialize new elements with default values
            }
            size = newSize;
        }
    }


};
