#include "FMQuadrupole.h"

#include <device/field/field_map/DeviceFieldMap.h>
#include <beam/Particle.h>

FMQuadrupole::FMQuadrupole(const DeviceParameters& params)
: 
MQuadrupole(params), 
FDevice(params),
Device(params)
{}

void FMQuadrupole::affectParticle(Particle & p) const
{
    try
    {
        FDevice::affectParticle(p);
    }
    catch (NullFieldException)
    {
        MQuadrupole::affectParticle(p);
    }
}

void FMQuadrupole::affectEllipses(BeamConfig* params) const
{
    MQuadrupole::affectEllipses(params);
}
