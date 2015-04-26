#include "HandlerCreator.h"
#include "FieldMapHandler.h"
#include <devices_2/common/DeviceGeometry.h>
#include <devices_2/field/field_map/common/primitives.h>
#include "physics/coord/CoordTransformation.h"

using namespace physics;

FieldMapHandler* HandlerCreator::getPrevHandler(const DeviceGeometry& curr,
                                                const DeviceGeometry& prev,
                                                const string& field_map)
{
    CoordTransformation global = calculateTransformation(curr, prev);
    CoordTransformation prevTransform = { global.Z, -global.X, -global.angle };
    auto handler = new FieldMapHandler(field_map, prevTransform);

    if (handler->getField(Point{ 0., 0., -curr.length / 2 }).isNull())
    {
        delete handler;
        return nullptr;
    }
    return handler;
}

FieldMapHandler* HandlerCreator::getCurrHandler(const string & field_map)
{
    CoordTransformation curr = { 0., 0., 0. };
    auto handler = new FieldMapHandler(field_map, curr);

    if (handler->getField(Point{ 0., 0., 0. }).isNull())
    {
        delete handler;
        return nullptr;
    }
    return handler;
}

FieldMapHandler* HandlerCreator::getNextHandler(const DeviceGeometry& curr,
                                                const DeviceGeometry& next,
                                                const string& field_map)
{
    CoordTransformation global = calculateTransformation(next, curr);
    CoordTransformation nextTransform = { -global.Z, -global.X, global.angle };
    auto handler = new FieldMapHandler(field_map, nextTransform);

    if (handler->getField(Point{ 0., 0., curr.length / 2 }).isNull())
    {
        delete handler;
        return nullptr;
    }
    return handler;
}