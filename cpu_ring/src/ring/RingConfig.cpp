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

void RingConfig::readParams(FileNames fileNames, DeviceType type)
{
	ifstream file(fileNames.fileName(type));
	if (!file)
		throw exception(("File " + fileNames.fileName(type) + " cannot be found").c_str());
	
	string line;
	while (getline(file, line))
	{
		if (line.empty() || line.at(0) == '#')
			continue;
		istringstream iss(line);
		vector<string> words{ istream_iterator<string>{iss},
							  istream_iterator<string>{} };

		if (words.size() != 5)
			throw exception(("File " + fileNames.fileName(type) + " has wrong format").c_str());

		string name(words.at(0));
		double length = atof(words.at(1).c_str());
		double force = atof(words.at(2).c_str());
		double appX = atof(words.at(3).c_str());
		double appY = atof(words.at(4).c_str());
		auto dParams = make_shared<DeviceParameters>(name, type, length, force, appX, appY);
		devices.insert(pair<string, shared_ptr<DeviceParameters>>(name, dParams));
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