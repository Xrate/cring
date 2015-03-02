#pragma once

#include "../global.h"
#include <map>

class FieldMap
{
public:
	static shared_ptr<const FieldMap> getFieldMap(const string& fileName);

	double getFieldValue(double x, double y, double z);
private:
	static map<string, shared_ptr<const FieldMap>> fieldMaps;

	FieldMap(const string& fileName);
	double *rawMap;
};