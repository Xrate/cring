#ifndef BEAMPARAMETERS_H
#define BEAMPARAMETERS_H

#include "../global.h"

enum DistType { UNIFORM, GAUSSIAN };

struct TwissParameters
{
	TwissParameters(double alf, double bet, double emt);
	double alf;
	double bet;
	double gam;
	double emt;
	double coordMax;
	double angleMax;
};

struct BeamParameters {
	BeamParameters(TwissParameters twiss_x,
	TwissParameters twiss_y,
	size_t num_particles, DistType dist_type,
	double momentum, double momentum_spread);

	static BeamParameters readBeamParameters(string fileName);

	TwissParameters twissX;
	TwissParameters twissY;
	size_t numParticles;
	DistType distType;
	double momentum;
	double momentumSpread;
};
#endif // BEAMPARAMETERS_H
