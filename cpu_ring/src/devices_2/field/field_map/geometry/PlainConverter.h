#pragma once
#include "CoordConverter.h"

struct DeviceGeometry;

class PlainConverter : public CoordConverter
{
public:
    explicit               PlainConverter(const DeviceGeometry&   )               ;
    virtual        Point   toPlain       (      double    X       ,
                                                double    Y       ) const override;
    virtual        Plane   getNextPlane  (                        ) const override;
    virtual        Vector  getMomentum   (const Particle& p       ) const override;
    virtual        void    applyNewMomentum(      Particle& p       ,
                                          const Vector&   m       ) const override;

private:
                   double  getCurrentZ   (                        ) const         ;
                   double  getNextZ      (                        ) const         ;

    const double length;
    const size_t nSteps;
};