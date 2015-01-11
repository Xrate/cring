#include "CRing.h"

CRing const* CRing::getInstance(RingConf config)
{
	if (!instance)
		instance = new CRing(config);
	return instance;
}

CRing const* CRing::getInstance()
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
		devices.push_back(CDevice::createDevice(deviceMap[name]));
	}
	numDevices = devices.size();
}

CRing::CRing(const RingConf& config)
{
	setConf(config);
}