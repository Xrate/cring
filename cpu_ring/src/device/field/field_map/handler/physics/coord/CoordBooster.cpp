#include "CoordBooster.h"
#include "CoordTransformation.h"

#include <cmath>
#include <device/field/field_map/common/primitives.h>

using namespace physics;

CoordBooster::CoordBooster(const CoordTransformation& t)
: Z(t.Z), X(t.X), angle(t.angle)
{}

Point CoordBooster::convertPoint(Point p) const
{
    double ownX = p.X*cos(angle) - p.Z*sin(angle) + X;
    double ownY = p.Y;
    double ownZ = p.X*sin(angle) + p.Z*cos(angle) + Z;

    return Point{ ownX , ownY, ownZ };
}

Point CoordBooster::rotateField(Point field) const
{
	double ownX = field.X*cos(-angle) - field.Z*sin(-angle);
	double ownY = field.Y;
	double ownZ = field.X*sin(-angle) + field.Z*cos(-angle);

	return Point{ ownX, ownY, ownZ };
}