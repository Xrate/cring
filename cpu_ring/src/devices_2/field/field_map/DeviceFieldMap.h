#pragma once
#include "global.h"

class FDevice;
class FieldMapHandler;
namespace physics
{
	struct Point;
}

class DeviceFieldMap
{
	friend FDevice;
public:
	         physics::Point getField      (      double  X        ,
				                                 double  Y        , 
								                 size_t  iS       );
private:
	explicit                DeviceFieldMap(const string& field_map);

    unique_ptr<FieldMapHandler> prev_device_map;
    unique_ptr<FieldMapHandler> curr_device_map;
    unique_ptr<FieldMapHandler> next_device_map;
};