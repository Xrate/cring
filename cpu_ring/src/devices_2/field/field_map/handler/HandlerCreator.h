#pragma once

#include "global.h"

struct DeviceGeometry;
class FieldMapHandler;

class HandlerCreator
{
public:
	static FieldMapHandler* getPrevHandler(const DeviceGeometry& curr,
	                                       const DeviceGeometry& prev,
	                                       const string& field_map);

	static FieldMapHandler* getCurrHandler(const string& field_map);

	static FieldMapHandler* getNextHandler(const DeviceGeometry& curr,
	                                       const DeviceGeometry& next,
	                                       const string& field_map);
};
