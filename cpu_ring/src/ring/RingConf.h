#ifndef RINGCONF_H
#define RINGCONF_H
#include "../global.h"
#include "../device/DeviceParameters.h"
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

class RingConf
{
public:
	explicit RingConf(FileNames fileNames);
	const map<string, DeviceParameters*>& getDevicesMap() const;
	const vector<string>& getStructure() const;
private:
	void readParams(string fileName, DeviceType type);
	void readStructure(string fileName);
	map<string, DeviceParameters*> devices;
	vector<string> structure;
};
#endif // RINGCONF_H
