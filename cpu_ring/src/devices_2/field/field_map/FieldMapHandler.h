#pragma once
#include "global.h"

namespace physics
{
    class FieldMapData;
    class CoordBooster;
	struct Point;
}
class FDevice;
struct DeviceGeometry;

class FieldMapHandler
{
public:
    static FieldMapHandler* getPrevHandler(DeviceGeometry curr, DeviceGeometry prev, const string& field_map);
    static FieldMapHandler* getCurrHandler(const string& field_map);
    static FieldMapHandler* getNextHandler(DeviceGeometry curr, DeviceGeometry next, const string& field_map);
	physics::Point getField(physics::Point p);
private:
	FieldMapHandler(const string& map_name, const physics::CoordBooster* converter);
	const string mapName;
    shared_ptr<const physics::FieldMapData> data;
    unique_ptr<const physics::CoordBooster> converter;
};