#include "Device.h"
#include "DeviceParameters.h"

#include <utils/logger/Logger.h>
#include <beam/CBeam.h>
#include <beam/Particle.h>
#include <device/field_matrix/FMDipole.h>
#include <device/field_matrix/FMDrift.h>
#include <device/field_matrix/FMQuadrupole.h>

shared_ptr<Device> createDevice(const DeviceParameters& params)
{
	switch (params.type_)
	{
	case DIPOLE:     return make_shared<FMDipole>(params);
	case DRIFT:      return make_shared<FMDrift>(params);
	case QUADRUPOLE: return make_shared<FMQuadrupole>(params);
	case SEXTUPOLE:  return make_shared<FMDrift>(params);
	}
	throw exception("DeviceFactory: enum FileNames error.");
}

Device::Device(const DeviceParameters& params)
{
    if (params.name_.empty())
        throw exception("Trying to create empty Device object.");

    name = params.name_;
    geometry.length = params.length_;
    geometry.angle = 0.;
    geometry.nSteps = size_t(params.type_);
    geometry.appertureX = params.appertureX_;
    geometry.appertureY = params.appertureY_;
    geometry.step = geometry.length / geometry.nSteps;

    curr_step = 0;
}

void Device::affectBeam(const shared_ptr<CBeam> beam) const
{
    auto particles = beam->particles().data();
    auto params = &beam->parameters();
    for (size_t iS = 0; iS < geometry.nSteps; ++iS)
    {
        curr_step = iS;
        #pragma omp parallel for
        for (int iP = 0; iP < beam->size(); ++iP)
            affectParticle(particles[iP]);

        affectEllipses(params);

        beam->addPath(geometry.step);
        Logger::printParticles();
        Logger::printEllipses(geometry.appertureX, geometry.appertureY);
    }
}