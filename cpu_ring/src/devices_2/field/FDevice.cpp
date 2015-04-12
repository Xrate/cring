#include "FDevice.h"
#include "field_map/physics/physics.h"
#include "field_map/DeviceFieldMap.h"
#include "beam/Particle.h"
#include "geometry/CoordConverter.h"
#include "geometry/helper/GeometryHelper.h"

FDevice::FDevice(const DeviceParameters& params)
: Device(params)
{
	converter = unique_ptr<CoordConverter>(CoordConverter::getConverter(geometry));
	converter->trackDeviceStep(curr_step);
}

using physics::Plane;
using physics::Vector;
using physics::Point;

void FDevice::affectParticle(Particle& p) const
{
	const Point  field    = fieldMap->getField(p.X, p.Y, curr_step);
	const Vector momentum = converter->getMomentum(p);
	const Plane  newPlane = converter->getNextPlane();
	
	const Vector newMomentum = GeometryHelper::calculateNewMomentum(momentum, field, newPlane);

	converter->updateParticle(p, newMomentum);
}