#pragma once

#include "beam/BeamConfig.h"
#include "beam/Particle.h"

class IParticleCreator
{
public:
    static shared_ptr<IParticleCreator> getParticleCreator(DistType distType);
    void createParticles(const BeamConfig& params, vector<Particle>& particles);
protected:
    IParticleCreator() = default;
    virtual Particle createParticle(const BeamConfig& params) = 0;
    virtual ~IParticleCreator() {}
};

class UniformParticleCreator : public IParticleCreator
{
protected:
    virtual Particle createParticle(const BeamConfig& params) override;
};

class GaussianParticleCreator : public IParticleCreator
{
protected:
    virtual Particle createParticle(const BeamConfig& params) override;
};