#pragma once

#include "CoordConverter.h"

namespace physics
{
	struct Point;
}

class CurveConverter : public CoordConverter
{
public:
	explicit               CurveConverter (      Geometry  geometry)               ;
	virtual  const Plane&  getNextPlane   (                        ) const override;
	virtual  const Vector& getMomentum    (const Particle& p       ) const override;
	virtual        void    updateParticle (      Particle& p       ,
		                                   const Vector&   m       ) const override;
private:
	               double  getCurrentAngle(                        ) const         ;
	               double  getNextAngle   (                        ) const         ;
	               double  getXCorrection (      double    angle   ) const         ;
	               Point   convertToPlain (      double    X       , 
					                             double    Y       ,
												 double    angle   ) const         ;

	const double rho;
	const double theta;
	const size_t nSteps;
};