#pragma once

#include "global.h"

namespace physics
{
	struct Plane;
	struct Vector;
	struct Point;
}

using namespace physics;

struct Particle;
struct DeviceGeometry;

class CoordConverter
{
public:
	static        CoordConverter*  getConverter   (DeviceGeometry  geometry)               ;

	virtual const Point&           getPlainCoord  (      double    X       ,
		                                                 double    Y       ) const      = 0;
	virtual const Plane&           getNextPlane   (                        ) const      = 0;
	virtual const Vector&          getMomentum    (const Particle& p       ) const      = 0;
	virtual       void             updateParticle (      Particle& p       ,
		                                           const Vector&   m       ) const      = 0;

	              void             trackDeviceStep(const size_t&   iS      )               ;

	virtual                       ~CoordConverter(){}

protected:
	const size_t*  dev_step;
};