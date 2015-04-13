#include "primitives.h"
#include "global.h"

Point Point::Null = { 0., 0., 0. };

bool Point::isNull() const
{
    return fabs(X) + fabs(Y) + fabs(Z) < DOUBLE_ERR;
}

Point operator+ (const Point& lhs, const Point& rhs)
{
    return Point{ lhs.X + rhs.X, lhs.Y + rhs.Y, lhs.Z + rhs.Z };
}

Point operator- (const Point& lhs, const Point& rhs)
{
    return Point{ lhs.X - rhs.X, lhs.Y - rhs.Y, lhs.Z - rhs.Z };
}

Point operator*(const Point& lhs, double alfa)
{
    return Point{ lhs.X * alfa, lhs.Y * alfa, lhs.Z * alfa };
}

Point operator*(const Point& lhs, const Point& rhs)
{
    return Point{ lhs.Y * rhs.Z - lhs.Z * rhs.Y,
        lhs.Z * rhs.X - lhs.X * rhs.Z,
        lhs.X * rhs.Y - lhs.Y * rhs.X };
}

double dist(const Point& lhs, const Point& rhs)
{
    return sqrt(sqr(lhs.X - rhs.X) + sqr(lhs.Y - rhs.Y) + sqr(lhs.Z - rhs.Z));
}

double abs(const Point& f)
{
    return sqrt(sqr(f.X) + sqr(f.Y) + sqr(f.Z));
}