#include "Logger.h"
#include <chrono>
#include <windows.h>
#include "ftoa.h"
#include <beam/CBeam.h>
#include <beam/Particle.h>

string Logger::dirName = "output\\Log_";
shared_ptr<const CBeam> Logger::beam;
Logger::BeamPointers Logger::beamPointers;
ofstream** Logger::pFile;
ofstream* Logger::ellFile;

void Logger::setUp(const shared_ptr<const CBeam> beam_)
{
    GenerateDir();
    if (beam_ == nullptr) throw new exception("Error: Trying to log empty beam");

    beam = beam_;
    beamPointers.particles = beam->particles().data();
    beamPointers.twissX = &beam->parameters().twissX;
    beamPointers.twissY = &beam->parameters().twissY;

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
    CreateDirectoryA("output", nullptr);
    CreateDirectoryA(dirName.c_str(), nullptr);
    CreateDirectoryA((dirName+"\\particles").c_str(), nullptr);
}

void Logger::printParticles()
{    
    // Bottleneck! Change only if you really know what you do!
    // All hard-coded digits present for maximum performance.
    // Optimize ftoa(), if you can =)
    #pragma omp parallel for
    for (int iP = 0; iP < beam->size(); ++iP)
    {
        char res[53];
        ftoa(beam->path(), res, 6, 3);
        ftoa(beamPointers.particles[iP].X, res + 12, 1, 6);
        ftoa(beamPointers.particles[iP].Y, res + 22, 1, 6);
        ftoa(beamPointers.particles[iP].aX, res + 32, 1, 6);
        ftoa(beamPointers.particles[iP].aY, res + 42, 1, 6);
        res[51] = '\n';
        *pFile[iP] << res;
    }
}

void Logger::printEllipses(const double& aX, const double& aY)
{    
    // Bottleneck! Change only if you really know what you do!
    // All hard-coded digits present for maximum performance.
    // Optimize ftoa(), if you can =)
    char res[137];
    ftoa(beam->path(), res, 6, 3);
    ftoa(aX, res + 12, 1, 6);
    ftoa(beamPointers.twissX->coordMax(), res + 22, 1, 6);
    ftoa(aY, res + 32, 1, 6);
    ftoa(beamPointers.twissY->coordMax(), res + 42, 1, 6);

    ftoa(beamPointers.twissX->alf, res + 52, 1, 6);
    ftoa(beamPointers.twissX->bet, res + 62, 3, 6);
    ftoa(beamPointers.twissX->gam, res + 74, 1, 6);
    ftoa(beamPointers.twissX->emt, res + 84, 1, 6);
    ftoa(beamPointers.twissY->alf, res + 94, 1, 6);
    ftoa(beamPointers.twissY->bet, res + 104, 3, 6);
    ftoa(beamPointers.twissY->gam, res + 116, 1, 6);
    ftoa(beamPointers.twissY->emt, res + 126, 1, 6);

    res[135] = '\n';
    *ellFile << res;
}

string Logger::logDir()
{
    return dirName;
}

void Logger::close()
{
    for (size_t iP = 0; iP < beam->size(); ++iP)
    {
        pFile[iP]->close(); delete pFile[iP];
    }
    delete[] pFile;
    ellFile->close(); delete ellFile;
}