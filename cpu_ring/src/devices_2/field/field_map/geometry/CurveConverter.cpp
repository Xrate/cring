#include "CurveConverter.h"
#include <global.h>
#include <beam/Particle.h>
#include <devices_2/common/DeviceGeometry.h>

CurveConverter::CurveConverter(const DeviceGeometry& geometry)
: rho(geometry.length/geometry.angle), 
  theta(geometry.angle), 
  nSteps(geometry.nSteps)
{}

Point CurveConverter::toPlain(double X, double Y, size_t iS) const
{
    double angle = getAngle(iS);
	double x = getXCorrection(angle) + X * cos(angle);
	double y = Y;
	double z = rho * sin(angle) + X * sin(angle);

	return Point{ x, y, z };
}

Plane CurveConverter::getPlane(size_t iS) const
{
    double angle = getAngle(iS);

	double x0 = getXCorrection(0.) - rho;
	double zA = rho * sin(angle);
	double xA = getXCorrection(angle);

	double A = -zA / (xA - x0);
	double B = 0.;
	double C = 1.;
	double D = zA * x0 / (xA - x0);

    return Plane{ A, B, C, D };
}

Vector CurveConverter::getMomentum(const Particle & p, size_t iS) const
{
	Point M = toPlain(p.X, p.Y, iS);

	double norm = 1 + sqr(p.aX) + sqr(p.aY);

	double X = p.p * p.aX / norm;
	double Y = p.p * p.aY / norm;
	double Z = p.p / norm;

	double angle = getAngle(iS);
	Point F = { X*cos(angle) - Z*sin(angle), Y, X*sin(angle) + Z*cos(angle) };

	return Vector{ M, F };
}

void CurveConverter::applyNewMomentum(Particle& p, const Vector& m, size_t iS) const
{
    double angle = getAngle(iS);
    p.X = (m.M.X - getXCorrection(angle)) / cos(angle);
    p.Y =  m.M.Y;

	double X = m.vec.X*cos(-angle) - m.vec.Z*sin(-angle);
	double Y = m.vec.Y;
	double Z = m.vec.X*sin(-angle) + m.vec.Z*cos(-angle);

	p.aX = X / Z;
    p.aY = Y / Z;
}

double CurveConverter::getAngle(size_t iS) const
{
	return 0.5 * theta * (2.* iS / nSteps - 1.);
}

double CurveConverter::getXCorrection(double angle) const
{
    return rho * (cos(angle) - 0.5*(1. + cos(0.5*theta)));
}