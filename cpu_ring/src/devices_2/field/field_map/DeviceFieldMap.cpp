#include "DeviceFieldMap.h"
#include "handler/HandlerCreator.h"
#include "handler/FieldMapHandler.h"
#include "common/primitives.h"
#include "calculation/FCalculator.h"
#include "geometry/ICoordConverter.h"
#include <beam/Particle.h>
#include "ExtendedDeviceFieldMap.h"

DeviceFieldMap::DeviceFieldMap(const DeviceGeometry& geometry, const string& name)
{
    if (!name.empty())
        device_map = shared_ptr<const FieldMapHandler>(HandlerCreator::getCurrHandler(name));

    converter = shared_ptr<const ICoordConverter>(getConverter(geometry));
}

DeviceFieldMap::DeviceFieldMap(const ExtendedDeviceFieldMap* map)
:
device_map(map->device_map), 
converter(map->converter)
{}

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