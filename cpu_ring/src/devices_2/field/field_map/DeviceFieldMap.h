#pragma once

#include "global.h"

class ExtendedDeviceFieldMap;
class FieldMapHandler;
class CoordConverter;
struct Point;
struct DeviceGeometry;
struct Particle;
class FDevice;

class NullFieldException{};

class DeviceFieldMap
{
    friend   FDevice;
public:
    explicit       DeviceFieldMap(const ExtendedDeviceFieldMap* map);
    virtual       ~DeviceFieldMap(                       ){}
    virtual  void  updateParticle(Particle& p            ) const;
protected:
    explicit       DeviceFieldMap(const DeviceGeometry&  , 
                                  const string& name     , 
                                  const size_t* step     )      ;
    virtual  Point getField      (const Point&  point    ) const;

    shared_ptr<const FieldMapHandler> device_map;
    shared_ptr<const CoordConverter> converter;
};