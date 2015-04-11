#pragma once

#include "global.h"

struct BeamConfig;
struct Particle;
class CBeam;
struct DeviceParameters;

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
    explicit      Device        (const DeviceParameters& params  )          ;
    virtual      ~Device        (                                ){}
    virtual  void affectBeam    (const shared_ptr<CBeam> beam    ) const    ;
	virtual  void affectParticle(      Particle&         particle) const = 0;
	virtual  void affectEllipses(      BeamConfig*       params  ) const = 0;
protected:
            Geometry geometry;
            string   name;
	mutable size_t   curr_step;
};