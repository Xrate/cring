#pragma once

#include <global.h>
#include "geometry.h"

struct DeviceGeometry;
struct Particle;

class ICoordConverter
{
public:
    virtual Point  toPlain         (      double    X ,
                                          double    Y ,
										  size_t    iS) const      = 0;
    virtual Plane  getPlane        (	  size_t    iS) const      = 0;
    virtual Vector getMomentum     (const Particle& p ,
		                                  size_t    iS) const      = 0;
    virtual void   applyNewMomentum(      Particle& p ,
                                    const Vector&   m ,
									      size_t    iS) const      = 0;

    virtual       ~ICoordConverter  (                  ){}
};

shared_ptr<ICoordConverter> getConverter(const DeviceGeometry& geometry);