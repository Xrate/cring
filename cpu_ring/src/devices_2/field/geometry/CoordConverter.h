#pragma once

#include "global.h"

namespace physics
{
	struct Plane;
	struct Vector;
}

struct Particle;
struct Geometry;

class CoordConverter
{
public:
	static               unique_ptr<CoordConverter> getConverter(      Geometry  geometry);
	       virtual const physics::Plane             getPlane    (const size_t    iS      ) const = 0;
	       virtual const physics::Vector            getMomentum (const Particle& p       , 
			                                                     const size_t    iS      ) const = 0;

		   virtual                                 ~CoordConverter() {}
};
