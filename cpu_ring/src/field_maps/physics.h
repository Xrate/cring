#pragma once
#include "global.h"

namespace physics
{
    struct Point
    {
        double X;
        double Y;
        double Z;
    };

    inline const Point operator+(const Point& lhs, const Point& rhs)
    {
        return Point{ lhs.X + rhs.X, lhs.Y + rhs.Y, lhs.Z + rhs.Z };
    }

    inline const Point operator*(const Point& lhs, double alfa)
    {
        return Point{ lhs.X * alfa, lhs.Y * alfa, lhs.Z * alfa };
    }

    inline double abs(Point& f)
    {
        return sqrt(sqr(f.X) + sqr(f.Y) + sqr(f.Z));
    }

    typedef Point Field;

    struct Plane
    {
        double A;
        double B;
        double C;
        double D;
        Point center;
    };

    struct Vector
    {
        Point M;
        Field vec;
    };
}