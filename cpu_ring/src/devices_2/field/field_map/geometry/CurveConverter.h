#pragma once

#include "CoordConverter.h"

struct DeviceGeometry;

class CurveConverter : public CoordConverter
{
public:
    explicit               CurveConverter  (const DeviceGeometry&   )               ;
    virtual        Point   toPlain         (      double    X       ,
                                                  double    Y       ) const override;
    virtual        Plane   getNextPlane    (                        ) const override;
    virtual        Vector  getMomentum     (const Particle& p       ) const override;
    virtual        void    applyNewMomentum(      Particle& p       ,
                                            const Vector&   m       ) const override;
private:
                   double  getCurrentAngle (                        ) const         ;
                   double  getNextAngle    (                        ) const         ;
                   double  getXCorrection  (      double    angle   ) const         ;
                   Point   convertToPlain  (      double    X       , 
                                                  double    Y       ,
                                                  double    angle   ) const         ;

    const double rho;
    const double theta;
    const size_t nSteps;
};