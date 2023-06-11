#pragma once
#include "point.h"
#include "custom_string.h"

struct City
{
    JakDojadeString name;
    Point *point;

    City(JakDojadeString name_, Point *point_): name(name_), point(point_) {}
};