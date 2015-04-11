#pragma once

#include "global.h"

struct DeviceParameters;
class Device;

class DeviceFactory
{
    DeviceFactory() = delete;
public:
    static shared_ptr<Device> createDevice(const DeviceParameters& params);
};