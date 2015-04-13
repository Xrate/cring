#pragma once

#include "global.h"
#include "devices_2/common/Device.h"

struct BeamConfig;
struct Particle;

class MDevice : public virtual Device
{
public:
    virtual      ~MDevice            (                                )                = 0 {}
    explicit      MDevice            (const DeviceParameters& params  )                   ;
protected:
    virtual  void initMatrices       (                                )                = 0;
             void initTwissMatrices  (                                )                   ;
    virtual  void affectEllipses     (      BeamConfig*       params  ) const override    ;
    virtual  void affectParticle     (      Particle&         particle) const override    ;

    double mX_P[6];
    double mY_P[6];
    double mX_T[9];
    double mY_T[9];
};