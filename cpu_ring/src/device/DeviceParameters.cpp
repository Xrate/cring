#include "DeviceParameters.h"

DeviceParameters::DeviceParameters(string name_, DeviceType type_, 
								  double length_, double force_, 
								  double apperture_x, double apperture_y): 
name(name_), type(type_), length(length_), force(force_), 
appertureX(apperture_x), appertureY(apperture_y)
{
}