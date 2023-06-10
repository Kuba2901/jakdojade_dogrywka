#pragma once
#include "custom_string.h"
#include "linked_list.h"

struct KeyValue {
    CustomString name;
    CityLinkedList cityLinkedList;
    bool filled;

    KeyValue(CustomString name_, CityLinkedList cityLinkedList_): name(name_), cityLinkedList(cityLinkedList_), filled(true) {}
    KeyValue() {
        this->cityLinkedList.head = nullptr;
        this->filled = false;
    }
};