#include "MDevice.h"
#include "beam/CBeam.h"
#include "common/logger/Logger.h"

MDevice::MDevice(const DeviceParameters& params)
: Device(params)
{
    for (size_t i = 0; i < 6; ++i) { mX_P[i] = 0.; mY_P[i] = 0.; }
    for (size_t j = 0; j < 9; ++j) { mX_T[j] = 0.; mY_T[j] = 0.; }
}

void MDevice::initTwissMatrices()
{
    double C = mX_P[0], S = mX_P[1];
    double C_ = mX_P[3], S_ = mX_P[4];

    mX_T[0] = +1 * C *C;   mX_T[1] = -2 * C *S;    mX_T[2] = +1 * S *S;
    mX_T[3] = -1 * C *C_;  mX_T[4] = C*S_ + C_*S;  mX_T[5] = -1 * S *S_;
    mX_T[6] = +1 * C_*C_;  mX_T[7] = -2 * C_*S_;   mX_T[8] = +1 * S_*S_;

    C = mY_P[0], S = mY_P[1];
    C_ = mY_P[3], S_ = mY_P[4];

    mY_T[0] = +1 * C *C;   mY_T[1] = -2 * C *S;    mY_T[2] = +1 * S *S;
    mY_T[3] = -1 * C *C_;  mY_T[4] = C*S_ + C_*S;  mY_T[5] = -1 * S *S_;
    mY_T[6] = +1 * C_*C_;  mY_T[7] = -2 * C_*S_;   mY_T[8] = +1 * S_*S_;
}

void MDevice::affectBeam(const shared_ptr<CBeam> beam) const
{
    auto particles = beam->particles().data();
    auto params = &beam->parameters();
    for (size_t iS = 0; iS < geometry.nSteps; ++iS)
    {
        #pragma omp parallel for
        for (int iP = 0; iP < beam->size(); ++iP)
            affectParticle(particles[iP]);

        affectEllipses(params);

        beam->addPath(geometry.step);
        Logger::printParticles();
        Logger::printEllipses(geometry.appertureX, geometry.appertureY);
    }
}

void MDevice::affectParticle(Particle& particle) const
{
    auto p = particle;
    if (!p.isAlive) return;

    particle.X  = mX_P[0] * p.X + mX_P[1] * p.aX + mX_P[2] * p.dp;
    particle.aX = mX_P[3] * p.X + mX_P[4] * p.aX + mX_P[5] * p.dp;
    particle.Y  = mY_P[0] * p.Y + mY_P[1] * p.aY + mY_P[2] * p.dp;
    particle.aY = mY_P[3] * p.Y + mY_P[4] * p.aY + mY_P[5] * p.dp;
    particle.isAlive = sqr(particle.X / geometry.appertureX) + sqr(particle.Y / geometry.appertureY) <= 1.;
}

void MDevice::affectEllipses(BeamParameters *params) const
{
    auto tX = params->twissX;
    params->twissX.bet = mX_T[0] * tX.bet + mX_T[1] * tX.alf + mX_T[2] * tX.gam;
    params->twissX.alf = mX_T[3] * tX.bet + mX_T[4] * tX.alf + mX_T[5] * tX.gam;
    params->twissX.gam = mX_T[6] * tX.bet + mX_T[7] * tX.alf + mX_T[8] * tX.gam;

    auto tY = params->twissY;
    params->twissY.bet = mY_T[0] * tY.bet + mY_T[1] * tY.alf + mY_T[2] * tY.gam;
    params->twissY.alf = mY_T[3] * tY.bet + mY_T[4] * tY.alf + mY_T[5] * tY.gam;
    params->twissY.gam = mY_T[6] * tY.bet + mY_T[7] * tY.alf + mY_T[8] * tY.gam;
}