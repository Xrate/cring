#pragma once

namespace physics
{
    const double DOUBLE_ERR = 1e-15;

    struct Point
    {
        double X;
        double Y;
        double Z;
		static Point NaN;
		friend const Point& operator+(const Point& lhs, const Point& rhs);
		friend const Point& operator-(const Point& lhs, const Point& rhs);
		friend const Point& operator*(const Point& lhs, double alfa);
		friend const Point& operator*(const Point& lhs, const Point& rhs);
		friend double dist(const Point& lhs, const Point& rhs);
		friend double abs(const Point& f);
    };

    typedef Point Field;

    struct Vector
    {
        Point M;
        Field vec;
    };

    struct Plane
    {
        double A;
        double B;
        double C;
        double D;
		friend bool HasPoint(Plane plane, Point p);
    };
}