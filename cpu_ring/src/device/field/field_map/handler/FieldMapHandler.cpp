#include "FieldMapHandler.h"

#include <device/field/field_map/common/primitives.h>
#include <device/field/field_map/handler/physics/coord/CoordBooster.h>
#include <device/field/field_map/handler/physics/data/FieldMapData.h>
#include <device/field/field_map/handler/physics/data/FieldMapDataReader.h>

Point FieldMapHandler::getField(Point p) const
{
    Point own = booster->convertPoint(p);
    Point rawField = data->getFieldInPoint(own);
	Point field = booster->rotateField(rawField);
    return field;
}

FieldMapHandler::FieldMapHandler(const string& map_name, const physics::CoordTransformation& transform)
{
    if (!map_name.empty())
    {
        mapName = map_name;
        data = shared_ptr<const physics::FieldMapData>(physics::FieldMapDataReader::getFieldMapData(mapName));
        booster = make_shared<const physics::CoordBooster>(transform);
    }
}