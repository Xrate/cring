#pragma once
#include "ICoordConverter.h"

struct DeviceGeometry;

class PlainConverter : public ICoordConverter
{
public:
    explicit               PlainConverter  (const DeviceGeometry&   )               ;
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
                   double  getZ            (      size_t    iS      ) const         ;

    const double length;
    const size_t nSteps;
};