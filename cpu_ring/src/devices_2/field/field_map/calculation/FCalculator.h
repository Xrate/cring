#pragma once

struct Particle;
struct Point;
class ICoordConverter;

class FCalculator
{
public:
    static void updateParticle(Particle&, const Point& field, const ICoordConverter*, size_t iS);
};
