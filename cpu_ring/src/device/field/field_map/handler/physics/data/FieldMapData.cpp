#include "FieldMapData.h"

#include <device/field/field_map/common/primitives.h>

// ## PHYSICS ##
using namespace physics;

typedef Point Field;
class OutOfRangeException{};

// small: coord < pointCoord
// big:   coord > pointCoord
struct NearestPointsField
{
    Point relative;
    Field xyz;
    Field Xyz;
    Field xYz;
    Field xyZ;
    Field XYz;
    Field xYZ;
    Field XyZ;
    Field XYZ;
};

static NearestPointsField getNearestPoints(const FieldMapData* map, Point p)
{
	if (p.X < -map->maxX || p.X > map->maxX ||
	    p.Y < -map->maxY || p.Y > map->maxY ||
	    p.Z < -map->maxZ || p.Z > map->maxZ)
			throw OutOfRangeException();

    size_t xRow = static_cast<size_t>(p.X / map->stepX + map->maxX / map->stepX);
    size_t yRow = static_cast<size_t>(p.Y / map->stepY + map->maxY / map->stepY);
    size_t zRow = static_cast<size_t>(p.Z / map->stepZ + map->maxZ / map->stepZ);

    NearestPointsField np;

	size_t xSteps = static_cast<size_t>(2 * map->maxX / map->stepX + 1);
	size_t ySteps = static_cast<size_t>(2 * map->maxY / map->stepY + 1);
	size_t zSteps = static_cast<size_t>(2 * map->maxZ / map->stepZ + 1);

    np.xyz = map->rawMap[      zRow +       yRow * zSteps +       xRow * ySteps*zSteps];
    np.Xyz = map->rawMap[      zRow +       yRow * zSteps + (xRow + 1) * ySteps*zSteps];
    np.xYz = map->rawMap[      zRow + (yRow + 1) * zSteps +       xRow * ySteps*zSteps];
    np.xyZ = map->rawMap[(zRow + 1) +       yRow * zSteps +       xRow * ySteps*zSteps];
    np.XYz = map->rawMap[      zRow + (yRow + 1) * zSteps + (xRow + 1) * ySteps*zSteps];
    np.xYZ = map->rawMap[(zRow + 1) + (yRow + 1) * zSteps +       xRow * ySteps*zSteps];
    np.XyZ = map->rawMap[(zRow + 1) +       yRow * zSteps + (xRow + 1) * ySteps*zSteps];
    np.XYZ = map->rawMap[(zRow + 1) + (yRow + 1) * zSteps + (xRow + 1) * ySteps*zSteps];

    np.relative = { (p.X - (xRow*map->stepX - map->maxX)) / map->stepX,
                    (p.Y - (yRow*map->stepY - map->maxY)) / map->stepY,
                    (p.Z - (zRow*map->stepZ - map->maxZ)) / map->stepZ };
    return np;
}

static Field fitField(const NearestPointsField& np)
{
    double sx = 1 - np.relative.X, sX = np.relative.X;
    Field c00 = np.xyz * sx + np.Xyz * sX;
    Field c01 = np.xyZ * sx + np.XyZ * sX;
    Field c10 = np.xYz * sx + np.XYz * sX;
    Field c11 = np.xYZ * sx + np.XYZ * sX;

    double sy = 1 - np.relative.Y, sY = np.relative.Y;
    Field c0 = c00 * sy + c10 * sY;
    Field c1 = c01 * sy + c11 * sY;

    double sz = 1 - np.relative.Z, sZ = np.relative.Z;
    Field c = c0 * sz + c1 * sZ;

    return c;
}

Field FieldMapData::getFieldInPoint(const Point& p) const
{
    try
    {
		return fitField(getNearestPoints(this, p)) * 0.959;
    }
	catch (OutOfRangeException)
    {
        return Field::Null;
    }
}

FieldMapData::~FieldMapData()
{
    if (rawMap != nullptr)
    {
        delete[] rawMap;
        rawMap = nullptr;
    }
}