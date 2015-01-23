#ifndef CBEAM_H
#define CBEAM_H
#include "../global.h"
#include "BeamParameters.h"

struct Particle
{
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
	friend class Logger;
public:
	explicit CBeam(BeamParameters parameters);
	void generateParticles(DistType dist_type);
	~CBeam();
private:
	void createUniformParticles();
	void createGaussianParticles();
	// Fields
	BeamParameters parameters_;
	ParticleVec particles_;
	const size_t numParticles_;
	double path_;
};

#endif // CBEAM_H