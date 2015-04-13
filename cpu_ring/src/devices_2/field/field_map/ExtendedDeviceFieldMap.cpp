#include "ExtendedDeviceFieldMap.h"
#include <devices_2/common/Device.h>
#include "handler/HandlerCreator.h"
#include "handler/FieldMapHandler.h"
#include "common/primitives.h"

ExtendedDeviceFieldMap::ExtendedDeviceFieldMap(const DeviceGeometry& geometry,
                                               const string& name            ,
                                               const size_t* step            )
: DeviceFieldMap(geometry, name, step)
{}

void ExtendedDeviceFieldMap::setPrevMap(DeviceGeometry curr, DeviceGeometry prev, const string& mapName)
{
    if (!mapName.empty())
        prev_device_map = shared_ptr<const FieldMapHandler>(HandlerCreator::getPrevHandler(curr, prev, mapName));
    else
        prev_device_map = nullptr;
}

void ExtendedDeviceFieldMap::setNextMap(DeviceGeometry curr, DeviceGeometry next, const string& mapName)
{
    if (!mapName.empty())
        next_device_map = shared_ptr<const FieldMapHandler>(HandlerCreator::getNextHandler(curr, next, mapName));
    else
        next_device_map = nullptr;
}

Point ExtendedDeviceFieldMap::getField(const Point& point) const
{
    Point field = Point::Null;
    if (device_map      != nullptr) field = field +      device_map->getField(point);
    if (prev_device_map != nullptr) field = field + prev_device_map->getField(point);
    if (next_device_map != nullptr) field = field + next_device_map->getField(point);

    if (field.isNull()) throw NullFieldException();

    return field;
}
