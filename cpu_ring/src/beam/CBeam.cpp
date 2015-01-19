#include "CBeam.h"

CBeam::CBeam(BeamParameters parameters) :
parameters_(parameters),
particles_(parameters.numParticles)
{
	generateParticles(parameters_.distType);
}

void CBeam::createUniformParticles()
{
//#pragma omp parallel for
	for (unsigned iParticle = 0; iParticle < parameters_.numParticles; ++iParticle)
	{
		double X = 0, Y = 0, aX = 0, aY = 0, dP = 0;
		bool isDead = true;
		while (isDead)
		{
			X = parameters_.twissX.coordMax;
			X *= (-1. + 2. / RAND_MAX * rand());

			Y = parameters_.twissY.coordMax;
			Y *= (-1. + 2. / RAND_MAX * rand());

			aX = parameters_.twissY.angleMax;
			aX *= (-1. + 2. / RAND_MAX * rand());

			aY = parameters_.twissY.angleMax;
			aY *= (-1. + 2. / RAND_MAX * rand());

			dP = parameters_.momentumSpread;
			dP *= (-1. + 2. / RAND_MAX * rand());

			// Particle should be in 3 ellipses (XY, XX', YY')
			bool isXY = pow2(X / parameters_.twissX.coordMax)
					  + pow2(Y / parameters_.twissY.coordMax) <= 1.;
			bool isXX = X*X   * parameters_.twissX.gam 
					  + aX*aX * parameters_.twissX.bet 
					  + X*aX  * parameters_.twissX.alf * 2.
					  <= parameters_.twissX.emt;
			bool isYY = X*X   * parameters_.twissY.gam
					  + aX*aX * parameters_.twissY.bet
					  + X*aX  * parameters_.twissY.alf * 2.
					  <= parameters_.twissY.emt;
			isDead = !(isXY && isXX && isYY);
		}
		particles_[iParticle].X  = X;
		particles_[iParticle].aX = aX;
		particles_[iParticle].Y = Y;
		particles_[iParticle].aY = aY;
		particles_[iParticle].dp = dP;
		particles_[iParticle].ID = iParticle;
		particles_[iParticle].isAlive = true;
	}
	numParticles = parameters_.numParticles;
}

void CBeam::createGaussianParticles()
{
}

void CBeam::generateParticles(DistType dist_type)
{
	switch (dist_type)
	{
	case UNIFORM:  createUniformParticles(); break;
	case GAUSSIAN: createGaussianParticles(); break;
	default: createUniformParticles(); break;
	}
}

CBeam::~CBeam()
{
	particles_.clear();
}