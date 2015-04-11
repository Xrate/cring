#include "FDevice.h"
#include "field_map/physics/physics.h"
#include "field_map/DeviceFieldMap.h"
#include "beam/Particle.h"
#include "geometry/CoordConverter.h"
#include "geometry/GeometryHelper.h"

FDevice::FDevice(const DeviceParameters& params)
: Device(params)
{
	convertor = CoordConverter::getConverter(geometry);
}

using physics::Plane;
using physics::Vector;
using physics::Point;

void FDevice::affectParticle(Particle& p) const
{
	const Point  field    = fieldMap->getField(p.X, p.Y, curr_step);
	const Vector momentum = convertor.getMomentum(p, curr_step);
	const Plane  newPlane = convertor.getPlane(curr_step + 1);
	
	const Vector newMomentum = GeometryHelper::calculateNewMomentum(momentum, field, newPlane);

	convertor.updateParticle(p, newMomentum, curr_step + 1);
}