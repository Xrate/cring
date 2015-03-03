#include "FreqAnalyzer.h"
#include "fstream"
#include <sstream>
#include <locale>

string FreqAnalyzer::dirName_;
size_t FreqAnalyzer::nTurns_;
size_t FreqAnalyzer::nParticles_;
size_t FreqAnalyzer::nSteps_;
vector<double> FreqAnalyzer::Qx;
vector<double> FreqAnalyzer::Qy;

void FreqAnalyzer::setUp(OutDirConfig dirConfig)
{
	dirName_ = dirConfig.dirName;
	nTurns_ = dirConfig.turns;
	nParticles_ = dirConfig.particles;
	nSteps_ = dirConfig.steps;
	Qx = vector<double>(nParticles_);
	Qy = vector<double>(nParticles_);
}

void FreqAnalyzer::print()
{
	ofstream pFile = ofstream(dirName_ + "\\freqMap.out", ifstream::out);
	for (size_t iP = 0; iP < nParticles_; ++iP)
		pFile << Qx[iP] << ' ' << Qy[iP] << endl;
	pFile.close();
}

void FreqAnalyzer::calculate()
{
	clock_t begin = clock();

	double* inXAll = static_cast<double*>(fftw_malloc(sizeof(double)* nTurns_));
	double* inYAll = static_cast<double*>(fftw_malloc(sizeof(double)* nTurns_));
	fftw_complex* outAll = static_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex) * (nTurns_/2 + 1)));
	fftw_plan plan = fftw_plan_dft_r2c_1d(static_cast<int>(nTurns_), inXAll, outAll, FFTW_MEASURE);

	#pragma omp parallel for
	for (int iP = 0; iP < nParticles_; ++iP)
	{
		double* inX = static_cast<double*>(fftw_malloc(sizeof(double)* nTurns_));
		double* inY = static_cast<double*>(fftw_malloc(sizeof(double)* nTurns_));
		fftw_complex* out = static_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex)* (nTurns_ / 2 + 1)));
		readParticleTraj(iP, inX, inY);
		Qx[iP] = findFrequency(plan, inX, out);
		Qy[iP] = findFrequency(plan, inY, out);
		fftw_free(inX);
		fftw_free(inY);
		fftw_free(out);
	}
	fftw_free(inXAll);
	fftw_free(inYAll);
	fftw_free(outAll);
	fftw_destroy_plan(plan);

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	cout << "Time of FFT: " << elapsed_secs << "s. " << endl;
}

void FreqAnalyzer::readParticleTraj(size_t iP, double* inX, double* inY)
{
	string fileName = dirName_ + "\\particles\\" + to_string(iP) + ".out";
	ifstream pFile = ifstream(fileName, ifstream::in);

	size_t lineNumber = static_cast<size_t>(static_cast <double>(rand()) / RAND_MAX * nSteps_);
	string line;
	size_t counter = 0;

	while (getline(pFile, line))
	{
		if (lineNumber == nSteps_)
		{
			istringstream iss(line);
			vector<string> words{ istream_iterator<string>{iss},
				istream_iterator<string>{} };
			inX[counter] = atof(words.at(1).c_str());
			inY[counter] = atof(words.at(2).c_str());
			lineNumber = 0;
			++counter;
		}
		lineNumber++;
	}

	pFile.close();
	if (counter != nTurns_)
		throw exception(("File" + to_string(iP) + ".out has wrong format").c_str());
}

double FreqAnalyzer::findFrequency(fftw_plan& plan, double* in, fftw_complex* out)
{
	fftw_execute_dft_r2c(plan, in, out);
	size_t n = nTurns_ / 2 + 1;
	double beta = 0., max = 0.;
	for (unsigned iP = 1; iP < n; ++iP)
	{
		double x = out[iP][0];
		double y = out[iP][1];
		double temp = sqrt(sqr(x) + sqr(y));
		if (temp > max)
		{
			max = temp;
			beta = double(iP) / nTurns_;
		}
	}
	return beta;
}