#include "FieldMap.h"
#include "field_maps/movement/CoordConvertor.h"
#include <fstream>

map<string, shared_ptr<const FieldMap>> FieldMap::fieldMaps;

shared_ptr<const FieldMap> FieldMap::getFieldMap(const string& fileName)
{
    auto it = fieldMaps.find(fileName);
    if (it != fieldMaps.end()) return it->second;

    fieldMaps[fileName] = shared_ptr<const FieldMap>(new FieldMap(fileName));
    return fieldMaps.at(fileName);
}

FieldMap::FieldMap(const string& fileName)
{
    FILE* file;
    if ((file = fopen(fileName.c_str(), "r")) == nullptr)
        throw exception(("File " + fileName + " cannot be found").c_str());

    fscanf_s(file, "%lf %lf %lf %lf %lf %lf", &data.maxX, &data.maxY, &data.maxZ, &data.stepX, &data.stepY, &data.stepZ);
    data.numPoints = static_cast<size_t>((2 * data.maxX / data.stepX + 1) 
        * (2 * data.maxY / data.stepY + 1) * (2 * data.maxZ / data.stepZ + 1));

    data.rawMap = new physics::Field[data.numPoints];

    for (size_t row = 0; row < data.numPoints; ++row)
    {
        double tmp;
        double Bx, By, Bz;
        fscanf_s(file, "%lf %lf %lf %lf %lf %lf", &tmp, &tmp, &tmp, &Bx, &By, &Bz);
        data.rawMap[row] = { Bx, By, Bz };
    }
    fclose(file);
}

FieldMap::~FieldMap()
{
    if (data.rawMap != nullptr)
    {
        delete[] data.rawMap;
        data.rawMap = nullptr;
    }
}