#include "Device.h"
#include "DeviceParameters.h"

Device::Device(const DeviceParameters& params)
{
    if (params.name_.empty()) 
        throw exception("Trying to create empty Device object.");

    name = params.name_;
    geometry.length = params.length_;
    geometry.angle = 0.;
    geometry.nSteps = size_t(params.type_);
    geometry.appertureX = params.appertureX_;
    geometry.appertureY = params.appertureY_;
    geometry.step = geometry.length / geometry.nSteps;
}