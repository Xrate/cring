#ifndef FREQANALYZER_H
#define FREQANALYZER_H
#include "../global.h"
#include <fftw3.h>

class FreqAnalyzer
{
public:
	static void setUp(string dirName, size_t turns, size_t size, size_t num_steps);
	static void print();
	static void calculate();
private:
	static void readParticleTraj(size_t iP, double* inX, double* inY);
	static double findFrequency(fftw_plan& plan, fftw_complex* out);
	static string dirName_;
	static size_t nTurns_;
	static size_t nParticles_;
	static size_t nSteps_;
	static vector<double> Qx;
	static vector<double> Qy;
};

#endif // FREQANALYZER_H
