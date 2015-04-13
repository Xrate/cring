#include "CRing.h"
#include <ctime>
#include <typeinfo>
#include "RingConfig.h"
#include <devices_2/common/Device.h>
#include <devices_2/common/DeviceFactory.h>
#include <beam/CBeam.h>
#include <devices_2/field/FDevice.h>
#include <devices_2/field_matrix/FMDipole.h>
#include <devices_2/field_matrix/FMDrift.h>
#include <devices_2/field_matrix/FMQuadrupole.h>

shared_ptr<const CRing> CRing::instance;

shared_ptr<const CRing> CRing::createInstance(const shared_ptr<const RingConfig> config)
{
    if (!instance) instance = shared_ptr<CRing const>(new CRing(config));
    return instance;
}

shared_ptr<const CRing> CRing::getInstance()
{
    if (instance) return instance;
    throw exception("CRing: Try to access null CRing");
}

static shared_ptr<Device> ProcessNeighborsAffection(Device** curr, const FDevice* prev, const FDevice* next)
{
    FDevice* f_curr = dynamic_cast<FDevice*>(*curr);
    if (typeid(*f_curr) == typeid(FMDipole))
    {
        if (f_curr->spotFieldDevice(prev, next))
        {
            auto fmPtr = dynamic_cast<FMDipole*>(f_curr);
            return shared_ptr<FMDipole>(fmPtr);
        }
        else
        {
            auto mPtr = new MDipole(*dynamic_cast<FMDipole*>(f_curr));
            delete *curr; *curr = nullptr;
            return shared_ptr<MDipole>(mPtr);
        }
    }
    if (typeid(*f_curr) == typeid(FMDrift))
    {
        if (f_curr->spotFieldDevice(prev, next))
        {
            auto fmPtr = dynamic_cast<FMDrift*>(f_curr);
            return shared_ptr<FMDrift>(fmPtr);
        }
        else
        {
            auto mPtr = new MDrift(*dynamic_cast<FMDrift*>(f_curr));
            delete *curr; *curr = nullptr;
            return shared_ptr<MDrift>(mPtr);
        }
    }
    if (typeid(*f_curr) == typeid(FMQuadrupole))
    {
        if (f_curr->spotFieldDevice(prev, next))
        {
            auto fmPtr = dynamic_cast<FMQuadrupole*>(f_curr);
            return shared_ptr<FMQuadrupole>(fmPtr);
        }
        else
        {
            auto mPtr = new MQuadrupole(*dynamic_cast<FMQuadrupole*>(f_curr));
            delete *curr; *curr = nullptr;
            return shared_ptr<MQuadrupole>(mPtr);
        }
    }

    throw exception("Unknown device type.");
}

static FDevice* getPrevDevice(vector<Device*> pre_devices, size_t i)
{
    if (i != 0)
        return dynamic_cast<FDevice*>(pre_devices.at(i - 1));

    return dynamic_cast<FDevice*>(pre_devices.at(pre_devices.size() - 1));
}

static FDevice* getNextDevice(vector<Device*> pre_devices, size_t i)
{
    if (i != pre_devices.size() - 1)
        return dynamic_cast<FDevice*>(pre_devices.at(i + 1));

    return dynamic_cast<FDevice*>(pre_devices.at(0));
}

CRing::CRing(shared_ptr<const RingConfig> config) :
nSteps(0)
{
    vector<Device*> pre_devices;
    for (string name : config->structure)
    {
        auto deviceParams = config->devices.at(name);
        auto device = DeviceFactory::createDevice(deviceParams);
        nSteps += static_cast<size_t>(deviceParams.type_);
        pre_devices.push_back(device);
    }

    for (size_t i = 0; i < pre_devices.size(); ++i)
    {
        const FDevice* prev = getPrevDevice(pre_devices, i);
        const FDevice* next = getNextDevice(pre_devices, i);
        devices.push_back(ProcessNeighborsAffection(&pre_devices[i], prev, next));
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

size_t CRing::numSteps() const
{
    return nSteps;
}