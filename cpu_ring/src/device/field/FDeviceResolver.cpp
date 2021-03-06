﻿#include "FDeviceResolver.h"
#include "FDevice.h"

#include <device/field_matrix/FMDipole.h>
#include <device/field_matrix/FMDrift.h>
#include <device/field_matrix/FMQuadrupole.h>

template <typename F, typename T>
static shared_ptr<Device> ResolveType(FDevice* curr, const FDevice* prev, const FDevice* next)
{
	if (curr->spotFieldDevice(prev, next))
	{
		auto mPtr = new F(*dynamic_cast<F*>(curr));
		return shared_ptr<F>(mPtr);
	}

	auto mPtr = new T(*dynamic_cast<F*>(curr));
	return shared_ptr<T>(mPtr);
}

static shared_ptr<Device> ProcessNeighborsAffection(shared_ptr<Device> curr, const FDevice* prev, const FDevice* next)
{
	FDevice* f_curr = dynamic_cast<FDevice*>(curr.get());
	if (typeid(*f_curr) == typeid(FMDipole))
		return ResolveType<FMDipole, MDipole>(f_curr, prev, next);

	if (typeid(*f_curr) == typeid(FMDrift))
		return ResolveType<FMDrift, MDrift>(f_curr, prev, next);

	if (typeid(*f_curr) == typeid(FMQuadrupole))
		return ResolveType<FMQuadrupole, MQuadrupole>(f_curr, prev, next);

	throw exception("Unknown device type.");
}

static FDevice* getPrevDevice(vector<shared_ptr<Device>> pre_devices, size_t i)
{
	return dynamic_cast<FDevice*>(i != 0
		                              ? pre_devices.at(i - 1).get()
		                              : pre_devices.at(pre_devices.size() - 1).get());
}

static FDevice* getNextDevice(vector<shared_ptr<Device>> pre_devices, size_t i)
{
	return dynamic_cast<FDevice*>(i != pre_devices.size() - 1
		                              ? pre_devices.at(i + 1).get()
		                              : pre_devices.at(0).get());
}

vector<shared_ptr<Device>> FDeviceResolver::CastNonFieldDevices(vector<shared_ptr<Device>> pre_devices)
{
	auto result = vector<shared_ptr<Device>>();
	result.reserve(pre_devices.size());

	for (size_t i = 0; i < pre_devices.size(); ++i)
	{
		const FDevice* prev = getPrevDevice(pre_devices, i);
		const FDevice* next = getNextDevice(pre_devices, i);
		result.push_back(ProcessNeighborsAffection(pre_devices[i], prev, next));
	}
	return result;
}
