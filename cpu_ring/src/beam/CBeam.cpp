#include "CBeam.h"
#include "beam/ParticleCreator/ParticleCreator.h"
#include "BeamConfig.h"

CBeam::CBeam(BeamConfig parameters) :
parameters_(parameters),
particles_(parameters.numParticles),
numParticles_(parameters.numParticles),
numTurns_(parameters.numTurns),
path_(0)
{
    auto creator = IParticleCreator::getParticleCreator(parameters_.distType);
    creator->createParticles(parameters_, particles_);
}

inline ParticleVec& CBeam::particles()
{
    return particles_;
}

inline BeamConfig& CBeam::parameters()
{
    return parameters_;
}

inline const ParticleVec& CBeam::particles() const
{
    return particles_;
}

inline const BeamConfig& CBeam::parameters() const
{
    return parameters_;
}

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

void CBeam::addPath(double step)
{
    path_ += step;
}