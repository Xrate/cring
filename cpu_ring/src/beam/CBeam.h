#pragma once

#include "global.h"
#include "beam/BeamParameters.h"
#include "beam/Particle.h"

class CBeam
{
public:
    explicit CBeam(BeamParameters params);
    size_t size() const;
    size_t turns() const;
    double path() const;
    void addPath(double step);
    ParticleVec& particles();
    BeamParameters& parameters();
    const ParticleVec& particles() const;
    const BeamParameters& parameters() const;
private:
    BeamParameters parameters_;
    ParticleVec particles_;
    const size_t numParticles_;
    const size_t numTurns_;
    double path_;
};

inline size_t CBeam::size() const
{
    return numParticles_;
}

inline size_t CBeam::turns() const
{
    return numTurns_;
}

inline double CBeam::path() const
{
    return path_;
}

inline void CBeam::addPath(double step)
{
    path_ += step;
}