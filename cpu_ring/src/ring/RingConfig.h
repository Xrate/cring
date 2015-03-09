#pragma once

#include "global.h"
#include "device/DeviceParameters.h"
#include <map>

struct FileNames
{
    string dipoleFile;
    string driftFile;
    string quadrupoleFile;
    string sextupoleFile;
    string structureFile;

    string fileName(DeviceType type)
    {
        switch (type)
        {
        case DIPOLE: return dipoleFile;
        case DRIFT: return driftFile;
        case QUADRUPOLE: return quadrupoleFile;
        case SEXTUPOLE: return sextupoleFile;
        }
        throw exception("RingConf: enum FileNames error.");
    }
};

class RingConfig
{
public:
    static shared_ptr<const RingConfig> readRingConfig(FileNames fileNames);
    map<string, DeviceParameters> devices;
    vector<string> structure;
private:
    explicit RingConfig(FileNames fileNames);
    void readParams(FileNames fileNames, DeviceType type);
    void readStructure(string fileName);
};
