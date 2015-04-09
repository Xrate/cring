#pragma once
#include "global.h"
#include <map>

namespace physics
{
    struct Point;
    struct Field;

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

    shared_ptr<const FieldMapData> getFieldMap(const string& fileName);

    Field getFieldInPoint(const FieldMapData& map, Point p);
}