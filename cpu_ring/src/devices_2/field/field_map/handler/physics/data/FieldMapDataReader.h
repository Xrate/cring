#pragma once

#include "global.h"

namespace physics
{
    struct FieldMapData;

    class FieldMapDataReader
    {
    public:
        static shared_ptr<const FieldMapData> getFieldMapData(const string& fileName);
    };
}