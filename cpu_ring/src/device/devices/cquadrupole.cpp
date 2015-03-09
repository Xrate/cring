#include "cquadrupole.h"
#include <cmath>

CQuadrupole::CQuadrupole(const DeviceParameters& params)
: CDevice(params.name_, params.mapFileName_)
{
    length = params.length_;
    force = params.force_;
    angle = 0.;
    appertureX = params.appertureX_;
    appertureY = params.appertureY_;
    nSteps = size_t(params.type_);
    step = length / nSteps;

    CQuadrupole::initDevice();
}

void CQuadrupole::initDevice()
{
    double sq_k = sqrt(fabs(force));
    double fi   = sq_k * step;

    mX_P[0] = cos(fi);       mX_P[1] = sin(fi)/sq_k;  mX_P[2] = 0.;
    mX_P[3] = -sin(fi)*sq_k; mX_P[4] = cos(fi);       mX_P[5] = 0.;

    mY_P[0] = cosh(fi);      mY_P[1] = sinh(fi)/sq_k; mY_P[2] = 0.;
    mY_P[3] = sinh(fi)*sq_k; mY_P[4] = cosh(fi);      mY_P[5] = 0.;

    if (force < 0) swap(mX_P, mY_P);

    generateTwissMatrices();
}

void CQuadrupole::affectBeam(const shared_ptr<CBeam> beam) const
{
    Particle* particles = beam->particles().data();
    auto params = &beam->parameters();

    vector<double[6]> MxP_all(beam->size()), MyP_all(beam->size());
    generateMatrices(MxP_all, MyP_all, beam);

    for (size_t iS = 0; iS < nSteps; ++iS)
    {
        #pragma omp parallel for
        for (int iP = 0; iP < beam->size(); ++iP)
            hasMap 
                ? affectParticleWithMap(particles[iP], iS) 
                : affectParticle1stOrder(particles[iP], MxP_all[iP], MyP_all[iP]);

        affectEllipses1stOrder(params);

        beam->addPath(step);
        Logger::printParticles();
        Logger::printEllipses(appertureX, appertureY);
    }
}

void CQuadrupole::generateMatrices(vector<double[6]> &MxP_all, 
                vector<double[6]>& MyP_all, const shared_ptr<CBeam> beam) const
{
    #pragma omp parallel for
    for (int iP = 0; iP < beam->size(); ++iP)
    {
        double sq_k = sqrt(fabs(force*(1. - beam->particles().at(iP).dp)));
        double fi = sq_k * step;

        MxP_all.at(iP)[0] = cos(fi);       MxP_all.at(iP)[1] = sin(fi) / sq_k;  MxP_all.at(iP)[2] = 0.;
        MxP_all.at(iP)[3] = -sin(fi)*sq_k; MxP_all.at(iP)[4] = cos(fi);         MxP_all.at(iP)[5] = 0.;

        MyP_all.at(iP)[0] = cosh(fi);      MyP_all.at(iP)[1] = sinh(fi) / sq_k; MyP_all.at(iP)[2] = 0.;
        MyP_all.at(iP)[3] = sinh(fi)*sq_k; MyP_all.at(iP)[4] = cosh(fi);        MyP_all.at(iP)[5] = 0.;

        if (force < 0) swap(MxP_all.at(iP), MyP_all.at(iP));
    }
}