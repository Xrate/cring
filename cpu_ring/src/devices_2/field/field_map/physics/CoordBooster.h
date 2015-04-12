#pragma once

#include "global.h"

namespace physics
{
	struct Point;

	class CoordBooster
	{
	public:
		CoordBooster(double z, double x, double angle);
		Point convertPoint(Point p) const;
	private:
		const double Z;
		const double X;
		const double angle;
	};
}
