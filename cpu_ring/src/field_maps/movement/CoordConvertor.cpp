#include "CoordConvertor.h"

CoordConvertor::CoordConvertor(const double angle, const double length, const size_t nSteps)
: rho(rho), theta(angle), n(nSteps)
{
}

inline double CoordConvertor::currentAngle(const size_t iS) const
{
    return theta / 2. * (2.*iS / n - 1);
}

physics::Point CoordConvertor::CurveToPlain(double X, double Y, const size_t iS) const
{
    double angle = currentAngle(iS);
    double x = rho * (1 - cos(angle)) + X * cos(angle);
    double y = Y;
    double z = rho * sin(angle) + X * sin(angle);

    return physics::Point{ x, y, z };
}

const physics::Plane CoordConvertor::getPlane(const size_t iS) const
{
    double angle = currentAngle(iS);
    double x = rho * (1 - cos(angle));
    double z = rho * sin(angle);

    double A = (z / rho) * (1 - x / rho);
    double B = 0.;
    double C = 1.;
    double D = -z *(1 - x / rho);

    return physics::Plane{ A, B, C, D };
}

const Vector CoordConvertor::getSpeedVector(const Particle& p, const size_t iS) const
{
    Point M = CurveToPlain(p.X, p.Y, iS);
    double angle = currentAngle(iS);

    double alf_X = atan(p.aX) - angle;
    double alf_Y = atan(p.aY);

    Field F = { p.p * sin(alf_X), p.p * sin(alf_Y), p.p * cos(alf_X) };
    return Vector{ M, F };
}