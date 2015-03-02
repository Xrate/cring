#pragma once

#include "../CDevice.h"
#include "../DeviceParameters.h"

class CSextupole : public CDevice
{
public:
	explicit CSextupole(const DeviceParameters& params);
	virtual void initDevice() override;
private:
	double force;
};
