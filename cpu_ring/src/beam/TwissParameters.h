#ifndef TWISS_H
#define TWISS_H
struct TwissParameters
{
	TwissParameters(double bet, double gam, double emt);
	double alf;
	double bet;
	double gam;
	double emt;
	double coordMax;
	double angleMax;
};
#endif // TWISS_H