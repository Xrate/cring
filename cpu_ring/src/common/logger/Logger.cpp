#include "Logger.h"
#include <chrono>
#include <sstream>
#include <direct.h>

double Logger::path = 0.;
string Logger::dirName = "";

void Logger::GenerateDir()
{
	stringstream dirNameSS;
	auto end = chrono::system_clock::now();
	time_t end_time = chrono::system_clock::to_time_t(end);
	dirNameSS << "Log at " << ctime(&end_time);
	dirName = dirNameSS.str();
	mkdir(dirName.c_str());
}

void Logger::setUpLogger()
{
	GenerateDir();
}

void Logger::closeLogger()
{

}