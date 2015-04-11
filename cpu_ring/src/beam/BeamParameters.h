#pragma once
#include "global.h"

enum DistType { UNIFORM, GAUSSIAN };

struct TwissParameters
{
    double alf;
    double bet;
    double gam;
    double emt;
    double coordMax() const { return sqrt(bet * emt); }
    double angleMax() const { return sqrt(gam * emt); }
};

struct BeamParameters
{
    TwissParameters twissX;
    TwissParameters twissY;
    size_t numParticles;
    size_t numTurns;
    DistType distType;
    double energy;
    double momentumSpread;

	explicit BeamParameters(const double params[10]);
    static const BeamParameters& readBeamParameters(string fileName);
};
