#include "FMDipole.h"
#include <devices_2/field/field_map/physics/physics.h>
#include <devices_2/field/geometry/CoordConverter.h>
#include <devices_2/field/field_map/DeviceFieldMap.h>
#include <beam/Particle.h>

FMDipole::FMDipole(const DeviceParameters& params)
: MDipole(params), FDevice(params)
{}

void FMDipole::affectParticle(Particle& p) const
{
	const Point field = fieldMap->getField(converter->getPlainCoord(p.X, p.Y));

	if (!field.isNull())
		FDevice::affectParticle(p);
	else
		MDipole::affectParticle(p);
}