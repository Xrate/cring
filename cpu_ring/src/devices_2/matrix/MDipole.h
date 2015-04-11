#pragma once

#include "MDevice.h"

class MDipole : public MDevice
{
public:
    explicit      MDipole           (const DeviceParameters& params)               ;
    virtual  void initMatrices      (                              )       override;
protected:
    double force;
};
