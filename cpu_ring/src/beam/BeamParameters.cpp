#include "BeamParameters.h"
#include <memory>
BeamParameters::BeamParameters(TwissParameters twiss_x, 
							   TwissParameters twiss_y, 
							   size_t num_particles, DistType dist_type, 
							   double momentum, double momentum_spread):
twissX(std::move(twiss_x)), twissY(std::move(twiss_y)), numParticles(num_particles),
distType(dist_type), momentum(momentum), momentumSpread(momentum_spread) 
{
}