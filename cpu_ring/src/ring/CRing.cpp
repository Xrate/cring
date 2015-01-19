#include "CRing.h"

CRing* CRing::instance = nullptr;

CRing* CRing::getInstance(RingConfig* config)
{
	if (!instance)
		instance = new CRing(config);
	return instance;
}

CRing * CRing::getInstance()
{
	if (instance)
		return instance;
	throw exception("CRing: Try to access null CRing");
}

void CRing::destroyInstance()
{
	delete instance;
}

void CRing::setConf(RingConfig* config)
{
	auto deviceMap = config->getDevicesMap();
	for (string name : config->getStructure())
	{
		auto deviceParams = deviceMap.at(name);
		devices.push_back(CDevice::createDevice(deviceParams));
	}
	numDevices = devices.size();
	delete config;
}

const vector<CDevice*>& CRing::getDevices() const
{
	return devices;
}

void CRing::affectBeam(CBeam* beam, size_t nTurns)
{
	for (int iT = 0; iT < nTurns; ++iT)
	{
		for (CDevice* device : devices)
		{
			device->affectBeam(beam);
		}
	}
}

CRing::CRing(RingConfig* config)
{
	setConf(config);
}

CRing::~CRing()
{
	for (auto device : devices)
	{
		if (device != nullptr)
		{
			delete device;
			device = nullptr;
		}
	}	
	devices.clear();
}