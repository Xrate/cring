#pragma once

#include "global.h"
#include "beam/Particle.h"
#include "field_maps/movement/CoordConvertor.h"

void moveParticle(Particle& p, CoordConvertor& convertor);