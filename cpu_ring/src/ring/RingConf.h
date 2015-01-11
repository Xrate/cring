#ifndef RINGCONF_H
#define RINGCONF_H
#include "../device/DeviceParameters.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

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
		cout << "RingConf: enum FileNames error." << endl;
		exit(EXIT_FAILURE);
		return string();
	}
};

class RingConf
{
public:
	explicit RingConf(FileNames fileNames);
	const map<string, DeviceParameters*>& getDevicesList() const;
	const vector<string>& getStructure() const;
private:
	void readParams(string fileName, DeviceType type);
	void readStructure(string fileName);
	map<string, DeviceParameters*> devices;
	vector<string> structure;
};
#endif // RINGCONF_H
