#ifndef DEVICESFACTORY_H
#define DEVICESFACTORY_H

#include "DeviceParameters.h"
#include "CDevice.h"

class DevicesFactory
{
public:
	static CDevice* createDevice(DeviceType type, DeviceParameters* params);
private:
	DevicesFactory(){}
};

#endif // DEVICESFACTORY_H
