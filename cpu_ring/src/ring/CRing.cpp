#include "CRing.h"
#include <ctime>

shared_ptr<const CRing> CRing::instance;

shared_ptr<const CRing> CRing::createInstance(const shared_ptr<const RingConfig> config)
{
    if (!instance) instance = make_shared<CRing const>(config);
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
    for (string name : config->structure)
    {
        auto deviceParams = config->devices.at(name);
        auto device = CDevice::createDevice(deviceParams);
        nSteps += static_cast<size_t>(deviceParams.type_);
        devices.push_back(device);
    }
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

inline size_t CRing::numSteps() const
{
    return nSteps;
}