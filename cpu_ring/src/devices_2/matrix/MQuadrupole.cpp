#include "MQuadrupole.h"
#include "devices_2/common/DeviceParameters.h"
#include "beam/Particle.h"
#include <cmath>
#include <devices_2/field_matrix/FMQuadrupole.h>

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

void MQuadrupole::affectParticle(Particle& particle) const
{
    auto p = particle;
    if (!p.isAlive) return;

    double mX[6], mY[6];
    generateMatrices(this, p, mX, mY);

    particle.X =  mX[0] * p.X + mX[1] * p.aX + mX[2] * p.dp;
    particle.aX = mX[3] * p.X + mX[4] * p.aX + mX[5] * p.dp;
    particle.Y =  mY[0] * p.Y + mY[1] * p.aY + mY[2] * p.dp;
    particle.aY = mY[3] * p.Y + mY[4] * p.aY + mY[5] * p.dp;
    particle.isAlive = sqr(particle.X / geometry.appertureX) 
                     + sqr(particle.Y / geometry.appertureY) <= 1.;
}

void generateMatrices(const MQuadrupole* quadrupole, const Particle& particle, 
                      double MxP[6], double MyP[6])
{
        double sq_k = sqrt(fabs(quadrupole->force*(1. - particle.dp)));
        double fi = sq_k * quadrupole->geometry.step;

        MxP[0] = cos(fi);       MxP[1] = sin(fi) / sq_k;  MxP[2] = 0.;
        MxP[3] = -sin(fi)*sq_k; MxP[4] = cos(fi);         MxP[5] = 0.;

        MyP[0] = cosh(fi);      MyP[1] = sinh(fi) / sq_k; MyP[2] = 0.;
        MyP[3] = sinh(fi)*sq_k; MyP[4] = cosh(fi);        MyP[5] = 0.;

        if (quadrupole->force < 0) swap(MxP, MyP);
}