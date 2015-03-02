#include "cquadrupole.h"
#include <cmath>

CQuadrupole::CQuadrupole(const DeviceParameters& params)
: CDevice(params.name_, params.mapFileName_)
{
	length = params.length_;
	force = params.force_;
	appertureX = params.appertureX_;
	appertureY = params.appertureY_;
	nSteps = size_t(params.type_);
	step = length / nSteps;

	CQuadrupole::initDevice();
}

void CQuadrupole::initDevice()
{
	
    double sq_k = sqrt(fabs(force));
    double fi   = sq_k * step;

	mX_P[0][0] = cos(fi);       mX_P[0][1] = sin(fi)/sq_k;  mX_P[0][2] = 0.;
	mX_P[1][0] = -sin(fi)*sq_k; mX_P[1][1] = cos(fi);       mX_P[1][2] = 0.;
	mX_P[2][0] = 0.;            mX_P[2][1] = 0.;            mX_P[2][2] = 1.;

	mY_P[0][0] = cosh(fi);      mY_P[0][1] = sinh(fi)/sq_k; mY_P[0][2] = 0.;
	mY_P[1][0] = sinh(fi)*sq_k; mY_P[1][1] = cosh(fi);      mY_P[1][2] = 0.;
	mY_P[2][0] = 0.;            mY_P[2][1] = 0.;            mY_P[2][2] = 1.;

	if (force < 0)
		swap(mX_P, mY_P);

    generateTwissMatrices();
}
