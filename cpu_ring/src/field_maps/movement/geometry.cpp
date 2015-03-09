#include "field_maps/FieldMap.h"
#include "field_maps/movement/CoordConvertor.h"
using namespace physics;

const Plane getMovementPlane(const Vector& speed, const Field& field)
{
    double A = speed.vec.Y * field.Z - speed.vec.Z * field.Y;
    double B = speed.vec.Z * field.X - speed.vec.X * field.Z;
    double C = speed.vec.X * field.Y - speed.vec.Y * field.X;
    double D = -(A * speed.M.X + B*speed.M.Y + C*speed.M.Z);

    return Plane{ A, B, C, D };
}

const Point getMovementCenter(const Vector& momentum, const Field& field)
{
    Field force = momentum.vec * field;
    double radius = 1. / 0.2998 * sqr(abs(momentum.vec)) / abs(force);

    return Point{ momentum.M.X - radius * force.X / sqrt(abs(force)),
                  momentum.M.X - radius * force.X / sqrt(abs(force)),
                  momentum.M.X - radius * force.X / sqrt(abs(force)) };
}

const Vector getDirectionVector(const Plane& p1, const Plane& p2)
{
    double z = (p2.D*p1.A - p1.D*p2.A) / (p1.C*p2.A - p2.C*p1.A);
    double y = 0;
    double x = -(p1.C*z + p1.D) / p1.A;
    
    double m = p1.B * p2.C - p1.C * p2.B;
    double n = p1.C * p2.A - p1.A * p2.C;
    double p = p1.A * p2.B - p1.B * p2.A;

    return Vector{ Point{ x, y, z }, m>0 ? Field{ m, n, p } : Field{ -m, -n, -p } };
}

const Vector getNewMomentum(const Vector& momentum, const Vector& directionVector, 
                            const Point& center, const Field& field)
{
    double radius = dist(momentum.M, center);
    double mnp = sqr(directionVector.vec.X) + sqr(directionVector.vec.Y) * sqr(directionVector.vec.Z);
    double c1 = directionVector.M.X - center.X;
    double c2 = directionVector.M.Y - center.Y;
    double c3 = directionVector.M.Z - center.Z;
    double mc1 = (directionVector.vec.X * c1);
    double nc2 = (directionVector.vec.Y * c2);
    double pc3 = (directionVector.vec.Z * c3);
    double dist = (sqr(c1) + sqr(c2) + sqr(c3) - sqr(radius));

    double a = (0.5 * sqrt(sqr(2 * mc1 + 2 * nc2 + 2 * pc3) - 4 * mnp * dist) - mc1 - nc2 - pc3) / mnp;

    Point newPoint{ directionVector.M.X + a * directionVector.vec.X,
                    directionVector.M.Y + a * directionVector.vec.Y,
                    directionVector.M.Z + a * directionVector.vec.Z };

    Field newDirection = (newPoint - center) * field;

    return Vector{ newPoint, newDirection * (abs(momentum.vec) / abs(newDirection)) };
}

void FieldMap::affectParticle(Particle& p, const double angle, const double length,
    const size_t nSteps, const size_t iS) const
{
    CoordConvertor convertor(angle, length, nSteps);
    const Plane oldPlane = convertor.getPlane(iS);
    const Plane newPlane = convertor.getPlane(iS + 1);
    const Vector momentum = convertor.getSpeedVector(p, iS);
    const Field field = getFieldInPoint(data, momentum.M);

    const Plane movePlane = getMovementPlane(momentum, field);
    const Point center = getMovementCenter(momentum, field);

    const Vector directionVector = getDirectionVector(newPlane, movePlane);
    const Vector momentumPoint = getNewMomentum(momentum, directionVector, center, field);
}
