#pragma once

#include "global.h"
#include <devices_2/common/Device.h>

class DeviceFieldMap;
class CoordConverter;
class CBeam;
struct DeviceParameters;

class FDevice : public virtual Device
{
public:
    explicit      FDevice        (const DeviceParameters& params  )               ;
    virtual      ~FDevice        (                                )            = 0 {}
    virtual  void affectParticle (      Particle&         particle) const override;
             bool spotFieldDevice(const FDevice*          prev    ,
                                  const FDevice*          next    )               ;

    const string fieldMapName;
protected:
    shared_ptr<DeviceFieldMap> fieldMap;
};