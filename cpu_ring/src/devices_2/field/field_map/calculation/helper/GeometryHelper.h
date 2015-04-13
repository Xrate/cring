#pragma once
#include <devices_2/field/field_map/geometry/geometry.h>

class GeometryHelper
{
public:
    static Vector calculateNewMomentum(const Vector& momentum,
                                       const Point&  field   ,
                                       const Plane&  newPlane);
};
