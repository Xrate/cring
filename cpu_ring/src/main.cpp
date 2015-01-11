#include "iostream"
#include "ring/CRing.h"
#include "ring/RingConf.h"
using namespace std;

int main(int argc, char *argv[])
{
	FileNames names;
	names.dipoleFile = string("data/dipoles.in");
	names.driftFile = string("data/drifts.in");
	names.quadrupoleFile = string("data/quadrupoles.in");
	names.sextupoleFile = string("data/sextupoles.in");
	names.structureFile = string("data/structure.in");
	RingConf config{ names };
	auto ring = CRing::getInstance(config);
	return 0;
}