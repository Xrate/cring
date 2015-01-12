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

class DeviceParameters
{
public:
	DeviceParameters(std::string name, DeviceType type, 
					 double length, double force, 
					 double apperture_x, double apperture_y);

	std::string name() const;
	DeviceType type() const;
	double length() const;
	double force() const;
	double appertureX() const;
	double appertureY() const;
	size_t nSteps() const;

private:
	std::string name_;
	DeviceType type_;
	double length_;
	double force_;
	double appertureX_;
	double appertureY_;
	size_t nSteps_;
};

#endif // DEVICEPARAMETERS_H
