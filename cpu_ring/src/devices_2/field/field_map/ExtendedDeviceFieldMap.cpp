#include "ExtendedDeviceFieldMap.h"
#include "physics/physics.h"
#include <devices_2/common/Device.h>
#include "FieldMapHandler.h"

using namespace physics;

ExtendedDeviceFieldMap::ExtendedDeviceFieldMap(const string& field_map)
: DeviceFieldMap(field_map)
{}

void ExtendedDeviceFieldMap::setPrevMap(DeviceGeometry curr, DeviceGeometry prev, const string& mapName)
{
	prev_device_map = unique_ptr<FieldMapHandler>(FieldMapHandler::getPrevHandler(curr, prev, mapName));
	if (prev_device_map != nullptr) hasField = true;
}

void ExtendedDeviceFieldMap::setNextMap(DeviceGeometry curr, DeviceGeometry next, const string& mapName)
{
	next_device_map = unique_ptr<FieldMapHandler>(FieldMapHandler::getNextHandler(curr, next, mapName));
	if (next_device_map != nullptr) hasField = true;
}

Point ExtendedDeviceFieldMap::getField(const Point& point) const
{
	return device_map->getField(point) + 
	  prev_device_map->getField(point) + 
	  next_device_map->getField(point);
}
