#pragma once

struct Point;

namespace physics
{
    struct CoordTransformation;

    class CoordBooster
    {
    public:
        explicit CoordBooster(const CoordTransformation& transform);
        Point convertPoint(Point p) const;
	    Point rotateField(Point raw_field) const;
    private:
        const double Z;
        const double X;
        const double angle;
    };
}
