#include "FieldMapData.h"
#include <assert.h>

// ## PHYSICS ##

// small: coord < pointCoord
// big: coord >= pointCoord
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

NearestPointsField getNearestPoints(const FieldMapData& map, Point p)
{
	size_t xSteps = static_cast<size_t>(2 * map.maxX / map.stepX + 1);
	size_t ySteps = static_cast<size_t>(2 * map.maxY / map.stepY + 1);
	size_t zSteps = static_cast<size_t>(2 * map.maxZ / map.stepZ + 1);

	size_t xRow = static_cast<size_t>(p.X / map.stepX + map.maxX / map.stepX);
	size_t yRow = static_cast<size_t>(p.Y / map.stepY + map.maxY / map.stepY);
	size_t zRow = static_cast<size_t>(p.Z / map.stepZ + map.maxZ / map.stepZ);
	
	assert(xRow > 0 && xRow < xSteps);
	assert(yRow > 0 && yRow < ySteps);
	assert(zRow > 0 && zRow < zSteps);

	NearestPointsField np;

	np.xyz = map.rawMap[zRow     +     yRow * ySteps +     xRow * xSteps*ySteps];
	np.Xyz = map.rawMap[zRow     +     yRow * ySteps + (xRow+1) * xSteps*ySteps];
	np.xYz = map.rawMap[zRow     + (yRow+1) * ySteps +     xRow * xSteps*ySteps];
	np.xyZ = map.rawMap[(zRow+1) +     yRow * ySteps +     xRow * xSteps*ySteps];
	np.XYz = map.rawMap[zRow     + (yRow+1) * ySteps + (xRow+1) * xSteps*ySteps];
	np.xYZ = map.rawMap[(zRow+1) + (yRow+1) * ySteps +     xRow * xSteps*ySteps];
	np.XyZ = map.rawMap[(zRow+1) +     yRow * ySteps + (xRow+1) * xSteps*ySteps];
	np.XYZ = map.rawMap[(zRow+1) + (yRow+1) * ySteps + (xRow+1) * xSteps*ySteps];
	np.relative = { xRow*map.stepX - map.maxX, yRow*map.stepY - map.maxY, yRow*map.stepY - map.maxY };
	return np;
}

Field getFieldValue(FieldMapData& map, Point p)
{
	NearestPointsField np = getNearestPoints(map, p);
}