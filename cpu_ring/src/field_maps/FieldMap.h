#pragma once

#include "global.h"
#include "field_maps/FieldMapData.h"
#include "beam/Particle.h"
#include <map>

class FieldMap
{
public:
    static shared_ptr<const FieldMap> getFieldMap(const string& fileName);

    void affectParticle(Particle& p, const double angle, const double length, 
                        const size_t nSteps, const size_t iS) const;

    FieldMap::~FieldMap();
private:
    static map<string, shared_ptr<const FieldMap>> fieldMaps;
    FieldMap(const string& fileName);

    physics::FieldMapData data;
};