#pragma once

#include "MDevice.h"

class MDrift : public MDevice
{
public:
    explicit      MDrift      (const DeviceParameters& params)               ;
    virtual  void initMatrices(                              )       override;
};
