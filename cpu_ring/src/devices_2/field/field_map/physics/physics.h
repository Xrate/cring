#pragma once

namespace physics
{
    const double DOUBLE_ERR = 1e-15;

    struct Point
    {
        double X;
        double Y;
        double Z;
		bool   isNull();
		static Point Null;
		friend const Point& operator+(const Point& lhs, const Point& rhs);
		friend const Point& operator-(const Point& lhs, const Point& rhs);   
		friend const Point& operator*(const Point& lhs, double alfa);
		friend const Point& operator*(const Point& lhs, const Point& rhs);
		friend double dist(const Point& lhs, const Point& rhs);
		friend double abs(const Point& f);
    };

    struct Vector
    {
        Point M;
		Point vec;
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