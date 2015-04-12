#pragma once

#include "global.h"

namespace physics
{
	struct Plane;
	struct Vector;
}

using namespace physics;

struct Particle;
struct Geometry;

class CoordConverter
{
public:
	static        CoordConverter*  getConverter   (      Geometry  geometry)               ;
	virtual const Plane&           getNextPlane   (                        ) const      = 0;
	virtual const Vector&          getMomentum    (const Particle& p       ) const      = 0;
	virtual       void             updateParticle (      Particle& p       ,
		                                           const Vector&   m       ) const      = 0;

	              void             trackDeviceStep(const size_t&   iS      )               ;

	virtual                       ~CoordConverter(){}

protected:
	const size_t*  dev_step;
};