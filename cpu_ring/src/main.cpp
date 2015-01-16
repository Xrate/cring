#include "global.h"
#include "ring/CRing.h"
#include "ring/RingConf.h"

int main(int argc, char *argv[])
{
	FileNames names;
	names.dipoleFile = string("data/dipoles.in");
	names.driftFile = string("data/drifts.in");
	names.quadrupoleFile = string("data/quadrupoles.in");
	names.sextupoleFile = string("data/sextupoles.in");
	names.structureFile = string("data/structure.in");
	string ellipseFile = string("data/ellipse.in");
	auto ring = CRing::getInstance(RingConfig::getRingConfig(names));
	auto beam = new CBeam(BeamParameters::readBeamParameters(ellipseFile));
	ring->affectBeam(beam);
	return 0;
}