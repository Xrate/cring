#pragma once

#include "global.h"
#include "RingConfig.h"
#include "device/CDevice.h"

class CRing
{
public:
    static shared_ptr<const CRing> createInstance(const shared_ptr<const RingConfig> config);
    static shared_ptr<const CRing> getInstance();
    void affectBeam(shared_ptr<CBeam> beam) const;
    inline size_t numSteps() const;
private:
    explicit CRing(shared_ptr<const RingConfig> config);

    static shared_ptr<const CRing> instance;
    size_t numDevices;
    size_t nSteps;
    vector<shared_ptr<const CDevice>> devices;
};