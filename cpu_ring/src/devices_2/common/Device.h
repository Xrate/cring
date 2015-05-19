#pragma once

#include "global.h"
#include "DeviceGeometry.h"

struct BeamConfig;
struct Particle;
class CBeam;
struct DeviceParameters;

class Device
{
public:
    virtual      ~Device        (                                )       = 0 {}
    explicit      Device        (const DeviceParameters& params  )          ;
    virtual  void affectBeam    (const shared_ptr<CBeam> beam    ) const    ;
    virtual  void affectParticle(      Particle&         particle) const = 0;
    virtual  void affectEllipses(      BeamConfig*       params  ) const = 0;
protected:
            DeviceGeometry geometry;
            string         name;
    mutable size_t         curr_step;
};

shared_ptr<Device> createDevice(const DeviceParameters& params);