#include "FMDipole.h"

#include <device/field/field_map/DeviceFieldMap.h>
#include <beam/Particle.h>

FMDipole::FMDipole(const DeviceParameters& params)
: 
MDipole(params), 
FDevice(params),
Device(params)
{
    geometry.angle = force;
}

void FMDipole::affectParticle(Particle& p) const
{
    try
    {
        FDevice::affectParticle(p);
    }
    catch (NullFieldException&)
    {
        MDipole::affectParticle(p);
    }
}

void FMDipole::affectEllipses(BeamConfig* params) const
{
    MDipole::affectEllipses(params);
}