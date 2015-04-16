#pragma once

struct Particle;
struct Point;
class CoordConverter;

class FCalculator
{
public:
    static void updateParticle(Particle&, const Point& field, const CoordConverter*, size_t iS);
};
