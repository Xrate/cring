#ifndef BEAMPARAMETERS_H
#define BEAMPARAMETERS_H
#include "TwissParameters.h"

enum DistType { UNIFORM, GAUSSIAN };

struct BeamParameters {
	BeamParameters(TwissParameters twiss_x,
	TwissParameters twiss_y,
	size_t num_particles, DistType dist_type,
	double momentum, double momentum_spread);

	TwissParameters twissX;
	TwissParameters twissY;
	size_t numParticles;
	DistType distType;
	double momentum;
	double momentumSpread;
};
#endif // BEAMPARAMETERS_H
