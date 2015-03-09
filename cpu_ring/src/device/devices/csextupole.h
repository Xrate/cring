#pragma once

#include "device/CDevice.h"

class CSextupole : public CDevice
{
public:
    explicit CSextupole(const DeviceParameters& params);
    virtual void initDevice() override;
private:
    double force;
};
