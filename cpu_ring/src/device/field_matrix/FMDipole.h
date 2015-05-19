#pragma once

#include <device/matrix/MDipole.h>
#include <device/field/FDevice.h>

class FMDipole : public MDipole, public FDevice
{
public:
    explicit      FMDipole      (const DeviceParameters& params  )               ;
    virtual  void affectParticle(      Particle&         particle) const override;
    virtual  void affectEllipses(      BeamConfig*       params  ) const override;
};