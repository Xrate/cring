#pragma once

#include "device/CDevice.h"

class CDipole : public CDevice
{
public:
    explicit CDipole(const DeviceParameters& params);
    virtual void initDevice() override;
private:
    double angle;
};
