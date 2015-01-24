#include "CRing.h"
#include <ctime>

shared_ptr<const CRing> CRing::instance;

shared_ptr<const CRing> CRing::createInstance(const shared_ptr<const RingConfig> config)
{
	if (!instance)
		instance = shared_ptr<const CRing>(new CRing(config));
	return instance;
}

shared_ptr<const CRing> CRing::getInstance()
{
	if (instance)
		return instance;
	throw exception("CRing: Try to access null CRing");
}

CRing::CRing(shared_ptr<const RingConfig> config)
{
	auto deviceMap = config->devices;
	for (string name : config->structure)
	{
		auto deviceParams = deviceMap.at(name);
		devices.push_back(CDevice::createDevice(deviceParams));
	}
	numDevices = devices.size();
}

void CRing::affectBeam(shared_ptr<CBeam> beam) const
{
	clock_t begin = clock();

	for (int iT = 0; iT < beam->turns(); ++iT)
	for (auto device : devices)
	{
		device->affectBeam(beam);
	}

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	cout << "Time: "      << elapsed_secs  << "s. " <<
			"Turns: "     << beam->turns() << ". "  <<
		    "Particles: " << beam->size()  << endl;
}