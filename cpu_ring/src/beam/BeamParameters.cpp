#include "BeamParameters.h"
#include <fstream>
#include <sstream>

const BeamParameters& BeamParameters::readBeamParameters(string fileName)
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

    return BeamParameters(params.data);
}

BeamParameters::BeamParameters(const double params[10])
{
    twissX.alf = params[0];                           twissY.alf = params[1];
    twissX.bet = params[2];                           twissY.bet = params[3];
    twissX.emt = params[4]*1.e-6;                     twissY.emt = params[5]*1.e-6;
    twissX.gam = (1. + sqr(twissX.alf)) / twissX.bet; twissY.gam = (1. + sqr(twissY.alf)) / twissY.bet;

    numParticles = static_cast<size_t>(params[8]);
    numTurns = static_cast<size_t>(params[9]);
    distType = UNIFORM;
    energy = params[6];
    momentumSpread = params[7]*0.;
}