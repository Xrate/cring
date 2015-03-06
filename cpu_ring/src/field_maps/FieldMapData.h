#pragma once

#include "physics.h"

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

Field getFieldValue(const FieldMapData& map, Point p);