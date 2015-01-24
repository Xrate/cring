#include "cdipole.h"

CDipole::CDipole(const shared_ptr<const DeviceParameters> params)
    : CDevice(params->name)
{
	length = params->length;
	angle  = params->force;
    appertureX = params->appertureX;
	appertureY = params->appertureY;
	nSteps = size_t(params->type);
    step = length / nSteps;

	CDipole::initMatrices();
}

void CDipole::initMatrices()
{
    double rho = length / angle;
    double fi  = step   / rho;

	mX_P[0][0] = cos(fi);       mX_P[0][1] = sin(fi)*rho;  mX_P[0][2] = (1-cos(fi))*rho;
	mX_P[1][0] = -sin(fi)/rho;  mX_P[1][1] = cos(fi);      mX_P[1][2] = sin(fi);
	mX_P[2][0] = 0.;            mX_P[2][1] = 0.;           mX_P[2][2] = 1.;

	mY_P[0][0] = 1.;  mY_P[0][1] = step;  mY_P[0][2] = 0.;
	mY_P[1][0] = 0.;  mY_P[1][1] = 1.;    mY_P[1][2] = 0.;
	mY_P[2][0] = 0.;  mY_P[2][1] = 0.;    mY_P[2][2] = 1.;

    generateTwissM();
}