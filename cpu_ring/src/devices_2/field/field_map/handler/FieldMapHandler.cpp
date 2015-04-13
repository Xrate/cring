#include "FieldMapHandler.h"
#include "physics/data/FieldMapData.h"
#include <devices_2/field/field_map/common/primitives.h>
#include "physics/coord/CoordBooster.h"
#include "physics/data/FieldMapDataReader.h"

Point FieldMapHandler::getField(Point p)
{
    Point own = booster->convertPoint(p);
    Point field = data->getFieldInPoint(own);
    return field;
}

FieldMapHandler::FieldMapHandler(const string& map_name, const physics::CoordTransformation& transform)
: 
mapName(map_name), 
data(physics::FieldMapDataReader::getFieldMapData(mapName)), 
booster(new physics::CoordBooster(transform))
{}