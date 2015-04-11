#pragma once
#include "global.h"

class FDevice;
class FieldMapHandler;

class DeviceFieldMap
{
public:
    void getField(double X, double Y, size_t iS);
	friend FDevice;
private:
	DeviceFieldMap(FDevice* prev, FDevice* curr, FDevice* next);
    unique_ptr<FieldMapHandler> prev_device;
    unique_ptr<FieldMapHandler> curr_device;
    unique_ptr<FieldMapHandler> next_device;
};