#ifndef DEVICEPARAMETERS_H
#define DEVICEPARAMETERS_H
#include "../global.h"

enum DeviceType
{
	DIPOLE,
	DRIFT,
	QUADRUPOLE,
	SEXTUPOLE
};

struct DeviceParameters
{
	DeviceParameters(std::string name, DeviceType type, 
					 double length, double force, 
					 double apperture_x, double apperture_y);
	string name;
	DeviceType type;
	double length;
	double force;
	double appertureX;
	double appertureY;
	size_t nSteps;
};

#endif // DEVICEPARAMETERS_H
