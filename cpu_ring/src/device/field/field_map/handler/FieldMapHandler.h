#pragma once
#include <global.h>

namespace physics
{
    class CoordBooster;
    struct CoordTransformation;
    struct FieldMapData;
}

struct Point;

class FieldMapHandler
{
    friend class HandlerCreator;
public:
    Point getField(Point p) const;
private:
    FieldMapHandler(const string& map_name, const physics::CoordTransformation& transform);
    string mapName;
    shared_ptr<const physics::FieldMapData> data;
    shared_ptr<const physics::CoordBooster> booster;
};