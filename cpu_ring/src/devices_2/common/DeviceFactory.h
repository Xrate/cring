#pragma once

#include "Device.h"

class DeviceFactory
{
    DeviceFactory() = delete;
public:
    static shared_ptr<Device> createDevice(const DeviceParameters& params);
};