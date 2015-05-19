#pragma once

#include "global.h"
#include <device/common/DeviceParameters.h>
#include <map>

struct FileNames
{
    string dipoleFile;
    string driftFile;
    string quadrupoleFile;
    string sextupoleFile;
    string structureFile;

    string fileName(DeviceType type);
};

class RingConfig
{
public:
	explicit RingConfig(FileNames fileNames);
    static shared_ptr<const RingConfig> readRingConfig(FileNames fileNames);
    map<string, DeviceParameters> devices;
    vector<string> structure;
private:
    void readParams(FileNames fileNames, DeviceType type);
    void readStructure(string fileName);
};
