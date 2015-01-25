#ifndef LOGGER_H
#define LOGGER_H
#include "../../beam/CBeam.h"
#include <fstream>

class Logger
{
public:
	void static printParticles();
	void static printEllipses(const double& appX, const double& appY);

	string static logDir();

	void static setUpLogger(const shared_ptr<const CBeam> beam_);
	void static closeLogger();
private:
	static ofstream **pFile;
	static ofstream *ellFile;
	static string dirName;
	static void GenerateDir();
	static shared_ptr<const CBeam> beam;
	static struct BeamPointers
	{
		Particle const* particles;
		TwissParameters const* twissX;
		TwissParameters const* twissY;
	} beamPointers;
};

#endif // LOGGER_H