#include "DeviceFactory.h"
#include "DeviceParameters.h"
#include ""

shared_ptr<Device> DeviceFactory::createDevice(const DeviceParameters& params)
{
    switch (params.type_)
    {
    case DIPOLE: return make_shared<FMDipole>(params);
    case DRIFT: return make_shared<FMDrift>(params);
    case QUADRUPOLE: return make_shared<FMQuadrupole>(params);
    case SEXTUPOLE: return make_shared<FMSextupole>(params);
    }
    throw exception("DeviceFactory: enum FileNames error.");
}
