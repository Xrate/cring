#include "FMDrift.h"
#include <devices_2/field/field_map/DeviceFieldMap.h>
#include <beam/Particle.h>

FMDrift::FMDrift(const DeviceParameters& params)
: 
MDrift(params), 
FDevice(params),
Device(params)
{}

void FMDrift::affectParticle(Particle& p) const
{
    try
    {
        FDevice::affectParticle(p);
    }
    catch (NullFieldException)
    {
        MDrift::affectParticle(p);
    }
}

void FMDrift::affectEllipses(BeamConfig* params) const
{
    MDrift::affectEllipses(params);
}