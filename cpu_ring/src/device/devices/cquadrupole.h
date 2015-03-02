#pragma once

#include "../CDevice.h"
#include "../DeviceParameters.h"

class CQuadrupole : public CDevice
{
public:
	explicit CQuadrupole(const DeviceParameters& params);
    virtual void initDevice() override;
private:
    double force;
};
