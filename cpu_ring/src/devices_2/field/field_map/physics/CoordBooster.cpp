#include "CoordBooster.h"
#include "physics.h"

using namespace physics;

CoordBooster::CoordBooster(double z, double x, double angle)
: Z(z), X(x), angle(angle)
{}

Point CoordBooster::convertPoint(Point p) const
{
	double ownX = p.Z*sin(angle) + p.X*cos(angle) - X;
	double ownY = p.Y;
	double ownZ = p.X*sin(angle) + p.Z*cos(angle) - Z;

	return Point{ ownX , ownY, ownZ };
}
