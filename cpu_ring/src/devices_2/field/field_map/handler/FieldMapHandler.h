#pragma once
#include "global.h"

namespace physics
{
    class CoordBooster;
    struct CoordTransformation;
    struct FieldMapData;
}

class FDevice;
struct DeviceGeometry;
struct Point;

class FieldMapHandler
{
    friend class HandlerCreator;
public:
    Point getField(Point p);
private:
    FieldMapHandler(const string& map_name, const physics::CoordTransformation& transform);
    const string mapName;
    shared_ptr<const physics::FieldMapData> data;
    shared_ptr<const physics::CoordBooster> booster;
};