#pragma once

#include "MDevice.h"

class FMDrift;

class MDrift : public MDevice
{
public:
    explicit      MDrift      (const DeviceParameters& params)               ;
    virtual  void initMatrices(                              )       override;
};
