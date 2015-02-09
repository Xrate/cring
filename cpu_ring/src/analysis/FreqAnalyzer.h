#pragma once

#include "../global.h"
#include "../common/OutDirConfig.h"
#include <fftw3.h>

class FreqAnalyzer
{
public:
	static void setUp(OutDirConfig dirConfig);
	static void print();
	static void calculate();
private:
	static void readParticleTraj(size_t iP, double* inX, double* inY);
	static double findFrequency(fftw_plan& plan, double* in, fftw_complex* out);
	static string dirName_;
	static size_t nTurns_;
	static size_t nParticles_;
	static size_t nSteps_;
	static vector<double> Qx;
	static vector<double> Qy;
};
