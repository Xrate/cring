#include "GeometryHelper.h"

#include <global.h>

static Plane getMovementPlane(const Vector& momentum, const Point& field)
{
	Point norm = momentum.vec * field * momentum.vec;
	double D = -(norm.X * momentum.M.X + norm.Y*momentum.M.Y + norm.Z*momentum.M.Z);

	return Plane{ norm.X, norm.Y, norm.Z, D };
}

static Point getMovementCenter(const Vector& momentum, const Point& field)
{
    Point force = momentum.vec * field;
	double radius = 3.3356 * abs(momentum.vec) / abs(field);

    return Point{ momentum.M.X - radius * force.X / abs(force),
                  momentum.M.Y - radius * force.Y / abs(force),
                  momentum.M.Z - radius * force.Z / abs(force) };
}

static Vector getDirectionVector(const Plane& p1, const Plane& p2)
{
	double m = p1.B * p2.C - p1.C * p2.B;
	double n = p1.C * p2.A - p1.A * p2.C;
	double p = p1.A * p2.B - p1.B * p2.A;

	double x = 0;
	double y = (p2.D*p1.C - p1.D*p2.C) / (p1.B*p2.C - p2.B*p1.C);
	double z = -(p1.B*x + p1.D) / p1.C;

	return Vector{ Point{ x, y, z }, Point{ m, n, p } };
}

static Vector getNewMomentum(const Vector& momentum,
                             const Vector& directionVector,
                             const Point& center)
{
    double radius = dist(momentum.M, center);
    double mnp = sqr(directionVector.vec.X) 
               + sqr(directionVector.vec.Y) 
               + sqr(directionVector.vec.Z);
    double c1 = directionVector.M.X - center.X;
    double c2 = directionVector.M.Y - center.Y;
    double c3 = directionVector.M.Z - center.Z;
    double mc1 = directionVector.vec.X * c1;
    double nc2 = directionVector.vec.Y * c2;
    double pc3 = directionVector.vec.Z * c3;
    double d1 = sqr(c1) + sqr(c2) + sqr(c3) - sqr(radius);

    double a1 = ( 0.5 * sqrt(sqr(2 * mc1 + 2 * nc2 + 2 * pc3) - 4 * mnp * d1) 
                    - mc1 - nc2 - pc3) / mnp;
	double a2 = (-0.5 * sqrt(sqr(2 * mc1 + 2 * nc2 + 2 * pc3) - 4 * mnp * d1)
		            - mc1 - nc2 - pc3) / mnp;

    Point newPoint1
	  { directionVector.M.X + a1 * directionVector.vec.X,
        directionVector.M.Y + a1 * directionVector.vec.Y,
        directionVector.M.Z + a1 * directionVector.vec.Z };

	Point newPoint2
	  { directionVector.M.X + a2 * directionVector.vec.X,
	    directionVector.M.Y + a2 * directionVector.vec.Y,
	    directionVector.M.Z + a2 * directionVector.vec.Z };

	Point newPoint = abs(newPoint1 - momentum.M) < abs(newPoint2 - momentum.M)
		? newPoint1
		: newPoint2;

    Point newDirection = (newPoint - center) * momentum.vec * (newPoint - center);

    return Vector{ newPoint, newDirection * (abs(momentum.vec) / abs(newDirection)) };
}

Vector GeometryHelper::calculateNewMomentum(const Vector& momentum,
                                            const Point& field,
                                            const Plane& newPlane)
{
    const Plane movePlane = getMovementPlane(momentum, field);
    const Vector directionVector = getDirectionVector(newPlane, movePlane);
    const Point center = getMovementCenter(momentum, field);

    const Vector newMomentum = getNewMomentum(momentum, directionVector, center);
    return newMomentum;
}