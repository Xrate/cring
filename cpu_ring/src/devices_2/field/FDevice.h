#pragma once

#include "global.h"
#include <devices_2/common/Device.h>

class DeviceFieldMap;
class CBeam;
struct DeviceParameters;

class FDevice : public virtual Device
{
public:
    explicit      FDevice       (const DeviceParameters& params  )               ;
    virtual      ~FDevice       (                                ){}
	virtual  void affectParticle(      Particle&         particle) const override;
protected:
    unique_ptr<DeviceFieldMap> fieldMap;
};