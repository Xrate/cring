#include "CDevice.h"
#include "device/devices/cdipole.h"
#include "device/devices/cdrift.h"
#include "device/devices/cquadrupole.h"
#include "device/devices/csextupole.h"

shared_ptr<CDevice> CDevice::createDevice(const DeviceParameters& params)
{
    switch (params.type_)
    {
    case DIPOLE: return make_shared<CDipole>(params);
    case DRIFT: return make_shared<CDrift>(params);
    case QUADRUPOLE: return make_shared<CQuadrupole>(params);
    case SEXTUPOLE: return make_shared<CSextupole>(params);
    }
    throw exception("DeviceFactory: enum FileNames error.");
}

CDevice::CDevice(const string& name_, const string& mapFileName_) :
hasMap(false)
{
    if (name_.empty()) throw exception("Trying to create empty CDevice object.");
    name = name_;

    if (!mapFileName_.empty())
    {
        hasMap = true;
        fieldMap = FieldMap::getFieldMap(mapFileName_);
    }

    for (size_t i = 0; i < 6; ++i) { mX_P[i] = 0.; mY_P[i] = 0.; }
    for (size_t j = 0; j < 9; ++j) { mX_T[j] = 0.; mY_T[j] = 0.; }
}

void CDevice::generateTwissMatrices()
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

void CDevice::affectBeam(const shared_ptr<CBeam> beam) const
{
    auto particles = beam->particles().data();
    auto params = &beam->parameters();
    for (size_t iS = 0; iS < nSteps; ++iS)
    {
        #pragma omp parallel for
        for (int iP = 0; iP < beam->size(); ++iP)
            hasMap
            ? affectParticleWithMap(particles[iP], iS)
            : affectParticle1stOrder(particles[iP], mX_P, mY_P);

        affectEllipses1stOrder(params);

        beam->addPath(step);
        Logger::printParticles();
        Logger::printEllipses(appertureX, appertureY);
    }
}

void CDevice::affectParticle1stOrder(Particle& particle, const double Mx[6], const double My[6]) const
{
    auto p = particle;
    if (!p.isAlive) return;

    particle.X =  Mx[0] * p.X + Mx[1] * p.aX + Mx[2] * p.dp;
    particle.aX = Mx[3] * p.X + Mx[4] * p.aX + Mx[5] * p.dp;
    particle.Y =  My[0] * p.Y + My[1] * p.aY + My[2] * p.dp;
    particle.aY = My[3] * p.Y + My[4] * p.aY + My[5] * p.dp;
    particle.isAlive = sqr(particle.X / appertureX) + sqr(particle.Y / appertureY) <= 1.;
}

void CDevice::affectParticleWithMap(Particle& particle, const size_t iS) const
{
    if (!particle.isAlive) return;
    fieldMap->affectParticle(particle, angle, length, nSteps, iS);
}

void CDevice::affectEllipses1stOrder(BeamParameters *params) const
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
