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
    explicit      FDevice       (const DeviceParameters& params  )               ;
    virtual      ~FDevice       (                                ){}
	virtual  void affectParticle(      Particle&         particle) const override;
	         void updateFieldMap(const FDevice*          prev    ,
								 const FDevice*          next    )               ;

	const string fieldMapName;
protected:
    unique_ptr<DeviceFieldMap> fieldMap;
	unique_ptr<CoordConverter> converter;
};