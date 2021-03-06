﻿#include "PlainConverter.h"

#include <global.h>
#include <beam/Particle.h>
#include <device/common/DeviceGeometry.h>

PlainConverter::PlainConverter(const DeviceGeometry& geometry)
: length(geometry.length),
  nSteps(geometry.nSteps)
{}

Point PlainConverter::toPlain(double X, double Y, size_t iS) const
{
	return Point{ X, Y, getZ(iS) };
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
	Point M = toPlain(p.X, p.Y, iS);
	double norm = sqrt(1 + sqr(p.aX) + sqr(p.aY));
	Point F = { p.p * p.aX / norm, p.p * p.aY / norm, p.p / norm};

	return Vector{ M, F };
}

void PlainConverter::applyNewMomentum(Particle & p, const Vector & m, size_t) const
{
    p.X = m.M.X;
    p.Y = m.M.Y;

	p.aX = m.vec.X / m.vec.Z;
    p.aY = m.vec.Y / m.vec.Z;
}
