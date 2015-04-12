#pragma once
#include "global.h"

namespace physics
{
    class FieldMapData;
    class CoordConverter;
}
class FDevice;
struct Geometry;

class FieldMapHandler
{
public:
    static FieldMapHandler* getPrevHandler(Geometry curr, Geometry prev, const string& field_map);
    static FieldMapHandler* getCurrHandler(const string& field_map);
    static FieldMapHandler* getNextHandler(Geometry curr, Geometry next, const string& field_map);
private:
	FieldMapHandler(const string& map_name, const physics::FieldMapData* data, const physics::CoordConverter* converter);
	const string mapName;
    shared_ptr<physics::FieldMapData> data;
    unique_ptr<physics::CoordConverter> converter;
};