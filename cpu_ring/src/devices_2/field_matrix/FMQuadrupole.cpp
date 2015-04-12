#include "FMQuadrupole.h"
#include <devices_2/field/field_map/physics/physics.h>
#include <devices_2/field/geometry/CoordConverter.h>
#include <devices_2/field/field_map/DeviceFieldMap.h>
#include <beam/Particle.h>

FMQuadrupole::FMQuadrupole(const DeviceParameters& params)
: MQuadrupole(params), FDevice(params)
{}

void FMQuadrupole::affectParticle(Particle & p) const
{
	const Point field = fieldMap->getField(converter->getPlainCoord(p.X, p.Y));

	if (!field.isNull())
		FDevice::affectParticle(p);
	else
		MQuadrupole::affectParticle(p);
}
