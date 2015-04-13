#include "DeviceFieldMap.h"
#include "handler/HandlerCreator.h"
#include "handler/FieldMapHandler.h"
#include "common/primitives.h"
#include "geometry/ConverterFactory.h"
#include "calculation/FCalculator.h"
#include "geometry/CoordConverter.h"
#include <beam/Particle.h>

DeviceFieldMap::DeviceFieldMap(const DeviceGeometry& geometry, const string& name, const size_t* step)
{
    if (!name.empty())
    {
        device_map = shared_ptr<FieldMapHandler>(HandlerCreator::getCurrHandler(name));
        converter = shared_ptr<CoordConverter>(ConverterFactory::getConverter(geometry, step));
    }
}

void DeviceFieldMap::updateParticle(Particle& p) const
{
    auto point = converter->toPlain(p.X, p.Y);
    auto field = getField(point);
    FCalculator::updateParticle(p, field, converter.get());
}

Point DeviceFieldMap::getField(const Point& point) const
{
    auto field =  device_map->getField(point);

    if (field.isNull())
        throw new NullFieldException();

    return field;
}