#include "DeviceFieldMap.h"

#include <beam/Particle.h>
#include <device/field/field_map/handler/HandlerCreator.h>
#include <device/field/field_map/handler/FieldMapHandler.h>
#include <device/field/field_map/common/primitives.h>
#include <device/field/field_map/calculation/FCalculator.h>
#include <device/field/field_map/geometry/ICoordConverter.h>

DeviceFieldMap::DeviceFieldMap(const DeviceGeometry& geometry, const string& name)
{
    if (!name.empty())
        device_map = shared_ptr<const FieldMapHandler>(HandlerCreator::getCurrHandler(name));

    converter = shared_ptr<const ICoordConverter>(getConverter(geometry));
}

void DeviceFieldMap::updateParticle(Particle& p, size_t iS) const
{
    auto point = converter->toPlain(p.X, p.Y, iS);
    auto field = getField(point);
    FCalculator::updateParticle(p, field, converter.get(), iS);
}

Point DeviceFieldMap::getField(const Point& point) const
{
    auto field =  device_map->getField(point);

    if (field.isNull())
        throw NullFieldException();

    return field;
}