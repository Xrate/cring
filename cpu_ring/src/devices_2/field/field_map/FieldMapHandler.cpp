#include "FieldMapHandler.h"
#include "physics/FieldMapData.h"
#include "physics/CoordBooster.h"
#include <devices_2/common/DeviceGeometry.h>

using namespace physics;

struct CoordTransformation
{
	double Z;
	double X;
	double angle;
};

static CoordTransformation calculateTransformation(DeviceGeometry curr, DeviceGeometry prev)
{
	CoordTransformation t;
	if (prev.angle == 0. && curr.angle == 0)
	{
		t.Z = (prev.length + curr.length) / 2;
		t.X = 0.;
		t.angle = 0.;
	}
	else if (prev.angle != 0. && curr.angle == 0.)
	{
		auto rho = prev.length / prev.angle;
		auto angle = prev.angle / 2;
		auto dR = rho / 2 * (1 - cos(angle));

		t.Z = curr.length / 2 + rho*cos(angle) - dR*sin(angle);
		t.X = rho*(1 - cos(angle)) + dR*sin(angle);
		t.angle = angle;
	}
	else if (prev.angle == 0. && curr.angle != 0)
	{
		auto rho = curr.length / curr.angle;
		auto angle = curr.angle / 2;
		auto dR = rho / 2 * (1 - cos(angle));
		t.Z = prev.length * cos(angle) / 2 + rho*sin(angle);
		t.X = prev.length * sin(angle) / 2 + dR;
		t.angle = angle;
	}
	else
		throw new exception("Not implemented");
	return t;
}

FieldMapHandler* FieldMapHandler::getPrevHandler(DeviceGeometry curr, DeviceGeometry prev, const string & field_map)
{
	CoordTransformation t = calculateTransformation(curr, prev);
	return new FieldMapHandler(field_map, new CoordBooster(-t.Z, -t.X, t.angle));
}

FieldMapHandler* FieldMapHandler::getCurrHandler(const string & field_map)
{
	CoordTransformation t = { 0., 0., 0. };
	return new FieldMapHandler(field_map, new CoordBooster(t.Z, t.X, t.angle));
}

FieldMapHandler* FieldMapHandler::getNextHandler(DeviceGeometry curr, DeviceGeometry next, const string & field_map)
{
	CoordTransformation t = calculateTransformation(curr, next);
	return new FieldMapHandler(field_map, new CoordBooster(t.Z, -t.X, -t.angle));
}

FieldMapHandler::FieldMapHandler(const string& map_name, 
								 const CoordBooster* converter)
: mapName(map_name), data(getFieldMapData(mapName)), converter(converter)
{}