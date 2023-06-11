#pragma once
#include <iostream>
#include "custom_string.h"

class CityNode {
public:
    JakDojadeString name;
    int weight;
    CityNode* next;

    CityNode(JakDojadeString name_, int weight_) : name(name_), weight(weight_), next(nullptr) {}
};