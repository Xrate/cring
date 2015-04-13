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
        prev_device_map = shared_ptr<FieldMapHandler>(HandlerCreator::getPrevHandler(curr, prev, mapName));
}

void ExtendedDeviceFieldMap::setNextMap(DeviceGeometry curr, DeviceGeometry next, const string& mapName)
{
    if (!mapName.empty())
        next_device_map = shared_ptr<FieldMapHandler>(HandlerCreator::getNextHandler(curr, next, mapName));
}

Point ExtendedDeviceFieldMap::getField(const Point& point) const
{
    auto field =  device_map->getField(point) + 
             prev_device_map->getField(point) + 
             next_device_map->getField(point);

    if (field.isNull())
        throw new NullFieldException();

    return field;
}
