#pragma once

#include "MDevice.h"

class MDipole : public MDevice
{
public:
    explicit      MDipole           (const DeviceParameters& params)               ;
    virtual  void initMatrices      (                              ) override      ;
    virtual  void affectBeam        (const shared_ptr<CBeam> beam  ) const override;
protected:
    double force;
};
