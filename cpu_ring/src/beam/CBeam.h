#pragma once

#include "global.h"
#include "beam/BeamParameters.h"
#include "beam/Particle.h"

class CBeam
{
public:
    explicit CBeam(BeamParameters params);
    inline size_t size() const;
    inline size_t turns() const;
    inline double path() const;
    void addPath(double step);
    inline ParticleVec& particles();
    inline BeamParameters& parameters();
    inline const ParticleVec& particles() const;
    inline const BeamParameters& parameters() const;
private:
    BeamParameters parameters_;
    ParticleVec particles_;
    const size_t numParticles_;
    const size_t numTurns_;
    double path_;
};
