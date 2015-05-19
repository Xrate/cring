#include "FreqAnalyzer.h"
#include "fstream"
#include <sstream>
#include <locale>
#include <iterator>
#include <fftw3.h>

DataProps FreqAnalyzer::config;
vector<double> FreqAnalyzer::Qx;
vector<double> FreqAnalyzer::Qy;

void FreqAnalyzer::setUp(DataProps dirConfig)
{
	config.dirName = dirConfig.dirName;
	config.turns = dirConfig.turns;
	config.particles = dirConfig.particles;
	config.steps = dirConfig.steps;
	Qx = vector<double>(config.particles);
	Qy = vector<double>(config.particles);
}

void FreqAnalyzer::print()
{
	ofstream pFile = ofstream(config.dirName + "\\freqMap.out", ifstream::out);
	for (size_t iP = 0; iP < config.particles; ++iP)
		pFile << Qx[iP] << ' ' << Qy[iP] << endl;
	pFile.close();
}

static double findFrequency(fftw_plan& plan, double* in, fftw_complex* out, size_t nTurns_);
static void readParticleTraj(const DataProps& config, size_t iP, double* inX, double* inY);

void FreqAnalyzer::calculate()
{
	clock_t begin = clock();

	size_t nTurns = config.turns;

	double* inXAll = static_cast<double*>(fftw_malloc(sizeof(double)* nTurns));
	double* inYAll = static_cast<double*>(fftw_malloc(sizeof(double)* nTurns));
	fftw_complex* outAll = static_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex) * (nTurns / 2 + 1)));
	fftw_plan plan = fftw_plan_dft_r2c_1d(static_cast<int>(nTurns), inXAll, outAll, FFTW_MEASURE);

	#pragma omp parallel for
	for (int iP = 0; iP < config.particles; ++iP)
	{
		double* inX = static_cast<double*>(fftw_malloc(sizeof(double)* nTurns));
		double* inY = static_cast<double*>(fftw_malloc(sizeof(double)* nTurns));
		fftw_complex* out = static_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex)* (nTurns / 2 + 1)));
		readParticleTraj(config, iP, inX, inY);
		Qx[iP] = findFrequency(plan, inX, out, nTurns);
		Qy[iP] = findFrequency(plan, inY, out, nTurns);
		fftw_free(inX);
		fftw_free(inY);
		fftw_free(out);
	}
	fftw_free(inXAll);
	fftw_free(inYAll);
	fftw_free(outAll);
	fftw_destroy_plan(plan);

	cout << "Time of FFT: " << double(clock() - begin) / CLOCKS_PER_SEC << "s. " << endl;
}

double findFrequency(fftw_plan& plan, double* in, fftw_complex* out, size_t nTurns_)
{
    fftw_execute_dft_r2c(plan, in, out);

    double max = 0.;
	unsigned iP = 1;
	for (; iP < nTurns_ / 2 + 1; ++iP)
    {
		double magnitude = sqr(out[iP][0]) + sqr(out[iP][1]);
        if (magnitude > max)
	        max = magnitude;
    }
	return double(iP) / nTurns_;
}

static void readParticleTraj(const DataProps& config, size_t iP, double* inX, double* inY)
{
    string fileName = config.dirName + "\\particles\\" + to_string(iP) + ".out";
    ifstream pFile = ifstream(fileName, ifstream::in);

    size_t lineNumber = static_cast<size_t>(
		static_cast <double>(rand()) / RAND_MAX * config.steps);
    string line;
    size_t counter = 0;

    while (getline(pFile, line))
	    if (lineNumber++ == config.steps)
	    {
		    istringstream iss(line);
		    vector<string> words{ istream_iterator<string>{iss}, istream_iterator<string>{} };
		    inX[counter] = atof(words.at(1).c_str());
		    inY[counter] = atof(words.at(2).c_str());
		    lineNumber = 0;
		    ++counter;
	    }

	pFile.close();
    if (counter != config.turns)
        throw exception(("File" + to_string(iP) + ".out has wrong format").c_str());
}