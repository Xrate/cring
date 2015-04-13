#include "FCalculator.h"
#include <beam/Particle.h>
#include "helper/GeometryHelper.h"
#include <devices_2/field/field_map/geometry/CoordConverter.h>

bool HasPoint(Plane plane, Point p);

void FCalculator::updateParticle(Particle& p, const Point& field, const CoordConverter* converter)
{
    const Vector momentum = converter->getMomentum(p);
    const Plane  newPlane = converter->getNextPlane();

    const Vector newMomentum = GeometryHelper::calculateNewMomentum(momentum, field, newPlane);

    converter->applyNewMomentum(p, newMomentum);
}