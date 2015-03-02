#pragma once

struct Field
{
	double Bx;
	double By;
	double Bz;
};

struct Point
{
	double X;
	double Y;
	double Z;
};

inline double abs(Field& f)
{
	return sqrt(sqr(f.Bx) + sqr(f.By) + sqr(f.Bz));
}

inline double abs(Point& p)
{
	return sqrt(sqr(p.X) + sqr(p.Y) + sqr(p.Z));
}