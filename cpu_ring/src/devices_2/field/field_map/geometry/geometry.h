#pragma once

#include <devices_2/field/field_map/common/primitives.h>

struct Vector
{
    Point M;
    Point vec;
};

struct Plane
{
	double A;
	double B;
	double C;
    double D;
};