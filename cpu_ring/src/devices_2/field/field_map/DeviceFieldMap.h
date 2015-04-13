#pragma once

#include "global.h"

class FieldMapHandler;
class CoordConverter;
struct Point;
struct DeviceGeometry;
struct Particle;
class FDevice;

class NullFieldException : exception{};

class DeviceFieldMap
{
    friend   FDevice;
public:
    virtual       ~DeviceFieldMap(                       ){}
    virtual  void  updateParticle(Particle& p            ) const;
protected:
    explicit       DeviceFieldMap(const DeviceGeometry&  , 
                                  const string& name     , 
                                  const size_t* step     )      ;
    virtual  Point getField      (const Point&  point    ) const;

    shared_ptr<FieldMapHandler> device_map;
    shared_ptr<CoordConverter> converter;
};