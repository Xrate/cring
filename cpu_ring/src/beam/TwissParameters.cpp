#include "TwissParameters.h"
#include <cmath>

TwissParameters::TwissParameters(double bet, double gam, double emt) :
bet(bet), gam(gam), emt(emt)
{
	alf = sqrt(bet*gam - 1);
	coordMax = sqrt(bet * emt);
	angleMax = sqrt(gam * emt);
}