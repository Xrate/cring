#include "BeamParameters.h"
#include <memory>
BeamParameters::BeamParameters(TwissParameters twiss_x, 
							   TwissParameters twiss_y, 
							   size_t num_particles, DistType dist_type, 
							   double momentum, double momentum_spread):
twissX_(std::move(twiss_x)), twissY_(std::move(twiss_y)), numParticles_(num_particles),
distType_(dist_type), momentum_(momentum), momentumSpread_(momentum_spread) 
{
}

const TwissParameters& BeamParameters::twissX() const { return twissX_; }
const TwissParameters& BeamParameters::twissY() const { return twissY_; }
size_t BeamParameters::numParticles() const { return numParticles_; }
DistType BeamParameters::distType() const { return distType_; }
double BeamParameters::momentum() const { return momentum_; }
double BeamParameters::momentumSpread() const { return momentumSpread_; }