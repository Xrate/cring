#pragma once

#include <global.h>

enum DeviceType // Number is nSteps for device (cannot be the same!)
{
    DIPOLE = 200,
    DRIFT = 500,
    QUADRUPOLE = 20,
    SEXTUPOLE = 15
};

struct DeviceParameters
{
    string name_;
    DeviceType type_;
    double length_;
    double force_;
    double appertureX_;
    double appertureY_;
    string mapFileName_;
};
