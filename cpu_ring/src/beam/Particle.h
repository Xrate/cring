#pragma once

#include "global.h"

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