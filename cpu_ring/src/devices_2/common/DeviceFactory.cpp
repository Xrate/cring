#include "DeviceFactory.h"
#include "DeviceParameters.h"
#include <devices_2/field_matrix/FMDipole.h>
#include <devices_2/field_matrix/FMQuadrupole.h>
#include <devices_2/field_matrix/FMDrift.h>

Device* DeviceFactory::createDevice(const DeviceParameters& params)
{
    switch (params.type_)
    {
    case DIPOLE: return new FMDipole(params);
    case DRIFT: return new FMDrift(params);
    case QUADRUPOLE: return new FMQuadrupole(params);
    case SEXTUPOLE: return new FMDrift(params);
    }
    throw exception("DeviceFactory: enum FileNames error.");
}
