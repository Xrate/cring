#pragma once
#include "DeviceFieldMap.h"

struct Geometry;

class ExtendedDeviceFieldMap : public DeviceFieldMap
{
	friend   FDevice;
public:
	explicit ExtendedDeviceFieldMap(const string& field_map);
	void setPrevMap(Geometry curr, Geometry prev, const string& mapName);
	void setNextMap(Geometry curr, Geometry next, const string& mapName);
	physics::Point getField(const physics::Point& point) const override;
	
protected:
	unique_ptr<FieldMapHandler> prev_device_map;
	unique_ptr<FieldMapHandler> next_device_map;
};
