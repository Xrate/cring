#pragma once

#include "global.h"

class CBeam;
class DeviceParameters;

struct Geometry
{
    double length;
    double angle;
    double step;
    double appertureX;
    double appertureY;
    size_t nSteps;
};

class Device
{
public:
    explicit Device(const DeviceParameters& params);
    virtual ~Device(){}
    virtual void affectBeam(const shared_ptr<CBeam> beam) const = 0;
protected:
    Geometry geometry;
    string name;
};