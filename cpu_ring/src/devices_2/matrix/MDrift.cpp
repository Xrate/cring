#include "MDrift.h"

MDrift::MDrift(const DeviceParameters& params)
: MDevice(params), Device(params)
{
    MDrift::initMatrices();
}

void MDrift::initMatrices()
{
    mX_P[0] = 1.;  mX_P[1] = geometry.step;  mX_P[2] = 0.;
    mX_P[3] = 0.;  mX_P[4] = 1.;             mX_P[5] = 0.;

    mY_P[0] = 1.;  mY_P[1] = geometry.step;  mY_P[2] = 0.;
    mY_P[3] = 0.;  mY_P[4] = 1.;             mY_P[5] = 0.;

    initTwissMatrices();
}

void MDrift::affectBeam(const shared_ptr<CBeam> beam) const
{
    MDevice::affectBeam(beam);
}