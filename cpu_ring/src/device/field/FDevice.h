#pragma once

#include <global.h>
#include <device/common/Device.h>

class DeviceFieldMap;
class ICoordConverter;
class CBeam;
struct DeviceParameters;

class FDevice : public virtual Device
{
public:
    virtual      ~FDevice        (                                )            = 0 {}
    explicit      FDevice        (const DeviceParameters& params  )               ;
    virtual  void affectParticle (      Particle&         particle) const override;
             bool spotFieldDevice(const FDevice*          prev    ,
                                  const FDevice*          next    )               ;

    string fieldMapName;
protected:
    shared_ptr<DeviceFieldMap> fieldMap;
};