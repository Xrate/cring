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

const map<string, DeviceParameters*>& RingConf::getDevicesList() const
{
	if (!devices.empty())
		return devices;
	cout << "RingConf: Try use devices var without init" << endl;
	exit(EXIT_FAILURE);
	return devices;
}

const vector<string>& RingConf::getStructure() const
{
	if (!structure.empty())
		return structure;
	cout << "RingConf: Try use structure var without init" << endl;
	exit(EXIT_FAILURE);
	return structure;
}

void RingConf::readParams(string fileName, DeviceType type)
{
	size_t numFields = type == DRIFT ? 4 : 5;
	ifstream file(fileName);
	string line;
	while (getline(file, line))
	{
		if (line.at(0) == '#')
			continue;
		istringstream iss(line);
		vector<string> words{ istream_iterator<string>{iss},
							  istream_iterator<string>{} };
		if (words.size() == numFields)
		{
			string name(words.at(0));
			double length = atof(words.at(1).c_str());
			double force = atof(words.at(2).c_str());
			double appX = atof(words.at(3).c_str());
			double appY = atof(words.at(4).c_str());
			auto device = new DeviceParameters(name, type, length, force, appX, appY);
			devices.insert(pair<string, DeviceParameters*>(name, device));
		}
	}
}

void RingConf::readStructure(string fileName)
{
	ifstream file(fileName);
	string line;
	while (getline(file, line) && !line.at(0) == '#')
		structure.push_back(line);
}