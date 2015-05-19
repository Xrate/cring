#pragma once

#include <device/matrix/MDrift.h>
#include <device/field/FDevice.h>

class FMDrift : public MDrift, public FDevice
{
public:
    explicit      FMDrift       (const DeviceParameters& params  )               ;
    virtual  void affectParticle(      Particle&         particle) const override;
    virtual  void affectEllipses(      BeamConfig*       params  ) const override;
};