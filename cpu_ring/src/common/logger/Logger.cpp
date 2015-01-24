#include "Logger.h"
#include <chrono>
#include <windows.h>

string Logger::dirName = "Log_";
shared_ptr<const CBeam> Logger::beam;
Logger::BeamPointers Logger::beamPointers;
ofstream* Logger::pXFile = nullptr;
ofstream* Logger::pYFile = nullptr;
ofstream* Logger::eXFile = nullptr;
ofstream* Logger::eYFile = nullptr;

void Logger::GenerateDir()
{
	using namespace chrono;
	time_t end_time = system_clock::to_time_t(system_clock::now());
	dirName.append(to_string(end_time));
	CreateDirectory(dirName.c_str(), nullptr);
}

void Logger::printParticles(double aX, double aY)
{
	size_t numParticles = beam->numParticles_;
	*pXFile << beam->path_ << " ";
	*pXFile << aX << " ";
	*pYFile << beam->path_ << " ";
	*pYFile << aY << " ";
	for (size_t iP = 0; iP < numParticles; ++iP)
	{
		*pXFile << beamPointers.particles[iP].X << " ";
		*pYFile << beamPointers.particles[iP].Y << " ";
	}
	*pXFile << endl;
	*pYFile << endl;
}

void Logger::printEllipses(double aX, double aY)
{
	*eXFile << beam->path_ << " ";
	*eXFile << aX << " ";
	*eYFile << beam->path_ << " ";
	*eYFile << aY << " ";

	*eXFile << beamPointers.twissX->coordMax << " ";
	*eXFile << beamPointers.twissX->alf << " ";
	*eXFile << beamPointers.twissX->bet << " ";
	*eXFile << beamPointers.twissX->gam << " ";
	*eXFile << beamPointers.twissX->emt << " ";

	*eYFile << beamPointers.twissY->coordMax << " ";
	*eYFile << beamPointers.twissY->alf << " ";
	*eYFile << beamPointers.twissY->bet << " ";
	*eYFile << beamPointers.twissY->gam << " ";
	*eYFile << beamPointers.twissY->emt << " ";
	
	*eXFile << endl;
	*eYFile << endl;
}

void Logger::setUpLogger(const shared_ptr<const CBeam> beam_)
{
	GenerateDir();
	if (beam_ == nullptr)
		throw new exception("Error: Trying to log empty beam");

	beam = beam_;

	beamPointers.particles = beam->particles_.data();
	beamPointers.twissX = &beam->parameters_.twissX;
	beamPointers.twissY = &beam->parameters_.twissY;

	pXFile = new ofstream(dirName + "\\particlesX.out", ofstream::out);
	pYFile = new ofstream(dirName + "\\particlesY.out", ofstream::out);
	eXFile = new ofstream(dirName + "\\ellipsesX.out", ofstream::out);
	eYFile = new ofstream(dirName + "\\ellipsesY.out", ofstream::out);
}

void Logger::closeLogger()
{
	pXFile->close(); delete pXFile;
	pYFile->close(); delete pYFile;
	eXFile->close(); delete eXFile;
	eYFile->close(); delete eYFile;
}