#ifndef CBEAM_H
#define CBEAM_H
#include <vector>
#include "BeamParameters.h"

struct Particle
{
	size_t ID;
	double X;
	double aX;
	double Y;
	double aY;
	double dp;
};
typedef std::vector<Particle> ParticleVec;

class CBeam
{
public:
	explicit CBeam(const BeamParameters& parameters);
	void generateParticles(DistType dist_type);
private:
	void createUniformParticles();
	void createGaussianParticles();
	// Fields
	BeamParameters parameters_;
	ParticleVec particles_;
};

#endif // CBEAM_H