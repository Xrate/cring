#include "CoordConverter.h"
#include <devices_2/common/DeviceGeometry.h>
#include "CurveConverter.h"
#include "PlainConverter.h"

using namespace physics;

CoordConverter*  CoordConverter::getConverter(DeviceGeometry  geometry)
{
	if (geometry.length <= 0.)
		throw new exception("Incorrect device length.");

	return geometry.angle != 0.
		? new CurveConverter(geometry)
		: new PlainConverter(geometry);
}

void CoordConverter::trackDeviceStep(const size_t& iS)
{
	dev_step = &iS;
}
