#include "FieldMapData.h"
#include "physics.h"
#include <map>

// ## PHYSICS ##
using namespace physics;

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

static NearestPointsField getNearestPoints(const FieldMapData& map, Point p)
{
    size_t xSteps = static_cast<size_t>(2 * map.maxX / map.stepX + 1);
    size_t ySteps = static_cast<size_t>(2 * map.maxY / map.stepY + 1);
    size_t zSteps = static_cast<size_t>(2 * map.maxZ / map.stepZ + 1);

    size_t xRow = static_cast<size_t>(p.X / map.stepX + map.maxX / map.stepX);
    size_t yRow = static_cast<size_t>(p.Y / map.stepY + map.maxY / map.stepY);
    size_t zRow = static_cast<size_t>(p.Z / map.stepZ + map.maxZ / map.stepZ);

    if (xRow < 0 || xRow >= xSteps - 1 || yRow < 0 || yRow >= ySteps - 1 || zRow < 0 || zRow >= zSteps - 1)
        throw exception("Particle now is out of bending area");

    NearestPointsField np;

    np.xyz = map.rawMap[zRow + yRow * zSteps + xRow * ySteps*zSteps];
    np.Xyz = map.rawMap[zRow + yRow * zSteps + (xRow + 1) * ySteps*zSteps];
    np.xYz = map.rawMap[zRow + (yRow + 1) * zSteps + xRow * ySteps*zSteps];
    np.xyZ = map.rawMap[(zRow + 1) + yRow * zSteps + xRow * ySteps*zSteps];
    np.XYz = map.rawMap[zRow + (yRow + 1) * zSteps + (xRow + 1) * ySteps*zSteps];
    np.xYZ = map.rawMap[(zRow + 1) + (yRow + 1) * zSteps + xRow * ySteps*zSteps];
    np.XyZ = map.rawMap[(zRow + 1) + yRow * zSteps + (xRow + 1) * ySteps*zSteps];
    np.XYZ = map.rawMap[(zRow + 1) + (yRow + 1) * zSteps + (xRow + 1) * ySteps*zSteps];
    np.relative = { (p.X - (xRow*map.stepX - map.maxX)) / map.stepX,
        (p.Y - (yRow*map.stepY - map.maxY)) / map.stepY,
        (p.Z - (zRow*map.stepZ - map.maxZ)) / map.stepZ };
    return np;
}

static Field fitField(const NearestPointsField& np)
{
    double sx = (1 - np.relative.X), sX = np.relative.X;
    Field c00 = np.xyz * sx + np.Xyz * sX;
    Field c01 = np.xyZ * sx + np.XyZ * sX;
    Field c10 = np.xYz * sx + np.XYz * sX;
    Field c11 = np.xYZ * sx + np.XYZ * sX;

    double sy = (1 - np.relative.Y), sY = np.relative.Y;
    Field c0 = c00 * sy + c10 * sY;
    Field c1 = c01 * sy + c11 * sY;

    double sz = (1 - np.relative.Z), sZ = np.relative.Z;
    Field c = c0 * sz + c1 * sZ;

    return c;
}

Field getFieldInPoint(const FieldMapData& map, Point p)
{
    return fitField(getNearestPoints(map, p));
}

static map<string, shared_ptr<const FieldMapData>> fieldMaps;

void FieldMapDataDeleter(FieldMapData* data)
{
    if (data->rawMap != nullptr)
    {
        delete[] data->rawMap;
        data->rawMap = nullptr;
    }
}

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

	data->rawMap = new Field[data->numPoints];

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

shared_ptr<const FieldMapData> physics::getFieldMap(const string& fileName)
{
    auto it = fieldMaps.find(fileName);
    if (it != fieldMaps.end()) return it->second;

    fieldMaps[fileName] = shared_ptr<const FieldMapData>(createFieldMapData(fileName), FieldMapDataDeleter);
    return fieldMaps.at(fileName);
}