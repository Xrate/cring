#include "DeviceParameters.h"

DeviceParameters::DeviceParameters(std::string name, DeviceType type, 
								  double length, double force, 
								  double apperture_x, double apperture_y): 
name_(name), type_(type), length_(length), force_(force), 
appertureX_(apperture_x), appertureY_(apperture_y)
{
}

std::string DeviceParameters::name() const
{
	return name_;
}

DeviceType DeviceParameters::type() const
{
	return type_;
}

double DeviceParameters::length() const
{
	return length_;
}

double DeviceParameters::force() const
{
	return force_;
}

double DeviceParameters::appertureX() const
{
	return appertureX_;
}

double DeviceParameters::appertureY() const
{
	return appertureY_;
}