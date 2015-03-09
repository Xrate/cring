#include "csextupole.h"

CSextupole::CSextupole(const DeviceParameters& params)
: CDevice(params.name_, params.mapFileName_)
{
    length = params.length_;
    force = params.force_;
    angle = 0.;
    appertureX = params.appertureX_;
    appertureY = params.appertureY_;
    nSteps = size_t(params.type_);
    step = length / nSteps;

    CSextupole::initDevice();
}

void CSextupole::initDevice()
{
    mX_P[0] = 1.;  mX_P[1] = step;  mX_P[2] = 0.;
    mX_P[3] = 0.;  mX_P[4] = 1.;    mX_P[5] = 0.;

    mY_P[0] = 1.;  mY_P[1] = step;  mY_P[2] = 0.;
    mY_P[3] = 0.;  mY_P[4] = 1.;    mY_P[5] = 0.;

    generateTwissMatrices();
}