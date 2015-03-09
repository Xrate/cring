#include "BeamParameters.h"
#include <fstream>
#include <sstream>

TwissParameters::TwissParameters(double alf, double bet, double emt) :
alf(alf), bet(bet), emt(emt), gam((1. + sqr(alf)) / bet)
{
}

BeamParameters BeamParameters::readBeamParameters(string fileName)
{
    ifstream file(fileName);
    if (!file) throw exception(("File " + fileName + " cannot be found").c_str());

    string line;
    vector<double> params;
    while (getline(file, line))
    {
        if (line.empty() || line.at(0) == '#') continue;

        stringstream lineStream(line);
        double param = -NAN;
        lineStream >> param;
        if (param == -NAN) throw exception(("File " + fileName + " has wrong format").c_str());

        params.push_back(param);
    }

    if (params.size() != 10) throw exception(("File " + fileName + " has wrong format").c_str());

    TwissParameters tX(params.at(0), params.at(2), params.at(4)*1.e-6);
    TwissParameters tY(params.at(1), params.at(3), params.at(5)*1.e-6);

    return BeamParameters{ tX, tY, static_cast<size_t>(params.at(8)),
        static_cast<size_t>(params.at(9)), UNIFORM, params.at(6), params.at(7)*0. };
}