#pragma once

#include "MDevice.h"

class MQuadrupole : public MDevice
{
public:
    explicit      MQuadrupole       (const DeviceParameters&  params      )               ;
    virtual  void initMatrices      (                                     ) override      ;
             void affectBeam        (const shared_ptr<CBeam>  beam        ) const override;
private:
    friend   void generateMatrices  (const MQuadrupole*       quadrupole  ,
                                           vector<double[6]>& MxP_all     ,
                                           vector<double[6]>& MyP_all     ,
                                     const shared_ptr<CBeam>  beam        )               ;
             void affectParticle    (      Particle&          particle    ,
                                     const double             MxP_all[6]  ,
                                     const double             MyP_all[6]  ) const         ;

protected:
    double force;
};
