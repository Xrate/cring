#include "CRing.h"

CRing* CRing::instance = nullptr;

CRing * CRing::getInstance(RingConf config)
{
	if (!instance)
		instance = new CRing(config);
	return instance;
}

CRing * CRing::getInstance()
{
	if (instance)
		return instance;
	cout << "CRing: Try to access null CRing" << endl;
	exit(EXIT_FAILURE);
	return instance;
}

void CRing::setConf(const RingConf& config)
{
	auto deviceMap = config.getDevicesMap();
	for (string name : config.getStructure())
	{
		auto deviceParams = deviceMap.at(name);
		devices.push_back(CDevice::createDevice(deviceParams));
	}
	numDevices = devices.size();
}

CRing::CRing(const RingConf& config)
{
	setConf(config);
}