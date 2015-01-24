#include "global.h"
#include "ring/CRing.h"
#include "ring/RingConfig.h"
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
	ring->affectBeam(beam, nTurns);

	CRing::destroyInstance();
	Logger::closeLogger();
	delete beam;

	return 0;
}