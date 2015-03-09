#include "cdipole.h"

CDipole::CDipole(const DeviceParameters& params)
: CDevice(params.name_, params.mapFileName_)
{
    length = params.length_;
    angle  = params.force_;
    radius = length / angle;
    appertureX = params.appertureX_;
    appertureY = params.appertureY_;
    nSteps = size_t(params.type_);
    step = length / nSteps;

    CDipole::initDevice();
}

void CDipole::initDevice()
{
    double rho = radius;
    double fi = step / radius;

    mX_P[0] = cos(fi);       mX_P[1] = sin(fi)*rho;  mX_P[2] = (1-cos(fi))*rho;
    mX_P[3] = -sin(fi)/rho;  mX_P[4] = cos(fi);      mX_P[5] = sin(fi);

    mY_P[0] = 1.;  mY_P[1] = step;  mY_P[2] = 0.;
    mY_P[3] = 0.;  mY_P[4] = 1.;    mY_P[5] = 0.;

    generateTwissMatrices();
}