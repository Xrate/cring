#include "FreqAnalyzer.h"
#include "fstream"
#include <sstream>

string FreqAnalyzer::dirName_;
size_t FreqAnalyzer::nTurns_;
size_t FreqAnalyzer::nParticles_;
size_t FreqAnalyzer::nSteps_;
vector<double> FreqAnalyzer::Qx;
vector<double> FreqAnalyzer::Qy;

void FreqAnalyzer::setUp(string dirName, size_t turns, size_t size, size_t num_steps)
{
	dirName_ = dirName;
	nTurns_ = turns;
	nParticles_ = size;
	nSteps_ = num_steps;
	Qx = vector<double>(size);
	Qy = vector<double>(size);
}

void FreqAnalyzer::print()
{
	ofstream pFile = ofstream(dirName_ + "\\freqMap.out", ifstream::out);
	for (size_t iP = 0; iP < nParticles_; ++iP)
	{
		pFile << Qx[iP] << ' ' << Qy[iP] << endl;
	}
	pFile.close();
}

void FreqAnalyzer::calculate()
{
	double* inX = new double[nTurns_];
	double* inY = new double[nTurns_];
	fftw_complex* out = static_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex) * (nTurns_/2 + 1)));
	fftw_plan planX = fftw_plan_dft_r2c_1d(static_cast<int>(nTurns_), inX, out, FFTW_FORWARD);
	fftw_plan planY = fftw_plan_dft_r2c_1d(static_cast<int>(nTurns_), inX, out, FFTW_FORWARD);

	for (int iP = 0; iP < nParticles_; ++iP)
	{
		vector<double> trajX(0);
		vector<double> trajY(0);
		readParticleTraj(iP, inX, inY);
		Qx[iP] = findFrequency(planX, out);
		Qy[iP] = findFrequency(planY, out);
	}
}

void FreqAnalyzer::readParticleTraj(size_t iP, double* inX, double* inY)
{
	ifstream pFile = ifstream(dirName_ + "\\particles\\" + to_string(iP) + ".out", ifstream::in);

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
	if (counter != nTurns_)
		throw exception(("File" + to_string(iP) + ".out has wrong format").c_str());
}

double FreqAnalyzer::findFrequency(fftw_plan& plan, fftw_complex* out)
{
	fftw_execute(plan);
	size_t n = nTurns_ / 2 + 1;
	double beta = 0., max = 0.;
	for (unsigned iP = 0; iP < n; ++iP)
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