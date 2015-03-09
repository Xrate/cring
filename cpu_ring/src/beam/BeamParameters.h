#pragma once
#include "global.h"

enum DistType { UNIFORM, GAUSSIAN };

struct TwissParameters
{
    TwissParameters(double alf, double bet, double emt);
    double alf;
    double bet;
    double gam;
    double emt;
    inline double coordMax() const { return sqrt(bet * emt); }
    inline double angleMax() const { return sqrt(gam * emt); }
};

struct BeamParameters 
{
    TwissParameters twissX;
    TwissParameters twissY;
    size_t numParticles;
    size_t numTurns;
    DistType distType;
    double momentum;
    double momentumSpread;

    static BeamParameters readBeamParameters(string fileName);
};
