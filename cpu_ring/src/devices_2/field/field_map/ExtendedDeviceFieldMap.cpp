#include "ExtendedDeviceFieldMap.h"
#include "physics/physics.h"
#include <devices_2/common/Device.h>
#include "FieldMapHandler.h"

using namespace physics;

ExtendedDeviceFieldMap::ExtendedDeviceFieldMap(const string& field_map)
: DeviceFieldMap(field_map)
{}

void ExtendedDeviceFieldMap::setPrevMap(Geometry curr, Geometry prev, const string& mapName)
{
	prev_device_map = unique_ptr<FieldMapHandler>(FieldMapHandler::getPrevHandler(curr, prev, mapName));
	if (prev_device_map != nullptr) hasField = true;
}

void ExtendedDeviceFieldMap::setNextMap(Geometry curr, Geometry next, const string& mapName)
{
	next_device_map = unique_ptr<FieldMapHandler>(FieldMapHandler::getNextHandler(curr, next, mapName));
	if (next_device_map != nullptr) hasField = true;
}

Point ExtendedDeviceFieldMap::getField(const Point & point) const
{

}
