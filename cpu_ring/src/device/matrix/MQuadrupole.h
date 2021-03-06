#pragma once

#include "MDevice.h"

class FMQuadrupole;

class MQuadrupole : public MDevice
{
public:
    explicit      MQuadrupole       (const DeviceParameters&  params    )               ;
    virtual  void initMatrices      (                                   )       override;
             void affectParticle    (      Particle&          particle  ) const override;
private:
    friend   void generateMatrices  (const MQuadrupole*       quadrupole,
                                     const Particle&          particle  ,
                                           double             MxP[6]    ,
                                           double             MyP[6]    )               ;

protected:
    double force;
};
