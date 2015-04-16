#pragma once

struct DeviceParameters;
class Device;

class DeviceFactory
{
    DeviceFactory() = delete;
public:
    static Device* createDevice(const DeviceParameters& params);
};