#pragma once
#include "global.h"

namespace physics
{
    class FieldMapData;
    class CoordConverter;
}
class FDevice;

class FieldMapHandler
{
public:
    static FieldMapHandler* getPrevHandler(FDevice* curr, FDevice* prev);
    static FieldMapHandler* getCurrHandler(FDevice* curr);
    static FieldMapHandler* getNextHandler(FDevice* curr, FDevice* next);
private:
    shared_ptr<physics::FieldMapData> data;
    unique_ptr<physics::CoordConverter> converter;
};