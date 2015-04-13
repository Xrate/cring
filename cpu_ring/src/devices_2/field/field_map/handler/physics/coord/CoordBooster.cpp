#include "CoordBooster.h"
#include "global.h"
#include "CoordTransformation.h"
#include <devices_2/field/field_map/common/primitives.h>

using namespace physics;

CoordBooster::CoordBooster(const CoordTransformation& t)
: Z(t.Z), X(t.X), angle(t.angle)
{}

Point CoordBooster::convertPoint(Point p) const
{
    double ownX = p.Z*sin(angle) + p.X*cos(angle) - X;
    double ownY = p.Y;
    double ownZ = p.X*sin(angle) + p.Z*cos(angle) - Z;

    return Point{ ownX , ownY, ownZ };
}
