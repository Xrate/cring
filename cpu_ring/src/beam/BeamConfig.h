#pragma once
#include "global.h"

enum DistType { UNIFORM, GAUSSIAN };

struct Twiss
{
    double alf;
    double bet;
    double gam;
    double emt;
    double coordMax() const { return sqrt(bet * emt); }
    double angleMax() const { return sqrt(gam * emt); }
};

struct BeamConfig
{
    Twiss twissX;
    Twiss twissY;
    size_t numParticles;
    size_t numTurns;
    DistType distType;
    double energy;
    double momentumSpread;

    explicit BeamConfig(const double params[10]);
    static BeamConfig readBeamConfig(string fileName);
};
