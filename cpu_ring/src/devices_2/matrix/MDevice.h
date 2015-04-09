#pragma once

#include "global.h"
#include "devices_2/common/Device.h"

class BeamParameters;
class Particle;

class MDevice : public virtual Device
{
public:
    explicit      MDevice            (const DeviceParameters& params)          ;
    virtual      ~MDevice            (                              ){}
    virtual  void affectBeam         (const shared_ptr<CBeam> beam  ) const = 0;
protected:
    virtual  void initMatrices       (                              )       = 0;
             void initTwissMatrices  (                              )          ;
             void affectEllipses     (BeamParameters *params        ) const    ;
             void affectParticle     (Particle& particle            ) const    ;

protected:
    double mX_P[6];
    double mY_P[6];
    double mX_T[9];
    double mY_T[9];
};