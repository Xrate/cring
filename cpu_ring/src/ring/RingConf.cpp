#include "RingConf.h"
#include <fstream>
#include <sstream>

RingConf::RingConf(FileNames fileNames)
{
	readParams(fileNames.fileName(DIPOLE), DIPOLE);
	readParams(fileNames.fileName(DRIFT), DRIFT);
	readParams(fileNames.fileName(QUADRUPOLE), QUADRUPOLE);
	readParams(fileNames.fileName(SEXTUPOLE), SEXTUPOLE);
	readStructure(fileNames.structureFile);
}

const map<string, DeviceParameters*>& RingConf::getDevicesMap() const
{
	if (!devices.empty())
		return devices;
	throw exception("Try to get empty devices map");
}

const vector<string>& RingConf::getStructure() const
{
	if (!structure.empty())
		return structure;
	throw exception("RingConf: Try use structure var without init");
}

void RingConf::readParams(string fileName, DeviceType type)
{
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
				auto device = new DeviceParameters(name, type, length, force, appX, appY);
				devices.insert(pair<string, DeviceParameters*>(name, device));
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
				auto device = new DeviceParameters(name, type, length, force, appX, appY);
				devices.insert(pair<string, DeviceParameters*>(name, device));
				break;
			}
		default:
			throw exception("RingConf FileNames error");
		}
	}
}

void RingConf::readStructure(string fileName)
{
	ifstream file(fileName);
	string line;
	while (getline(file, line))
	if (!(line.at(0) == '#'))
		structure.push_back(line);
}