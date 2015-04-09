#pragma once

#include "devices_2/matrix/MDrift.h"
#include "devices_2/field/FDevice.h"

class FMDrift : public MDrift, public FDevice
{
public:
    explicit     FMDrift   (const DeviceParameters& params)               ;
    virtual void affectBeam(const shared_ptr<CBeam> beam  ) const override;
};