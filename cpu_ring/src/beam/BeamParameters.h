#ifndef BEAMPARAMETERS_H
#define BEAMPARAMETERS_H
#include "TwissParameters.h"

enum DistType { UNIFORM, GAUSSIAN };

class BeamParameters
{
public:
	BeamParameters(TwissParameters twiss_x, TwissParameters twiss_y, 
				   size_t num_particles, DistType dist_type, 
				   double momentum, double momentum_spread);

	const TwissParameters& twissX() const;
	const TwissParameters& twissY() const;
	size_t numParticles() const;
	DistType distType() const;
	double momentum() const;
	double momentumSpread() const;
private:
	TwissParameters twissX_;
	TwissParameters twissY_;
	size_t numParticles_;
	DistType distType_;
	double momentum_;
	double momentumSpread_;
};
#endif // BEAMPARAMETERS_H
