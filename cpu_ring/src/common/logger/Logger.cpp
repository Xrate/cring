#include "Logger.h"
#include <chrono>
#include <windows.h>

string Logger::dirName = "output\\Log_";
shared_ptr<const CBeam> Logger::beam;
Logger::BeamPointers Logger::beamPointers;
ofstream** Logger::pFile;
ofstream* Logger::ellFile;

void Logger::setUpLogger(const shared_ptr<const CBeam> beam_)
{
	GenerateDir();
	if (beam_ == nullptr)
		throw new exception("Error: Trying to log empty beam");

	beam = beam_;
	beamPointers.particles = beam->particles_.data();
	beamPointers.twissX = &beam->parameters_.twissX;
	beamPointers.twissY = &beam->parameters_.twissY;

	ellFile = new ofstream(dirName + "\\ellipses.out", ofstream::out);
	pFile = new ofstream*[beam_->size()];
	for (size_t iP = 0; iP < beam_->size(); ++iP)
		pFile[iP] = new ofstream(dirName + "\\particles\\" + to_string(iP) + ".out", ofstream::out);
}

void Logger::GenerateDir()
{
	using namespace chrono;
	time_t end_time = system_clock::to_time_t(system_clock::now());
	dirName.append(to_string(end_time));
	CreateDirectory("output", nullptr);
	CreateDirectory(dirName.c_str(), nullptr);
	CreateDirectory((dirName+"\\particles").c_str(), nullptr);
}

void Logger::printParticles()
{
#pragma omp parallel for
	for (int iP = 0; iP < beam->size(); ++iP)
	{
		char temp[28];
		sprintf_s(temp, "%03.3f %+1.5f %+1.5f\n", 
			beam->path_, beamPointers.particles[iP].X, beamPointers.particles[iP].Y);
		*pFile[iP] << temp;
	}
}

void Logger::printEllipses(const double& aX, const double& aY)
{
	char temp[125];
	sprintf_s(temp, "%03.3f %+1.5f %+1.5f %+1.5f %+1.5f %+1.5f %+1.5f %+1.5f %+1.5f %+1.5f %+1.5f %+1.5f %+1.5f\n", 
		beam->path_, aX, beamPointers.twissX->coordMax(), aY, beamPointers.twissY->coordMax(), 
		beamPointers.twissX->alf, beamPointers.twissX->bet, beamPointers.twissX->gam, beamPointers.twissX->emt,
		beamPointers.twissY->alf, beamPointers.twissY->bet, beamPointers.twissY->gam, beamPointers.twissY->emt);
	*ellFile << temp;
}

string Logger::logDir()
{
	return dirName;
}

void Logger::closeLogger()
{
	for (size_t iP = 0; iP < beam->size(); ++iP)
	{
		pFile[iP]->close(); delete pFile[iP];
	}
	delete[] pFile;
	ellFile->close(); delete ellFile;
}