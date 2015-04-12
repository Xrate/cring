#pragma once

#include "global.h"

namespace physics
{
	struct Point;
	struct Vector;
	struct Plane;
}
using namespace physics;

class GeometryHelper
{
public:
	static const Vector& calculateNewMomentum(const Vector& momentum,
		                                      const Point&  field   ,
		                                      const Plane&  newPlane);
};
