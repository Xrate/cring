#pragma once

#include "global.h"
#include "BeamConfig.h"

struct BeamConfig;
struct Particle;

class CBeam
{
public:
    explicit CBeam(BeamConfig params);
    inline size_t size() const;
    inline size_t turns() const;
    inline double path() const;
    void addPath(double step);
    inline vector<Particle>& particles();
    inline BeamConfig& parameters();
    inline const vector<Particle>& particles() const;
    inline const BeamConfig& parameters() const;
private:
    BeamConfig parameters_;
	vector<Particle> particles_;
    const size_t numParticles_;
    const size_t numTurns_;
    double path_;
};
