#include "FieldMapHandler.h"
#include "physics/data/FieldMapData.h"
#include <devices_2/field/field_map/common/primitives.h>
#include "physics/coord/CoordBooster.h"
#include "physics/data/FieldMapDataReader.h"

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