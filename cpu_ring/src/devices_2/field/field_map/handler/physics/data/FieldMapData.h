#pragma once

struct Point;

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

        Point* rawMap;

        Point getFieldInPoint(const Point& p) const;
    };
}