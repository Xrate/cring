#include "TwissParameters.h"
#include <set>

TwissParameters::TwissParameters(double bet, double gam, double emt) :
bet_(bet), gam_(gam), emt_(emt)
{
	alf_ = sqrt(bet_*gam_ - 1);
	cmx_ = sqrt(bet_ * emt_);
	amx_ = sqrt(gam_ * emt_);
}

double TwissParameters::alf() const { return alf_; }
double TwissParameters::bet() const { return bet_; }
double TwissParameters::gam() const { return gam_; }
double TwissParameters::emt() const { return emt_; }
double TwissParameters::coordMax() const { return cmx_; }
double TwissParameters::angleMax() const { return amx_; }