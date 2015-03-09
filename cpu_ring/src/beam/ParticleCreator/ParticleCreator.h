#pragma once

#include "beam/BeamParameters.h"
#include "beam/Particle.h"

class IParticleCreator
{
public:
    static shared_ptr<IParticleCreator> getParticleCreator(DistType distType);
    void createParticles(const BeamParameters& params, ParticleVec& particles);
protected:
    IParticleCreator() = default;
    virtual Particle createParticle(const BeamParameters& params) = 0;
};

class UniformParticleCreator : public IParticleCreator
{
protected:
    virtual Particle createParticle(const BeamParameters& params);
};

class GaussianParticleCreator : public IParticleCreator
{
protected:
    virtual Particle createParticle(const BeamParameters& params);
};