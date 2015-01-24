#ifndef LOGGER_H
#define LOGGER_H
#include "../../beam/CBeam.h"
#include <fstream>

class Logger
{
public:
	void static printParticles(double, double);
	void static printEllipses(double, double);

	void static setUpLogger(const shared_ptr<const CBeam> beam_);
	void static closeLogger();
private:
	static ofstream *pXFile;
	static ofstream *pYFile;
	static ofstream *eXFile;
	static ofstream *eYFile;
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