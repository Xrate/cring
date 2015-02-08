#pragma once

#include "../CDevice.h"
#include "../DeviceParameters.h"

class CDipole : public CDevice
{
public:
	explicit CDipole(const DeviceParameters& params);
    virtual void initMatrices() override;

private:
    double angle;
};
