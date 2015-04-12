#pragma once
#include "DeviceFieldMap.h"

struct DeviceGeometry;

class ExtendedDeviceFieldMap : public DeviceFieldMap
{
	friend   FDevice;
public:
	explicit ExtendedDeviceFieldMap(const string& field_map);
	void setPrevMap(DeviceGeometry curr, DeviceGeometry prev, const string& mapName);
	void setNextMap(DeviceGeometry curr, DeviceGeometry next, const string& mapName);
	physics::Point getField(const physics::Point& point) const override;
	
protected:
	unique_ptr<FieldMapHandler> prev_device_map;
	unique_ptr<FieldMapHandler> next_device_map;
};
