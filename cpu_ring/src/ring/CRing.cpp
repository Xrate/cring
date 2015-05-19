#include "CRing.h"
#include <ctime>
#include <ring/RingConfig.h>
#include <device/field/FDeviceResolver.h>
#include <device/common/Device.h>
#include <beam/CBeam.h>

shared_ptr<const CRing> CRing::instance;

shared_ptr<const CRing> CRing::createInstance(const shared_ptr<const RingConfig> config)
{
    if (!instance) 
		instance = shared_ptr<CRing const>(new CRing(config));
    return instance;
}

shared_ptr<const CRing> CRing::getInstance()
{
    if (instance) return instance;
    throw exception("CRing: Try to access null CRing");
}

CRing::CRing(shared_ptr<const RingConfig> config) :
nSteps(0)
{
	vector<shared_ptr<Device>> pre_devices;
    for (string name : config->structure)
    {
        auto deviceParams = config->devices.at(name);
        auto device = createDevice(deviceParams);
        nSteps += static_cast<size_t>(deviceParams.type_);
        pre_devices.push_back(device);
    }

	devices = FDeviceResolver::CastNonFieldDevices(pre_devices);
    numDevices = devices.size();
}

void CRing::affectBeam(shared_ptr<CBeam> beam) const
{
    clock_t begin = clock();

    for (int iT = 0; iT < beam->turns(); ++iT)
    for (auto device : devices)
        device->affectBeam(beam);

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    cout << "Time of traj: " << elapsed_secs << "s. " << endl;
}

size_t CRing::numSteps() const
{
    return nSteps;
}