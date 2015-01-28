#include "global.h"
#include "ring/CRing.h"
#include "ring/RingConfig.h"
#include "analysis/FreqAnalyzer.h"
#include "common/logger/Logger.h"
#include "common/plotter/Plotter.h"
#include <vld.h>
#include <fftw3.h>

int main(int argc, char *argv[])
{
	FileNames names;
	names.dipoleFile = string("data/dipoles.in");
	names.driftFile = string("data/drifts.in");
	names.quadrupoleFile = string("data/quadrupoles.in");
	names.sextupoleFile = string("data/sextupoles.in");
	names.structureFile = string("data/structure.in");
	string beamFile = string("data/beam.in");

	const shared_ptr<const CRing> ring = CRing::createInstance(RingConfig::readRingConfig(names));
	const shared_ptr<CBeam> beam = make_shared<CBeam>(BeamParameters::readBeamParameters(beamFile));

	Logger::setUp(beam);
	ring->affectBeam(beam);
	Logger::close();

	FreqAnalyzer::setUp(Logger::logDir(), beam->turns(), beam->size(), ring->numSteps());
	FreqAnalyzer::calculate();
	FreqAnalyzer::print();

	Plotter::setUp(Logger::logDir(), beam->turns(), beam->size(), ring->numSteps());
	Plotter::plot("plot14", 1, 4);
	Plotter::plotFreqMap();

	return 0;
}