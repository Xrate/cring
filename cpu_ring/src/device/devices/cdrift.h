#pragma once

#include "../CDevice.h"
#include "../DeviceParameters.h"

class CDrift : public CDevice
{
public:
	explicit CDrift(const DeviceParameters& params);
    virtual void initMatrices() override;
};
