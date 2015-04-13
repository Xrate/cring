#pragma once

const double DOUBLE_ERR = 1e-15;

struct Point
{
    double X;
    double Y;
    double Z;
    static Point Null;
    bool   isNull() const;
    friend Point operator+(const Point& lhs, const Point& rhs);
    friend Point operator-(const Point& lhs, const Point& rhs);
    friend Point operator*(const Point& lhs, double alfa);
    friend Point operator*(const Point& lhs, const Point& rhs);
};

double dist(const Point& lhs, const Point& rhs);
double abs(const Point& f);

typedef Point Field;