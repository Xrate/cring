#include "RingConfig.h"
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <iterator>

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
    return make_shared<RingConfig const>(fileNames);
}

void RingConfig::readStructure(string fileName)
{
    ifstream file(fileName);
    string line;
    while (getline(file, line))
        if (!(line.empty() || line.at(0) == '#')) 
			structure.push_back(line);
}

static inline string getDirName(const string& str)
{
    return str.substr(0, str.find_last_of("/\\"));
}

static inline string verifyFile(const string& name) 
{
    struct stat buffer;
    return stat(name.c_str(), &buffer) == 0 ? name : "";
}

void RingConfig::readParams(FileNames fileNames, DeviceType type)
{
	string fileName = fileNames.fileName(type);
	ifstream file(fileName);
    if (!file) 
		throw exception(("File " + fileName + " cannot be found").c_str());
    
    string dirName = getDirName(fileName);

    string line;
    while (getline(file, line))
    {
        if (line.empty() || line.at(0) == '#') continue;

        istringstream iss(line);
        vector<string> words{ istream_iterator<string>{iss}, istream_iterator<string>{} };

		if (words.size() < 5 || words.size() > 6) 
			throw exception(("File " + fileName + " has wrong format").c_str());

        string name(words.at(0));
        double length = atof(words.at(1).c_str());
        double force = atof(words.at(2).c_str());
        double appX = atof(words.at(3).c_str());
        double appY = atof(words.at(4).c_str());
        string mapFileName = words.size() == 6 ? verifyFile(dirName + "/" + words.at(5) + ".table") : "";

        DeviceParameters dParams = { name, type, length, force, appX, appY, mapFileName };
        devices.insert(pair<string, DeviceParameters>(name, dParams));
    }
}

string FileNames::fileName(DeviceType type)
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