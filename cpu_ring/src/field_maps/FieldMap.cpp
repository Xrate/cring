#include "FieldMap.h"

map<string, shared_ptr<const FieldMap>> FieldMap::fieldMaps;

shared_ptr<const FieldMap> FieldMap::getFieldMap(const string& fileName)
{
	auto it = fieldMaps.find(fileName);
	if (it != fieldMaps.end())
		return it->second;

	fieldMaps[fileName] = shared_ptr<const FieldMap>(new FieldMap(fileName));
	return fieldMaps.at(fileName);
}

FieldMap::FieldMap(const string& fileName)
{
	throw exception("Map logic not implemented");
}
