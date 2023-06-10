#pragma once
#include <iostream>
#include "custom_string.h"

class CityNode {
public:
    CustomString name;
    int weight;
    CityNode* next;

    CityNode(CustomString name_, int weight_) : name(name_), weight(weight_), next(nullptr) {}
};