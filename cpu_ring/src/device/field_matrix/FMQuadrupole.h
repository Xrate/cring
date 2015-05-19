#pragma once

#include <device/matrix/MQuadrupole.h>
#include <device/field/FDevice.h>

class FMQuadrupole : public MQuadrupole, public FDevice
{
public:
    explicit      FMQuadrupole  (const DeviceParameters& params  )               ;
    virtual  void affectParticle(      Particle&         particle) const override;
    virtual  void affectEllipses(      BeamConfig*       params  ) const override;
};