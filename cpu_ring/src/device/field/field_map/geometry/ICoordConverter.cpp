#include "ICoordConverter.h"
#include "CurveConverter.h"
#include "PlainConverter.h"

#include <device/common/DeviceGeometry.h>

shared_ptr<ICoordConverter> getConverter(const DeviceGeometry& geometry)
{
	if (geometry.length <= 0.)
		throw new exception("Incorrect device length.");

	if (geometry.angle != 0)
		return static_pointer_cast<ICoordConverter>(make_shared<CurveConverter>(geometry));
	else
		return static_pointer_cast<ICoordConverter>(make_shared<PlainConverter>(geometry));
}