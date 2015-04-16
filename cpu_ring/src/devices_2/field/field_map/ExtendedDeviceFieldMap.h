#pragma once
#include "DeviceFieldMap.h"

struct DeviceGeometry;

class ExtendedDeviceFieldMap : public DeviceFieldMap
{
    friend   FDevice;
public:
    ExtendedDeviceFieldMap(const DeviceGeometry&  , 
                           const string& name     );
    void setPrevMap(DeviceGeometry curr, DeviceGeometry prev, const string& mapName);
    void setNextMap(DeviceGeometry curr, DeviceGeometry next, const string& mapName);
    Point getField(const Point& point) const override;
    
protected:
    shared_ptr<const FieldMapHandler> prev_device_map;
    shared_ptr<const FieldMapHandler> next_device_map;
};
