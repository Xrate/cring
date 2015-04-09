#pragma once

#include "MDevice.h"

class MDrift : public MDevice
{
public:
    explicit      MDrift      (const DeviceParameters& params)               ;
    virtual  void initMatrices(                              ) override      ;
    virtual  void affectBeam  (const shared_ptr<CBeam> beam  ) const override;
};
