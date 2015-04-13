#pragma once

#include "geometry.h"

struct Particle;

class CoordConverter
{
public:
    virtual Point  toPlain         (      double    X ,
                                          double    Y ) const      = 0;
    virtual Plane  getNextPlane    (                  ) const      = 0;
    virtual Vector getMomentum     (const Particle& p ) const      = 0;
    virtual void   applyNewMomentum(      Particle& p ,
                                    const Vector&   m ) const      = 0;

            void   trackDeviceStep (const size_t*   iS){ dev_step = iS; }
    virtual       ~CoordConverter  (                  ){}

protected:
    const size_t*  dev_step;
};