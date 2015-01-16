#ifndef CBEAM_H
#define CBEAM_H
#include "../global.h"
#include "BeamParameters.h"

struct Particle
{
	size_t ID;
	bool isAlive;
	double X;
	double aX;
	double Y;
	double aY;
	double dp;
};
typedef vector<Particle> ParticleVec;

class CBeam
{
	friend class CDevice;
public:
	explicit CBeam(BeamParameters parameters);
	void generateParticles(DistType dist_type);
private:
	void createUniformParticles();
	void createGaussianParticles();
	// Fields
	BeamParameters parameters_;
	ParticleVec particles_;
	size_t numParticles;
};

#endif // CBEAM_H