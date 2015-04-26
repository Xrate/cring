#include "PlainConverter.h"
#include <global.h>
#include <devices_2/common/DeviceGeometry.h>
#include <beam/Particle.h>

PlainConverter::PlainConverter(const DeviceGeometry& geometry)
: length(geometry.length),
  nSteps(geometry.nSteps)
{}

Point PlainConverter::toPlain(double X, double Y, size_t iS) const
{
    double z = getZ(iS);
    return Point{ X ,Y, z };
}

double PlainConverter::getZ(size_t iS) const
{
    return 0.5 * length * (2.* iS / nSteps - 1.);
}

Plane PlainConverter::getPlane(size_t iS) const
{
    double z = getZ(iS);
    return Plane{ 0., 0., -1., z };
}

Vector PlainConverter::getMomentum(const Particle & p, size_t iS) const
{
	Point M = Point{ p.X, p.Y, getZ(iS) };
	Point F = { p.p * p.aX, p.p * p.aY, p.p };

	return Vector{ M, F * (1 / (1 + sqr(p.aX) + sqr(p.aY))) };
}

void PlainConverter::applyNewMomentum(Particle & p, const Vector & m, size_t) const
{
    p.X = m.M.X;
    p.Y = m.M.Y;

	p.aX = m.vec.X / m.vec.Z;
    p.aY = m.vec.Y / m.vec.Z;
}
