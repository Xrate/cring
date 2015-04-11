#pragma once

#include "MDevice.h"

class MQuadrupole : public MDevice
{
public:
    explicit      MQuadrupole       (const DeviceParameters&  params    )               ;
    virtual  void initMatrices      (                                   )       override;
private:
             void affectParticle    (      Particle&          particle  ) const override;

	friend   void generateMatrices  (const MQuadrupole*       quadrupole,
				                     const Particle&          particle  ,
								           double             MxP[6]    ,
				                           double             MyP[6]    )                 ;

protected:
    double force;
};
