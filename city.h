#pragma once
#include "point.h"
#include "custom_string.h"

struct City
{
    CustomString name;
    Point *point;

    City(CustomString name_, Point *point_): name(name_), point(point_) {}
};