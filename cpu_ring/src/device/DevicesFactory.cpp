#include "DevicesFactory.h"
#include "devices/cdipole.h"
#include "devices/cdrift.h"
#include "devices/cquadrupole.h"
#include "devices/csextupole.h"
#include <iostream>

CDevice* DevicesFactory::createDevice(DeviceType type, DeviceParameters* params)
{
	switch (type)
	{
	case DIPOLE: return new CDipole(params);
	case DRIFT: return new CDrift(params);
	case QUADRUPOLE: return new CQuadrupole(params);
	case SEXTUPOLE: return new CSextupole(params);
	}
	cout << "DeviceFactory: enum FileNames error." << endl;
	exit(EXIT_FAILURE);
	return new CDrift(params);
}