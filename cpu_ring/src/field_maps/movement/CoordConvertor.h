#pragma once

#include "beam/Particle.h"
#include "field_maps/physics.h"
using namespace physics;

class CoordConverter
{
public:
    CoordConverter(const double angle, const double length, const size_t nSteps);
    Point CurveToPlain(double X, double Y, const size_t iS) const;
    const Plane getPlane(const size_t iS) const;
    const Vector getMomentum(const Particle& p, const size_t iS) const;
    void updateParticle(Particle& p, const Vector& newMomentum, const size_t iS);
private:
    const double rho;
    const double theta;
    const size_t n;

    double currentAngle(const size_t iS) const;
    double xCoordCorrection(double angle) const;
};