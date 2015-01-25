#ifndef DEVICEPARAMETERS_H
#define DEVICEPARAMETERS_H
#include "../global.h"

enum DeviceType // Number is nSteps for device (cannot be the same!)
{
	DIPOLE = 25,
	DRIFT = 10,
	QUADRUPOLE = 20,
	SEXTUPOLE = 15
};

struct DeviceParameters
{
	DeviceParameters(string name, DeviceType type, 
					 double length, double force, 
					 double apperture_x, double apperture_y);
	string name;
	DeviceType type;
	double length;
	double force;
	double appertureX;
	double appertureY;
};

#endif // DEVICEPARAMETERS_H
