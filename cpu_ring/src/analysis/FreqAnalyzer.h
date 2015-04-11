#pragma once

#include "global.h"
#include "common/OutDirConfig.h"

class FreqAnalyzer
{
public:
    static void setUp(OutDirConfig dirConfig);
    static void print();
    static void calculate();
private:
    friend static void readParticleTraj(size_t iP, double* inX, double* inY);
    static string dirName_;
    static size_t nTurns_;
    static size_t nParticles_;
    static size_t nSteps_;
    static vector<double> Qx;
    static vector<double> Qy;
};
