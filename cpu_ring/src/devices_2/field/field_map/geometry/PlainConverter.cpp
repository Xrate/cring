#include "PlainConverter.h"
#include <devices_2/common/DeviceGeometry.h>
#include <beam/Particle.h>

PlainConverter::PlainConverter(const DeviceGeometry& geometry)
: length(geometry.length),
  nSteps(geometry.nSteps)
{}

Point PlainConverter::toPlain(double X, double Y) const
{
    double z = getCurrentZ();
    return Point{ X ,Y, z };
}

double PlainConverter::getCurrentZ() const
{
    return 0.5 * length * (2.* (*dev_step) / nSteps - 1.);
}

double PlainConverter::getNextZ() const
{
    return 0.5 * length * (2.* (*dev_step + 1) / nSteps - 1.);
}

Plane PlainConverter::getNextPlane() const
{
    double z = getNextZ();
    return Plane{ 0., 0., 1., z };
}

Vector PlainConverter::getMomentum(const Particle & p) const
{
    double z = getCurrentZ();
    Point M = Point{ p.X, p.Y, z };

    double alf_X = atan(p.aX);
    double alf_Y = atan(p.aY);

    Point F = { p.p * cos(alf_Y) * sin(alf_X), p.p * sin(alf_Y), p.p * cos(alf_Y) * cos(alf_X) };
    return Vector{ M, F };
}

void PlainConverter::applyNewMomentum(Particle & p, const Vector & m) const
{
    p.X = m.M.X;
    p.Y = m.M.Y;

    p.aX = tan(atan(m.vec.X / m.vec.Z));
    p.aY = tan(asin(m.vec.Y / abs(m.vec)));
}
