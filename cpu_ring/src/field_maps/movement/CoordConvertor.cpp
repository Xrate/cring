#include "CoordConvertor.h"

CoordConverter::CoordConverter(const double angle, const double length, const size_t nSteps)
: rho(length/angle), theta(angle), n(nSteps)
{
}

inline double CoordConverter::currentAngle(const size_t iS) const
{
    return 0.5 * theta * (2.*iS / n - 1.);
}

physics::Point CoordConverter::CurveToPlain(double X, double Y, const size_t iS) const
{
    double angle = currentAngle(iS);
    double x = xCoordCorrection(angle) + X * cos(angle);
    double y = Y;
    double z = rho * sin(angle) + X * sin(angle);

    return physics::Point{ x, y, z };
}

const physics::Plane CoordConverter::getPlane(const size_t iS) const
{
    double angle = currentAngle(iS);
    double x = xCoordCorrection(angle);
    double xA = 0.5*rho * (1 - cos(0.5*theta));
    double z = rho * sin(angle);

    if (z == 0) return physics::Plane{ 0, 0, 1, 0 };

    double A = -z / (x - xA + rho);
    double B = 0.;
    double C = 1.;
    double D = -z * (rho - xA) / (x - xA + rho);

    return physics::Plane{ A, B, C, D };
}

const Vector CoordConverter::getMomentum(const Particle& p, const size_t iS) const
{
    Point M = CurveToPlain(p.X, p.Y, iS);
    double angle = currentAngle(iS);

    double alf_X = atan(p.aX) - angle;
    double alf_Y = atan(p.aY);

    Field F = { p.p * cos(alf_Y) * sin(alf_X), p.p * sin(alf_Y), p.p * cos(alf_Y) * cos(alf_X) };
    return Vector{ M, F };
}

void CoordConverter::updateParticle(Particle& p, const Vector& newMomentum, const size_t iS)
{
    double angle = currentAngle(iS);
    p.X = (newMomentum.M.X - xCoordCorrection(angle)) / cos(angle);
    p.Y = newMomentum.M.Y;

    p.aX = tan(atan(newMomentum.vec.X / newMomentum.vec.Z) + angle);
    p.aY = tan(asin(newMomentum.vec.Y / abs(newMomentum.vec)));
}

inline double CoordConverter::xCoordCorrection(double angle) const
{
    return rho * (cos(angle) - 0.5*(1. + cos(0.5*theta)));
}
