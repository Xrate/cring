#include "CBeam.h"
#include "ParticleCreator/ParticleCreator.h"

CBeam::CBeam(BeamParameters parameters) :
parameters_(parameters),
particles_(parameters.numParticles),
numParticles_(parameters.numParticles),
numTurns_(parameters.numTurns),
path_(0)
{
	auto creator = IParticleCreator::getParticleCreator(parameters_.distType);
	creator->createParticles(parameters_, particles_);
}

ParticleVec& CBeam::particles()
{
	return particles_;
}

BeamParameters& CBeam::parameters()
{
	return parameters_;
}

const ParticleVec& CBeam::particles() const
{
	return particles_;
}

const BeamParameters& CBeam::parameters() const
{
	return parameters_;
}