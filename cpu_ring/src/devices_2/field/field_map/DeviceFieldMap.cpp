#include "DeviceFieldMap.h"
#include "physics/physics.h"
#include "FieldMapHandler.h"

using namespace physics;

DeviceFieldMap::DeviceFieldMap(const string& field_map)
: hasField(false)
{
	device_map = unique_ptr<FieldMapHandler>(FieldMapHandler::getCurrHandler(field_map));
	if (device_map != nullptr) hasField = true;
}

Point DeviceFieldMap::getField(const Point& point) const
{
	return device_map->getField(point);
}