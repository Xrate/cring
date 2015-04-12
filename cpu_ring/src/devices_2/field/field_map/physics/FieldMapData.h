#pragma once
#include "global.h"

namespace physics
{
    struct Point;
	typedef Point Field;

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

    shared_ptr<const FieldMapData> getFieldMapData(const string& fileName);

    Field getFieldInPoint(const FieldMapData& map, Point p);
}