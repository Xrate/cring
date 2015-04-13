#include "GeometryHelper.h"
#include "global.h"

static Plane getMovementPlane(const Vector& momentum, const Point& field)
{
    Point force = momentum.vec * field;
    double A = momentum.vec.Y * force.Z - momentum.vec.Z * force.Y;
    double B = momentum.vec.Z * force.X - momentum.vec.X * force.Z;
    double C = momentum.vec.X * force.Y - momentum.vec.Y * force.X;
    double D = -(A * momentum.M.X + B*momentum.M.Y + C*momentum.M.Z);

    return Plane{ A, B, C, D };
}

static Point getMovementCenter(const Vector& momentum, const Point& field)
{
    Point force = momentum.vec * field;
    double radius = 3.3356 * sqr(abs(momentum.vec)) / abs(force);

    return Point{ momentum.M.X - radius * force.X / abs(force),
        momentum.M.Y - radius * force.Y / abs(force),
        momentum.M.Z - radius * force.Z / abs(force) };
}

static Vector getDirectionVector(const Plane& p1, const Plane& p2)
{
    double x = (p2.D*p1.C - p1.D*p2.C) / (p1.A*p2.C - p2.A*p1.C);
    double y = 0;
    double z = -(p1.A*x + p1.D) / p1.C;

    double m = p1.B * p2.C - p1.C * p2.B;
    double n = p1.C * p2.A - p1.A * p2.C;
    double p = p1.A * p2.B - p1.B * p2.A;

    return Vector{ Point{ x, y, z }, m>0 ? Point{ m, n, p } : Point{ -m, -n, -p } };
}

static Vector getNewMomentum(const Vector& momentum, const Vector& directionVector, 
                                    const Point&  center)
{
    double radius = dist(momentum.M, center);
    double mnp = sqr(directionVector.vec.X) 
               + sqr(directionVector.vec.Y) 
               + sqr(directionVector.vec.Z);
    double c1 = directionVector.M.X - center.X;
    double c2 = directionVector.M.Y - center.Y;
    double c3 = directionVector.M.Z - center.Z;
    double mc1 = (directionVector.vec.X * c1);
    double nc2 = (directionVector.vec.Y * c2);
    double pc3 = (directionVector.vec.Z * c3);
    double d1 = (sqr(c1) + sqr(c2) + sqr(c3) - sqr(radius));

    double a = (0.5 * sqrt(sqr(2 * mc1 + 2 * nc2 + 2 * pc3) - 4 * mnp * d1) 
                    - mc1 - nc2 - pc3) / mnp;

    Point newPoint{ directionVector.M.X + a * directionVector.vec.X,
        directionVector.M.Y + a * directionVector.vec.Y,
        directionVector.M.Z + a * directionVector.vec.Z };

    Point newDirection = ((newPoint - center) * momentum.vec) * (newPoint - center);

    return Vector{ newPoint, newDirection * (abs(momentum.vec) / abs(newDirection)) };
}

Vector GeometryHelper::calculateNewMomentum(const Vector& momentum, const Point& field, 
                                                   const Plane&  newPlane)
{
    const Plane movePlane = getMovementPlane(momentum, field);
    const Vector directionVector = getDirectionVector(newPlane, movePlane);
    const Point center = getMovementCenter(momentum, field);

    const Vector newMomentum = getNewMomentum(momentum, directionVector, center);
    return newMomentum;
}