﻿#include "ExtendedDeviceFieldMap.h"

#include <device/common/Device.h>
#include <device/field/field_map/handler/HandlerCreator.h>
#include <device/field/field_map/handler/FieldMapHandler.h>
#include <device/field/field_map/common/primitives.h>

ExtendedDeviceFieldMap::ExtendedDeviceFieldMap(const DeviceGeometry& geometry,
                                               const string& name            )
: DeviceFieldMap(geometry, name)
{}

void ExtendedDeviceFieldMap::setPrevMap(const DeviceGeometry& curr,
                                        const DeviceGeometry& prev,
                                        const string& mapName)
{
    if (!mapName.empty())
        prev_device_map = shared_ptr<const FieldMapHandler>(HandlerCreator::getPrevHandler(curr, prev, mapName));
    else
        prev_device_map = nullptr;
}

void ExtendedDeviceFieldMap::setNextMap(const DeviceGeometry& curr,
                                        const DeviceGeometry& next,
                                        const string& mapName)
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
