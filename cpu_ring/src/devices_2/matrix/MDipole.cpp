#include "MDipole.h"
#include "devices_2/common/DeviceParameters.h"

MDipole::MDipole(const DeviceParameters& params)
: MDevice(params), Device(params)
{
    force = params.force_;
    MDipole::initMatrices();
}

void MDipole::initMatrices()
{
    double rho = geometry.length / force;
    double fi = geometry.step / rho;

    mX_P[0] = cos(fi);         mX_P[1] = sin(fi)*rho;  mX_P[2] = (1 - cos(fi))*rho;
    mX_P[3] = -sin(fi) / rho;  mX_P[4] = cos(fi);      mX_P[5] = sin(fi);

    mY_P[0] = 1.;  mY_P[1] = geometry.step;  mY_P[2] = 0.;
    mY_P[3] = 0.;  mY_P[4] = 1.;             mY_P[5] = 0.;

    initTwissMatrices();
}
