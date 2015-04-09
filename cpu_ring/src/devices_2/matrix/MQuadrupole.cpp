#include "MQuadrupole.h"
#include "devices_2/common/DeviceParameters.h"
#include "beam/CBeam.h"
#include "common/logger/Logger.h"
#include <cmath>

MQuadrupole::MQuadrupole(const DeviceParameters& params)
: MDevice(params), Device(params)
{
    force = params.force_;

    MQuadrupole::initMatrices();
}

void MQuadrupole::initMatrices()
{
    double sq_k = sqrt(fabs(force));
    double fi = sq_k * geometry.step;

    mX_P[0] = cos(fi);       mX_P[1] = sin(fi) / sq_k;  mX_P[2] = 0.;
    mX_P[3] = -sin(fi)*sq_k; mX_P[4] = cos(fi);         mX_P[5] = 0.;

    mY_P[0] = cosh(fi);      mY_P[1] = sinh(fi) / sq_k; mY_P[2] = 0.;
    mY_P[3] = sinh(fi)*sq_k; mY_P[4] = cosh(fi);        mY_P[5] = 0.;

    if (force < 0) swap(mX_P, mY_P);

    initTwissMatrices();
}

void MQuadrupole::affectBeam(const shared_ptr<CBeam> beam) const
{
    Particle* particles = beam->particles().data();
    auto params = &beam->parameters();

    vector<double[6]> MxP_all(beam->size()), MyP_all(beam->size());
    generateMatrices(this, MxP_all, MyP_all, beam);

    for (size_t iS = 0; iS < geometry.nSteps; ++iS)
    {
        #pragma omp parallel for
        for (int iP = 0; iP < beam->size(); ++iP)
            affectParticle(particles[iP], MxP_all[iP], MyP_all[iP]);

        affectEllipses(params);

        beam->addPath(geometry.step);
        Logger::printParticles();
        Logger::printEllipses(geometry.appertureX, geometry.appertureY);
    }
}

void MQuadrupole::affectParticle(Particle& particle, const double mX[6], const double mY[6]) const
{
    auto p = particle;
    if (!p.isAlive) return;

    particle.X =  mX[0] * p.X + mX[1] * p.aX + mX[2] * p.dp;
    particle.aX = mX[3] * p.X + mX[4] * p.aX + mX[5] * p.dp;
    particle.Y =  mY[0] * p.Y + mY[1] * p.aY + mY[2] * p.dp;
    particle.aY = mY[3] * p.Y + mY[4] * p.aY + mY[5] * p.dp;
    particle.isAlive = sqr(particle.X / geometry.appertureX) + sqr(particle.Y / geometry.appertureY) <= 1.;
}

void generateMatrices(const MQuadrupole* quadrupole, 
    vector<double[6]> &MxP_all, vector<double[6]>& MyP_all, const shared_ptr<CBeam> beam)
{
    #pragma omp parallel for
    for (int iP = 0; iP < beam->size(); ++iP)
    {
        double sq_k = sqrt(fabs(quadrupole->force*(1. - beam->particles().at(iP).dp)));
        double fi = sq_k * quadrupole->geometry.step;

        MxP_all.at(iP)[0] = cos(fi);       MxP_all.at(iP)[1] = sin(fi) / sq_k;  MxP_all.at(iP)[2] = 0.;
        MxP_all.at(iP)[3] = -sin(fi)*sq_k; MxP_all.at(iP)[4] = cos(fi);         MxP_all.at(iP)[5] = 0.;

        MyP_all.at(iP)[0] = cosh(fi);      MyP_all.at(iP)[1] = sinh(fi) / sq_k; MyP_all.at(iP)[2] = 0.;
        MyP_all.at(iP)[3] = sinh(fi)*sq_k; MyP_all.at(iP)[4] = cosh(fi);        MyP_all.at(iP)[5] = 0.;

        if (quadrupole->force < 0) swap(MxP_all.at(iP), MyP_all.at(iP));
    }
}