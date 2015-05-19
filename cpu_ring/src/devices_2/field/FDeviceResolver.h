#pragma once
#include <vector>
#include <memory>

using std::vector;
using std::shared_ptr;

class Device;

class FDeviceResolver
{
public:
	static vector<shared_ptr<Device>> CastNonFieldDevices(vector<shared_ptr<Device>> pre_devices);
};
