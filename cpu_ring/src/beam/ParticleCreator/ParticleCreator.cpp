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

void IParticleCreator::createParticles(const BeamConfig& params, vector<Particle>& particles)
{
	for (unsigned iParticle = 0; iParticle < params.numParticles; ++iParticle)
		particles[iParticle] = createParticle(params);
}

Particle UniformParticleCreator::createParticle(const BeamConfig& params)
{
	const double m0 = 0.93272;
	auto normedRand = []() -> double { return -1. + 2. / RAND_MAX * rand(); };

	while (true)
	{
		double X_ = params.twissX.coordMax() * normedRand();
		double Y_ = params.twissY.coordMax() * normedRand();
		double aX_ = params.twissY.angleMax() * normedRand();
		double aY_ = params.twissY.angleMax() * normedRand();
		double dP_ = params.momentumSpread * normedRand();
		double P_ = sqrt(sqr(params.energy + m0) - sqr(m0)) * (1 + dP_);

		// Particle should be in 3 ellipses (XY, XX', YY')
		bool isXY = sqr(X_ / params.twissX.coordMax())
			      + sqr(Y_ / params.twissY.coordMax()) 
				 <= 1.;
		bool isXX =  X_ *  X_ * params.twissX.gam
			      + aX_ * aX_ * params.twissX.bet
			      +  X_ * aX_ * params.twissX.alf * 2.
			     <= params.twissX.emt;
		bool isYY = Y_  * Y_  * params.twissY.gam
			      + aY_ * aY_ * params.twissY.bet
			      + Y_  * aY_ * params.twissY.alf * 2.
			     <= params.twissY.emt;
		if (isXY && isXX && isYY)
			return Particle{ true, X_, aX_, Y_, aY_, dP_, P_ };
	}
}

Particle GaussianParticleCreator::createParticle(const BeamConfig& params)
{
	throw exception(("Not implemented"));
}
