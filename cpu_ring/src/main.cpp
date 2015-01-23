#include "global.h"
#include "ring/CRing.h"
#include "ring/RingConfig.h"
#include <ctime>
#include "common/logger/Logger.h"
#include <vld.h>

int main(int argc, char *argv[])
{
	FileNames names;
	names.dipoleFile = string("data/dipoles.in");
	names.driftFile = string("data/drifts.in");
	names.quadrupoleFile = string("data/quadrupoles.in");
	names.sextupoleFile = string("data/sextupoles.in");
	names.structureFile = string("data/structure.in");
	string ellipseFile = string("data/ellipse.in");
	const CRing* ring = CRing::getInstance(RingConfig::readRingConfig(names));
	CBeam * const beam = new CBeam(BeamParameters::readBeamParameters(ellipseFile));

	Logger::setUpLogger(beam);

	const size_t nTurns = 1;
	clock_t begin = clock();

	ring->affectBeam(beam, nTurns);

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	cout << elapsed_secs << endl;

	CRing::destroyInstance();
	delete beam;
	Logger::closeLogger();

	return 0;
}