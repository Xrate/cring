#pragma once

#include "devices_2/matrix/MQuadrupole.h"
#include "devices_2/field/FDevice.h"

class FMQuadrupole : public MQuadrupole, public FDevice
{
public:
    explicit      FMQuadrupole  (const DeviceParameters& params  )               ;
	virtual  void affectParticle(      Particle&         particle) const override;
};