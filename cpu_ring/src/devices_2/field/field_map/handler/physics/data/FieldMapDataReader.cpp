#include "FieldMapDataReader.h"
#include "FieldMapData.h"
#include <devices_2/field/field_map/common/primitives.h>
#include <map>

using namespace physics;

map<string, shared_ptr<const FieldMapData>> FieldMapDataReader::fieldMaps;

static FieldMapData* createFieldMapData(const string& fileName)
{
    auto data = new FieldMapData();
    FILE* file;
    if ((file = fopen(fileName.c_str(), "r")) == nullptr)
        throw exception(("File " + fileName + " cannot be found").c_str());

    fscanf_s(file, "%lf %lf %lf %lf %lf %lf", &(data->maxX), &(data->maxY), &(data->maxZ),
        &(data->stepX), &(data->stepY), &(data->stepZ));
    data->numPoints = static_cast<size_t>((2 * data->maxX / data->stepX + 1)
        * (2 * data->maxY / data->stepY + 1)
        * (2 * data->maxZ / data->stepZ + 1));

    data->rawMap = new Point[data->numPoints];

    for (size_t row = 0; row < data->numPoints; ++row)
    {
        double tmp;
        double Bx, By, Bz;
        fscanf_s(file, "%lf %lf %lf %lf %lf %lf", &tmp, &tmp, &tmp, &Bx, &By, &Bz);
        data->rawMap[row] = { Bx, By, Bz };
    }
    fclose(file);
    return data;
}

shared_ptr<const FieldMapData> FieldMapDataReader::getFieldMapData(const string& fileName)
{
    auto it = fieldMaps.find(fileName);
    if (it == fieldMaps.end()) 
        fieldMaps[fileName] = shared_ptr<FieldMapData>(createFieldMapData(fileName));

    return fieldMaps.at(fileName);
}