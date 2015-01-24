#include "RingConfig.h"
#include <fstream>
#include <sstream>

RingConfig::RingConfig(FileNames fileNames)
{
	readParams(fileNames, DIPOLE);
	readParams(fileNames, DRIFT);
	readParams(fileNames, QUADRUPOLE);
	readParams(fileNames, SEXTUPOLE);
	readStructure(fileNames.structureFile);
}

shared_ptr<const RingConfig> RingConfig::readRingConfig(FileNames fileNames)
{
	return shared_ptr<const RingConfig>(new RingConfig(fileNames));
}

const map<string, shared_ptr<DeviceParameters>>& RingConfig::getDevicesMap() const
{
	if (!devices.empty())
		return devices;
	throw exception("Try to get empty devices map");
}

const vector<string>& RingConfig::getStructure() const
{
	if (!structure.empty())
		return structure;
	throw exception("RingConf: Try use structure var without init");
}

void RingConfig::readParams(FileNames fileNames, DeviceType type)
{
	string fileName = fileNames.fileName(type);
		ifstream file(fileName);
	if (!file)
	{
		throw exception(("File " + fileName + " cannot be found").c_str());
	}
	string line;
	while (getline(file, line))
	{
		if (line.at(0) == '#')
			continue;
		istringstream iss(line);
		vector<string> words{ istream_iterator<string>{iss},
							  istream_iterator<string>{} };
		switch (type)
		{
		case DIPOLE:
		case QUADRUPOLE:
		case SEXTUPOLE: 
			if (words.size() == 5)
			{
				string name(words.at(0));
				double length = atof(words.at(1).c_str());
				double force = atof(words.at(2).c_str());
				double appX = atof(words.at(3).c_str());
				double appY = atof(words.at(4).c_str());
				auto dParams = make_shared<DeviceParameters>(name, type, length, force, appX, appY);
				devices.insert(pair<string, shared_ptr<DeviceParameters>>(name, dParams));
				break;
			}
		case DRIFT: 
			if (words.size() == 4)
			{
				string name(words.at(0));
				double length = atof(words.at(1).c_str());
				double force = 0.;
				double appX = atof(words.at(2).c_str());
				double appY = atof(words.at(3).c_str());
				auto dParams = make_shared<DeviceParameters>(name, type, length, force, appX, appY);
				devices.insert(pair<string, shared_ptr<DeviceParameters>>(name, dParams));
				break;
			}
		default:
			throw exception("RingConf FileNames error");
		}
	}
}

void RingConfig::readStructure(string fileName)
{
	ifstream file(fileName);
	string line;
	while (getline(file, line))
	if (!(line.empty() || line.at(0) == '#'))
		structure.push_back(line);
}