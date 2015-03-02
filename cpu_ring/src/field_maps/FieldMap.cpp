#include "FieldMap.h"
#include <fstream>
#include <sstream>

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
	FILE* file;
	if (NULL == fopen_s(&file, fileName.c_str(), "r"))
		throw exception(("File " + fileName + " cannot be found").c_str());

	fscanf_s(file, "%lf %lf %lf %lf %lf %lf", &maxX, &maxY, &maxZ, &stepX, &stepY, &stepZ);
	numPoints = static_cast<size_t>((2 * maxX / stepX + 1) * (2 * maxY / stepY + 1) * (2 * maxZ / stepZ + 1));

	rawMap = new Field[numPoints];

	for (size_t row = 0; row < numPoints; ++row)
	{
		double tmp;
		double Bx, By, Bz;
		fscanf_s(file, "%lf %lf %lf %lf %lf %lf", &tmp, &tmp, &tmp, &Bx, &By, &Bz);
		rawMap[row] = { Bx, By, Bz };
	}
}

FieldMap::~FieldMap()
{
	if (rawMap != nullptr)
	{
		delete[] rawMap;
		rawMap = nullptr;
	}
}