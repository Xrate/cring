#pragma once

#include "../global.h"
#include "FieldMapData.h"
#include <map>

class FieldMap
{
public:
	static shared_ptr<const FieldMap> getFieldMap(const string& fileName);

	Field getFieldValue(Point p);
	FieldMap::~FieldMap();
private:
	static map<string, shared_ptr<const FieldMap>> fieldMaps;
	FieldMap(const string& fileName);

	FieldMapData data;
};