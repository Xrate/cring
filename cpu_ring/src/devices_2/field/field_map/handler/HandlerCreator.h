#pragma once

#include "global.h"

struct DeviceGeometry;
class FieldMapHandler;

class HandlerCreator
{
public:
    static FieldMapHandler* getPrevHandler(DeviceGeometry curr, DeviceGeometry prev, const string& field_map);
    static FieldMapHandler* getCurrHandler(const string& field_map);
    static FieldMapHandler* getNextHandler(DeviceGeometry curr, DeviceGeometry next, const string& field_map);
};
