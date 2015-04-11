#pragma once

#include "devices_2/matrix/MDipole.h"
#include "devices_2/field/FDevice.h"

class FMDipole : public MDipole, public FDevice
{
public:
    explicit      FMDipole      (const DeviceParameters& params  )               ;
	virtual  void affectParticle(      Particle&         particle) const override;
};