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
	friend   FDevice;
public:
	virtual                ~DeviceFieldMap(                                ){}

	virtual  physics::Point getField      (const physics::Point&  point    ) const;

protected:
	explicit                DeviceFieldMap(const string&          field_map)      ;

    unique_ptr<FieldMapHandler> device_map;
public:
	bool hasField;
};