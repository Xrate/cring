#pragma once

#include <global.h>
#include <map>

namespace physics
{
    struct FieldMapData;

    class FieldMapDataReader
    {
    public:
        static shared_ptr<const FieldMapData> getFieldMapData(const string& fileName);
        static map<string, shared_ptr<const FieldMapData>> fieldMaps;
    };
}