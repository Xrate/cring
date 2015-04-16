#pragma once

#include "global.h"

class CoordConverter;
struct DeviceGeometry;

class ConverterFactory
{
public:
    static shared_ptr<CoordConverter> getConverter(const DeviceGeometry& geometry);
};
