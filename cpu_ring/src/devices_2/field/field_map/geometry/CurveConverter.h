#pragma once

#include "CoordConverter.h"

struct DeviceGeometry;

class CurveConverter : public CoordConverter
{
public:
    explicit               CurveConverter  (const DeviceGeometry&   )               ;
    virtual        Point   toPlain         (      double    X       ,
                                                  double    Y       ,
												  size_t    iS      ) const override;
    virtual        Plane   getPlane        (	  size_t    iS      ) const override;
    virtual        Vector  getMomentum     (const Particle& p       ,
		                                          size_t    iS      ) const override;
    virtual        void    applyNewMomentum(      Particle& p       ,
                                            const Vector&   m       ,
											      size_t    iS      ) const override;
private:
                   double  getAngle        (	  size_t    iS      ) const         ;
                   double  getXCorrection  (      double    angle   ) const         ;

    const double rho;
    const double theta;
    const size_t nSteps;
};