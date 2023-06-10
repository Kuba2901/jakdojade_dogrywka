#pragma once

template<typename FirstType, typename SecondType>
struct KVPair {
    FirstType first;
    SecondType second;

    KVPair(FirstType first_, SecondType second_) {
        this->first = first_;
        this->second = second_;
    }

    KVPair() {}
};