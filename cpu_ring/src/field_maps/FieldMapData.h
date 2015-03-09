#pragma once

#include "field_maps/physics.h"

namespace physics
{
    struct FieldMapData
    {
        size_t numPoints;

        double maxX;
        double maxY;
        double maxZ;

        double stepX;
        double stepY;
        double stepZ;

        Field* rawMap;
    };

    Field getFieldInPoint(const FieldMapData& map, Point p);
}