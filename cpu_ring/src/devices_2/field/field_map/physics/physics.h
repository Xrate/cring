#pragma once
#include "global.h"

namespace physics
{
    const double DOUBLE_ERR = 1e-15;

    struct Point
    {
        double X;
        double Y;
        double Z;
    };

    Point NaN = { -1e15, -1e15, -1e15 };

    typedef Point Field;

    struct Vector
    {
        Point M;
        Field vec;
    };

    inline const Point& operator+(const Point& lhs, const Point& rhs)
    {
        return Point{ lhs.X + rhs.X, lhs.Y + rhs.Y, lhs.Z + rhs.Z };
    }

    inline const Point& operator-(const Point& lhs, const Point& rhs)
    {
        return Point{ lhs.X - rhs.X, lhs.Y - rhs.Y, lhs.Z - rhs.Z };
    }

    inline const Point& operator*(const Point& lhs, double alfa)
    {
        return Point{ lhs.X * alfa, lhs.Y * alfa, lhs.Z * alfa };
    }

    inline const Point& operator*(const Point& lhs, const Point& rhs)
    {
        return Point{ lhs.Y * rhs.Z - lhs.Z * rhs.Y, 
                      lhs.Z * rhs.X - lhs.X * rhs.Z,
                      lhs.X * rhs.Y - lhs.Y * rhs.X };
    }

    inline double dist(const Point& lhs, const Point& rhs)
    {
        return sqrt(sqr(lhs.X - rhs.X) + sqr(lhs.Y - rhs.Y) + sqr(lhs.Z - rhs.Z));
    }

    inline double abs(const Point& f)
    {
        return sqrt(sqr(f.X) + sqr(f.Y) + sqr(f.Z));
    }

    struct Plane
    {
        double A;
        double B;
        double C;
        double D;
        
    };

    inline bool HasPoint(Plane plane, Point p)
    {
        return plane.A*p.X + plane.B*p.Y + plane.C*p.Z + plane.D < DOUBLE_ERR;
    }
}