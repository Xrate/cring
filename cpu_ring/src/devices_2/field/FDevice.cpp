#include "FDevice.h"
#include "field_map/physics/physics.h"
#include "field_map/DeviceFieldMap.h"
#include "beam/Particle.h"
#include "geometry/CoordConverter.h"
#include "geometry/helper/GeometryHelper.h"
#include "field_map/ExtendedDeviceFieldMap.h"
#include <devices_2/common/DeviceParameters.h>

FDevice::FDevice(const DeviceParameters& params)
: Device(params), fieldMapName(params.mapFileName_)
{
	converter = unique_ptr<CoordConverter>(CoordConverter::getConverter(geometry));
	converter->trackDeviceStep(curr_step);

	fieldMap = make_unique<ExtendedDeviceFieldMap>(params.mapFileName_);
}

void FDevice::updateFieldMap(const FDevice* prev, const FDevice* next)
{
	auto extendedFieldMap = dynamic_cast<ExtendedDeviceFieldMap*>(fieldMap.get());
	extendedFieldMap->setPrevMap(this->geometry, prev->geometry, prev->fieldMapName);
	extendedFieldMap->setNextMap(this->geometry, next->geometry, next->fieldMapName);

	if (extendedFieldMap->prev_device_map == nullptr &&
		extendedFieldMap->next_device_map == nullptr)
		fieldMap = unique_ptr<DeviceFieldMap>(static_cast<DeviceFieldMap*>(fieldMap.get()));
}

using physics::Plane;
using physics::Vector;
using physics::Point;

void FDevice::affectParticle(Particle& p) const
{
	const Point  plain    = converter->getPlainCoord(p.X, p.Y);
	const Point  field    = fieldMap->getField(plain);
	const Vector momentum = converter->getMomentum(p);
	const Plane  newPlane = converter->getNextPlane();
	
	const Vector newMomentum = GeometryHelper::calculateNewMomentum(momentum, field, newPlane);

	converter->updateParticle(p, newMomentum);
}