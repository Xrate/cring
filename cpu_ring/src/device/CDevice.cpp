#include "CDevice.h"
#include "devices/cdipole.h"
#include "devices/cdrift.h"
#include "devices/cquadrupole.h"
#include "devices/csextupole.h"

CDevice::CDevice(const string& name_)
{
	if (name_.empty())
	{
		cout << "You are trying to create empty CDevice object." << endl
			<< "Please check your input files." << endl;
		exit(EXIT_FAILURE);
	}
	name = name_;
	for (size_t i = 0; i < 3; ++i)
	for (size_t j = 0; j < 3; ++j)
	{
		mX_P[i][j] = 0;
		mY_P[i][j] = 0;
		mX_T[i][j] = 0;
		mY_T[i][j] = 0;
	}
}

void CDevice::affectBeam(CBeam* beam)
{
	for (size_t iS = 0; iS < nSteps; ++iS)
	{
		#pragma omp parallel for
		for (size_t iP = 0; iP < beam->numParticles; ++iP)
		{
			{
				auto particle = beam->particles_.at(iP);
				if (!particle.isAlive)
					continue;
				beam->particles_[iP].X =
					mX_P[0][0] * particle.X +
					mX_P[0][1] * particle.aX +
					mX_P[0][2] * particle.dp;
				beam->particles_[iP].aX =
					mX_P[1][0] * particle.X +
					mX_P[1][1] * particle.aX +
					mX_P[1][2] * particle.dp;
				beam->particles_[iP].Y =
					mY_P[0][0] * particle.Y +
					mY_P[0][1] * particle.aY +
					mY_P[0][2] * particle.dp;
				beam->particles_[iP].aY =
					mY_P[1][0] * particle.X +
					mY_P[1][1] * particle.aX +
					mY_P[1][2] * particle.dp;
				beam->particles_[iP].isAlive = 
						  pow2(beam->particles_[iP].X / appertureX)
						+ pow2(beam->particles_[iP].Y / appertureY) <= 1.;
			}
		}
		auto params = beam->parameters_;
		beam->parameters_.twissX.bet =
			mX_T[0][0] * params.twissX.bet +
			mX_T[0][1] * params.twissX.alf +
			mX_T[0][2] * params.twissX.gam;
	}
}

void CDevice::generateTwissM()
{
	double C = mX_P[0][0],  S = mX_P[0][1];
	double C_= mX_P[1][0],  S_= mX_P[1][1];

	mX_T[0][0] = +1 * C *C;   mX_T[0][1] = -2 * C *S;    mX_T[0][2] = +1 * S *S;
	mX_T[1][0] = -1 * C *C_;  mX_T[1][1] = C*S_ + C_*S;  mX_T[1][2] = -1 * S *S_;
	mX_T[2][0] = +1 * C_*C_;  mX_T[2][1] = -2 * C_*S_;   mX_T[2][2] = +1 * S_*S_;

	C = mY_P[0][0], S = mY_P[0][1];
	C_= mY_P[1][0], S_= mY_P[1][1];

	mY_T[0][0] = +1 * C *C;   mY_T[0][1] = -2 * C *S;    mY_T[0][2] = +1 * S *S;
	mY_T[1][0] = -1 * C *C_;  mY_T[1][1] = C*S_ + C_*S;  mY_T[1][2] = -1 * S *S_;
	mY_T[2][0] = +1 * C_*C_;  mY_T[2][1] = -2 * C_*S_;   mY_T[2][2] = +1 * S_*S_;
}

CDevice* CDevice::createDevice(DeviceParameters* params)
{
	switch (params->type())
	{
	case DIPOLE: return new CDipole(params);
	case DRIFT: return new CDrift(params);
	case QUADRUPOLE: return new CQuadrupole(params);
	case SEXTUPOLE: return new CSextupole(params);
	}
	cout << "DeviceFactory: enum FileNames error." << endl;
	exit(EXIT_FAILURE);
	return new CDrift(params);
}