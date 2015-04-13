#pragma once

struct DeviceGeometry;

namespace physics
{
    struct CoordTransformation
    {
        double Z;
        double X;
        double angle;
    };
    CoordTransformation calculateTransformation(DeviceGeometry curr, DeviceGeometry prev);
}