#pragma once

namespace physics
{
	class CoordBooster
	{
	public:
		CoordBooster(double z, double x, double angle);
	private:
		const double Z;
		const double X;
		const double angle;
	};
}
