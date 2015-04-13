#pragma once

struct Particle;
struct Point;
class CoordConverter;

class FCalculator
{
public:
    static void updateParticle(Particle& p, const Point& field, const CoordConverter* converter);
};
