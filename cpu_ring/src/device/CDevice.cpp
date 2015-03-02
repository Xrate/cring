#include "CDevice.h"
#include "devices/cdipole.h"
#include "devices/cdrift.h"
#include "devices/cquadrupole.h"
#include "devices/csextupole.h"
#include "../common/logger/Logger.h"

shared_ptr<CDevice> CDevice::createDevice(const DeviceParameters& params)
{
	switch (params.type_)
	{
	case DIPOLE: return make_shared<CDipole>(params);
	case DRIFT: return make_shared<CDrift>(params);
	case QUADRUPOLE: return make_shared<CQuadrupole>(params);
	case SEXTUPOLE: return make_shared<CSextupole>(params);
	}
	throw exception("DeviceFactory: enum FileNames error.");
}

CDevice::CDevice(const string& name_, const string& mapFileName_) :
hasMap(false)
{
	if (name_.empty())
		throw exception("Trying to create empty CDevice object.");
	name = name_;

	if (!mapFileName_.empty())
	{
		hasMap = true;
		fieldMap = FieldMap::getFieldMap(mapFileName_);
	}

	for (size_t i = 0; i < 3; ++i)
	for (size_t j = 0; j < 3; ++j)
	{
		mX_P[i][j] = 0.;
		mY_P[i][j] = 0.;
		mX_T[i][j] = 0.;
		mY_T[i][j] = 0.;
	}
}

void CDevice::generateTwissMatrices()
{
	double C = mX_P[0][0], S = mX_P[0][1];
	double C_ = mX_P[1][0], S_ = mX_P[1][1];

	mX_T[0][0] = +1 * C *C;   mX_T[0][1] = -2 * C *S;    mX_T[0][2] = +1 * S *S;
	mX_T[1][0] = -1 * C *C_;  mX_T[1][1] = C*S_ + C_*S;  mX_T[1][2] = -1 * S *S_;
	mX_T[2][0] = +1 * C_*C_;  mX_T[2][1] = -2 * C_*S_;   mX_T[2][2] = +1 * S_*S_;

	C = mY_P[0][0], S = mY_P[0][1];
	C_ = mY_P[1][0], S_ = mY_P[1][1];

	mY_T[0][0] = +1 * C *C;   mY_T[0][1] = -2 * C *S;    mY_T[0][2] = +1 * S *S;
	mY_T[1][0] = -1 * C *C_;  mY_T[1][1] = C*S_ + C_*S;  mY_T[1][2] = -1 * S *S_;
	mY_T[2][0] = +1 * C_*C_;  mY_T[2][1] = -2 * C_*S_;   mY_T[2][2] = +1 * S_*S_;
}

void CDevice::affectBeam(const shared_ptr<CBeam> beam) const
{
	auto particles = beam->particles().data();
	auto params = &beam->parameters();
	for (size_t iS = 0; iS < nSteps; ++iS)
	{
		beam->addPath(step);
		#pragma omp parallel for
		for (int iP = 0; iP < beam->size(); ++iP)
			//affectParticle1stOrder(particles[iP]);
			hasMap ? affectParticleWithMap(particles[iP]) : affectParticle1stOrder(particles[iP]);
		Logger::printParticles();

		//auto tX = params->twissX;
		//params->twissX.bet = mX_T[0][0] * tX.bet + mX_T[0][1] * tX.alf + mX_T[0][2] * tX.gam;
		//params->twissX.alf = mX_T[1][0] * tX.bet + mX_T[1][1] * tX.alf + mX_T[1][2] * tX.gam;
		//params->twissX.gam = mX_T[2][0] * tX.bet + mX_T[2][1] * tX.alf + mX_T[2][2] * tX.gam;

		//auto tY = params->twissY;
		//params->twissY.bet = mY_T[0][0] * tY.bet + mY_T[0][1] * tY.alf + mY_T[0][2] * tY.gam;
		//params->twissY.alf = mY_T[1][0] * tY.bet + mY_T[1][1] * tY.alf + mY_T[1][2] * tY.gam;
		//params->twissY.gam = mY_T[2][0] * tY.bet + mY_T[2][1] * tY.alf + mY_T[2][2] * tY.gam;
		//Logger::printEllipses(appertureX, appertureY);
	}
}

inline void CDevice::affectParticle1stOrder(Particle& particle) const
{
	auto p = particle;
	if (!p.isAlive)
		return;
	particle.X  = mX_P[0][0] * p.X + mX_P[0][1] * p.aX + mX_P[0][2] * p.dp;
	particle.aX = mX_P[1][0] * p.X + mX_P[1][1] * p.aX + mX_P[1][2] * p.dp;
	particle.Y  = mY_P[0][0] * p.Y + mY_P[0][1] * p.aY + mY_P[0][2] * p.dp;
	particle.aY = mY_P[1][0] * p.Y + mY_P[1][1] * p.aY + mY_P[1][2] * p.dp;
	particle.isAlive = sqr(particle.X / appertureX)
		+ sqr(particle.Y / appertureY) <= 1.;
}

void CDevice::affectParticleWithMap(Particle& particle) const
{
	return;
}