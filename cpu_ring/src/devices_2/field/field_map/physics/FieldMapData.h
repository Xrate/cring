#pragma once
#include "global.h"

namespace physics
{
    struct Point;

    struct FieldMapData
    {
        size_t numPoints;

        double maxX;
        double maxY;
        double maxZ;

        double stepX;
        double stepY;
        double stepZ;

        Point* rawMap;

		Point getFieldInPoint(const Point& p) const;
    };

    shared_ptr<const FieldMapData> getFieldMapData(const string& fileName);
}