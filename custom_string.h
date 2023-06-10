#pragma once
#include "custom_vector.h"

class CustomString
{

private:
    CustomVector<char> data;

    friend std::istream& operator>>(std::istream& input, CustomString& customString)
    {
        std::string temp;
        input >> temp;
        customString = CustomString(temp.c_str());
        return input;
    }

public:
    // Default constructor
    CustomString() = default;

    // Constructor with a C-style string
    CustomString(const char* str)
    {
        size_t length = 0;
        while (str[length] != '\0')
        {
            ++length;
        }
        data.reserve(length);
        for (size_t i = 0; i < length; ++i)
        {
            data.push_back(str[i]);
        }
    }

    // Copy constructor
    CustomString(const CustomString& other) : data(other.data) {}

    // Move constructora
    CustomString(CustomString&& other) noexcept : data(std::move(other.data)) {}

    // Destructor
    ~CustomString() {}

    // Assignment operator
    CustomString& operator=(const CustomString& other)
    {
        if (this != &other)
        {
            data = other.data;
        }
        return *this;
    }

    // Move assignment operator
    CustomString& operator=(CustomString&& other) noexcept
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
    const char* c_str()
    {
        // Add a null terminator to the end of the CustomVector data
        data.push_back('\0');
        // Get the pointer to the data and remove the null terminator
        const char* str = data.getData();
        data.pop_back();
        return str;
    }

    // Append a single character to the current string
    CustomString& append(char ch)
    {
        data.push_back(ch);
        return *this;
    }

    void clear() {
        for (int i = 0; i < this->data.getSize(); ++i) {
            this->data.pop_back();
        }
    }

    size_t toHash()
    {
        size_t hash = 0;
        size_t prime = 31;  // A prime number used for better distribution

        for (int i = 0; i < this->data.getSize(); ++i) {
            hash ^= (this->data[i] + prime);
        }

        return hash;
    }
};
