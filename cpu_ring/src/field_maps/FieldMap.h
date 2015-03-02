#pragma once

#include "../global.h"
#include "physics.h"
#include <map>

class FieldMap
{
public:
	static shared_ptr<const FieldMap> getFieldMap(const string& fileName);

	Field getFieldValue(Point p);
	FieldMap::~FieldMap();
private:
	static map<string, shared_ptr<const FieldMap>> fieldMaps;

	size_t numPoints;

	double maxX;
	double maxY;
	double maxZ;

	double stepX;
	double stepY;
	double stepZ;

	FieldMap(const string& fileName);
	Field* rawMap;
};