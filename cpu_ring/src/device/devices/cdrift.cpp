#include "cdrift.h"

CDrift::CDrift(const DeviceParameters& params)
: CDevice(params.name_)
{
	length = params.length_;
	appertureX = params.appertureX_;
	appertureY = params.appertureY_;
	nSteps = size_t(params.type_);
	step = length / nSteps;

	CDrift::initMatrices();
}

void CDrift::initMatrices()
{
	mX_P[0][0] = 1.;  mX_P[0][1] = step;  mX_P[0][2] = 0.;
	mX_P[1][0] = 0.;  mX_P[1][1] = 1.;    mX_P[1][2] = 0.;
	mX_P[2][0] = 0.;  mX_P[2][1] = 0.;    mX_P[2][2] = 1.;

	mY_P[0][0] = 1.;  mY_P[0][1] = step;  mY_P[0][2] = 0.;
	mY_P[1][0] = 0.;  mY_P[1][1] = 1.;    mY_P[1][2] = 0.;
	mY_P[2][0] = 0.;  mY_P[2][1] = 0.;    mY_P[2][2] = 1.;

    generateTwissM();
}
