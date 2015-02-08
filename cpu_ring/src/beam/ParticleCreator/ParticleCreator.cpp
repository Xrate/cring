#include "ParticleCreator.h"

shared_ptr<IParticleCreator> IParticleCreator::getParticleCreator(DistType distType)
{
	switch (distType)
	{
	case UNIFORM: return make_shared<UniformParticleCreator>();
	case GAUSSIAN: return make_shared<GaussianParticleCreator>();
	default: throw exception(("IParticleCreator: Error with DistType"));
	}
}

void IParticleCreator::createParticles(const BeamParameters& params, ParticleVec& particles)
{
	for (unsigned iParticle = 0; iParticle < params.numParticles; ++iParticle)
		particles[iParticle] = createParticle(params);
}

Particle UniformParticleCreator::createParticle(const BeamParameters& params)
{
	double X_ = 0, Y_ = 0, aX_ = 0, aY_ = 0, dP_ = 0;
	bool isDead = true;
	auto normedRand = []() -> double { return -1. + 2. / RAND_MAX * rand(); };
	while (isDead)
	{
		X_ = params.twissX.coordMax()  * normedRand();

		Y_ = params.twissY.coordMax()  * normedRand();

		aX_ = params.twissY.angleMax() * normedRand();

		aY_ = params.twissY.angleMax() * normedRand();

		dP_ = params.momentumSpread    * normedRand();

		// Particle should be in 3 ellipses (XY, XX', YY')
		bool isXY = sqr(X_ / params.twissX.coordMax())
			+ sqr(Y_ / params.twissY.coordMax()) <= 1.;
		bool isXX = X_*X_   * params.twissX.gam
			+ aX_*aX_ * params.twissX.bet
			+ X_*aX_  * params.twissX.alf * 2.
			<= params.twissX.emt;
		bool isYY = Y_*Y_   * params.twissY.gam
			+ aY_*aY_ * params.twissY.bet
			+ Y_*aY_  * params.twissY.alf * 2.
			<= params.twissY.emt;
		isDead = !(isXY && isXX && isYY);
	}
	return Particle{true, X_, aX_, Y_, aY_, dP_ };
}

Particle GaussianParticleCreator::createParticle(const BeamParameters& params)
{
	throw exception(("Not implemented"));
}
