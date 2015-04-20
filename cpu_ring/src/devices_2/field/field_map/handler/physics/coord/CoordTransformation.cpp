#include "CoordTransformation.h"
#include "global.h"
#include <devices_2/common/DeviceGeometry.h>

using namespace physics;

CoordTransformation physics::calculateTransformation(DeviceGeometry curr, DeviceGeometry prev)
{
    CoordTransformation t;
    if (prev.angle == 0. && curr.angle == 0)
    {
        t.Z = (prev.length + curr.length) / 2;
        t.X = 0.;
        t.angle = 0.;
    }
    else if (prev.angle != 0. && curr.angle == 0.)
    {
        auto rho = prev.length / prev.angle;
        auto angle = prev.angle / 2;
        auto dR = rho / 2 * (1 - cos(angle));

        t.Z = curr.length / 2 + rho*sin(angle) - dR*sin(angle);
        t.X = rho*(1 - cos(angle)) + dR*cos(angle);
        t.angle = angle;
    }
    else if (prev.angle == 0. && curr.angle != 0)
    {
        auto rho = curr.length / curr.angle;
        auto angle = curr.angle / 2;
        auto dR = rho / 2 * (1 - cos(angle));
        t.Z = prev.length * cos(angle) / 2 + rho*sin(angle);
        t.X = prev.length * sin(angle) / 2 + dR;
        t.angle = angle;
    }
    else
        throw new exception("Not implemented");
    return t;
}