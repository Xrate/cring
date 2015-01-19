#ifndef LOGGER_H
#define LOGGER_H
#include "../../beam/CBeam.h"

class Logger
{
	void static printParticles(const ParticleVec& particles);
	void static printEllipses(const BeamParameters& parameters);
	void static printPathInAppertures(CDevice* device);

	void static setUpLogger();
	void static closeLogger();
public:
	static double path;
	static string dirName;
	static void GenerateDir();
};

#endif // LOGGER_H