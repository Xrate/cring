#include "CurveConverter.h"
#include <devices_2/field/field_map/physics/physics.h>
#include <beam/Particle.h>
#include <devices_2/common/DeviceGeometry.h>

using namespace physics;

CurveConverter::CurveConverter(DeviceGeometry geometry)
: rho(geometry.length/geometry.angle), 
  theta(geometry.angle), 
  nSteps(geometry.nSteps)
{
}

const Point& CurveConverter::getPlainCoord(double X, double Y) const
{
	double angle = getCurrentAngle();
	return convertToPlain(X,Y, angle);
}

const Plane& CurveConverter::getNextPlane() const
{
	double angle = getNextAngle();
	double x = getXCorrection(angle);
	double xA = 0.5*rho * (1 - cos(0.5*theta));
	double z = rho * sin(angle);

	if (z == 0) return Plane{ 0, 0, 1, 0 };

	double A = -z / (x - xA + rho);
	double B = 0.;
	double C = 1.;
	double D = -z * (rho - xA) / (x - xA + rho);

	return Plane{ A, B, C, D };
}

const Vector& CurveConverter::getMomentum(const Particle & p) const
{
	double angle = getCurrentAngle();
	Point M = convertToPlain(p.X, p.Y, angle);

	double alf_X = atan(p.aX) - angle;
	double alf_Y = atan(p.aY);

	Point F = { p.p * cos(alf_Y) * sin(alf_X), p.p * sin(alf_Y), p.p * cos(alf_Y) * cos(alf_X) };
	return Vector{ M, F };
}

void CurveConverter::updateParticle(Particle& p, const Vector& m) const
{
	double angle = getNextAngle();
	p.X = (m.M.X - getXCorrection(angle)) / cos(angle);
	p.Y =  m.M.Y;

	p.aX = tan(atan(m.vec.X / m.vec.Z) + angle);
	p.aY = tan(asin(m.vec.Y / abs(m.vec)));
}

double CurveConverter::getCurrentAngle() const
{
	return 0.5 * theta * (2.* (*dev_step) / nSteps - 1.);
}

double CurveConverter::getNextAngle() const
{
	return 0.5 * theta * (2.* (*dev_step + 1) / nSteps - 1.);
}

double CurveConverter::getXCorrection(double angle) const
{
	return rho * (cos(angle) - 0.5*(1. + cos(0.5*theta)));
}

Point CurveConverter::convertToPlain(double X, double Y, double angle) const
{
	double x = getXCorrection(angle) + X * cos(angle);
	double y = Y;
	double z = rho * sin(angle) + X * sin(angle);

	return Point{ x, y, z };
}