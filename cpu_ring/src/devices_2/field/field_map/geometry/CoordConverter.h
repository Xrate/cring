#pragma once

#include "geometry.h"

struct Particle;

class CoordConverter
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

    virtual       ~CoordConverter  (                  ){}

protected:
    const size_t*  dev_step;
};