#pragma once
#include "custom_vector.h"

class JakDojadeString
{

private:
    JakDojadeVector<char> data;

    friend std::istream& operator>>(std::istream& input, JakDojadeString& customString)
    {
        size_t bufferSize = 100;

        char* buffer = new char[bufferSize];
        input >> buffer;

        customString = JakDojadeString(buffer);

        delete[] buffer; // Deallocate the dynamically allocated memory

        return input;
    }

public:
    // Default constructor
    JakDojadeString() = default;

    // Constructor with a C-style string
    JakDojadeString(const char* str)
    {
        size_t length = 0;
        while (str[length] != '\0')
        {
            ++length;
        }
        data.reserveCapacity(length);
        for (size_t i = 0; i < length; ++i)
        {
            data.pushToVector(str[i]);
        }
    }

    // Copy constructor
    JakDojadeString(const JakDojadeString& other) {
        data.resizeVector(other.length());

        for (int i = 0; i < data.getSize(); ++i) {
            this->data[i] = other[i];
        }

    }

    // Assignment operator
    JakDojadeString& operator=(const JakDojadeString& other)
    {
        if (this != &other)
        {
            data = other.data;
        }
        return *this;
    }

    // Move assignment operator
    JakDojadeString& operator=(JakDojadeString&& other) noexcept
    {
        if (this != &other)
        {
            data = std::move(other.data);
        }
        return *this;
    }

    // Accessor operator[]
    char& operator[](size_t index)
    {
        return data[index];
    }

    // Accessor operator[] for const objects
    const char& operator[](size_t index) const
    {
        return data[index];
    }

    // Get the length of the string
    size_t length() const
    {
        return data.getSize();
    }

    // Convert the string to a C-style string
    const char* CStyle()
    {
        // Add a null terminator to the end of the JakDojadeString data
        data.pushToVector('\0');

        // Get the pointer to the data and remove the null terminator
        const char* str = data.getData();

        data.popBackVector();
        return str;
    }

    // Append a single character to the current string
    JakDojadeString& append(char ch)
    {
        data.pushToVector(ch);
        return *this;
    }

    void clear() {
        while (data.getSize() > 0) {
            data.popBackVector();
        }

        data.popBackVector();
    }

    size_t toHash()
    {
        size_t hash = 0;
        size_t prime = 31;  // A prime number used for better distribution

        for (int i = 0; i < this->data.getSize(); ++i) {
            hash = hash * prime + static_cast<size_t>(data[i]);
        }

        return hash;

    }
};
