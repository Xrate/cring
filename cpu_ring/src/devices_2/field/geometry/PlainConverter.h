﻿#pragma once
#include "CoordConverter.h"

class PlainConverter : public CoordConverter
{
public:
	explicit               PlainConverter(DeviceGeometry  geometry)               ;
	virtual  const Point&  getPlainCoord (      double    X       ,
		                                        double    Y       ) const override;
	virtual  const Plane&  getNextPlane  (                        ) const override;
	virtual  const Vector& getMomentum   (const Particle& p       ) const override;
	virtual        void    updateParticle(      Particle& p       ,
		                                  const Vector&   m       ) const override;

private:
	               double  getCurrentZ   (                        ) const         ;
	               double  getNextZ      (                        ) const         ;

	const double length;
	const size_t nSteps;
};