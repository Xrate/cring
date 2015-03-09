#pragma once

#include "device/CDevice.h"

class CDrift : public CDevice
{
public:
    explicit CDrift(const DeviceParameters& params);
    virtual void initDevice() override;
};
