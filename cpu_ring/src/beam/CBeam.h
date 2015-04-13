#pragma once

#include "global.h"
#include "BeamConfig.h"
#include <beam/Particle.h>

struct BeamConfig;
struct Particle;

class CBeam
{
public:
    explicit CBeam(BeamConfig params);
    size_t size() const;
    size_t turns() const;
    double path() const;
    void addPath(double step);
    vector<Particle>& particles();
    BeamConfig& parameters();
    const vector<Particle>& particles() const;
    const BeamConfig& parameters() const;
private:
    BeamConfig parameters_;
    vector<Particle> particles_;
    const size_t numParticles_;
    const size_t numTurns_;
    double path_;
};
