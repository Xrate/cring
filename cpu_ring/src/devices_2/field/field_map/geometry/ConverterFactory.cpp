﻿#include "ConverterFactory.h"
#include <devices_2/common/DeviceGeometry.h>
#include "CoordConverter.h"
#include "CurveConverter.h"
#include "PlainConverter.h"

shared_ptr<CoordConverter> ConverterFactory::getConverter(const DeviceGeometry& geometry)
{
    if (geometry.length <= 0.)
        throw new exception("Incorrect device length.");

    CoordConverter* converter;

    if (geometry.angle != 0.)
        converter = new CurveConverter(geometry);
    else
        converter = new PlainConverter(geometry);

    return shared_ptr<CoordConverter>(converter);
}