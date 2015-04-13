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

CRing::CRing(shared_ptr<const RingConfig> config) :
nSteps(0)
{
    for (string name : config->structure)
    {
        auto deviceParams = config->devices.at(name);
        auto device = DeviceFactory::createDevice(deviceParams);
        nSteps += static_cast<size_t>(deviceParams.type_);
        devices.push_back(device);
    }
    numDevices = devices.size();

    for (size_t i = 0; i < numDevices; ++i)
    {
        FDevice* curr = dynamic_cast<FDevice*>(devices.at(i).get());
        const FDevice* prev;
        const FDevice* next;
        if (i == 0)
        {
            prev = dynamic_cast<const FDevice*>(devices.at(numDevices - 1).get());
            next = dynamic_cast<const FDevice*>(devices.at(1).get());
        }
        else if (i == numDevices - 1)
        {
            prev = dynamic_cast<const FDevice*>(devices.at(numDevices - 2).get());
            next = dynamic_cast<const FDevice*>(devices.at(0).get());
        }
        else
        {
            prev = dynamic_cast<const FDevice*>(devices.at(i-1).get());
            next = dynamic_cast<const FDevice*>(devices.at(i+1).get());
        }

        if (!curr->spotFieldDevice(prev, next))
        {
            if (typeid(*curr) == typeid(FMDipole))
            {
                auto mPtr = new MDipole(*dynamic_cast<FMDipole*>(curr));
                devices.at(i).reset();
                devices[i] = shared_ptr<MDipole>(mPtr);
            }
            else if (typeid(*curr) == typeid(FMDrift))
            {
                auto mPtr = new MDrift(*dynamic_cast<FMDrift*>(curr));
                devices.at(i).reset();
                devices[i] = shared_ptr<MDrift>(mPtr);
            }
            else if (typeid(*curr) == typeid(FMQuadrupole))
            {
                auto mPtr = new MQuadrupole(*dynamic_cast<FMQuadrupole*>(curr));
                devices.at(i).reset();
                devices[i] = shared_ptr<MQuadrupole>(mPtr);
            }
            else
                throw new exception("Unknow device type.");
        }
    }
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