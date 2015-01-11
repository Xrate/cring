#ifndef TWISS_H
#define TWISS_H
class TwissParameters
{
public:
	TwissParameters(double bet, double gam, double emt);
	double alf() const;
	double bet() const;
	double gam() const;
	double emt() const;
	double coordMax() const;
	double angleMax() const;
private:
	double alf_;
	double bet_;
	double gam_;
	double emt_;
	double cmx_;
	double amx_;
};
#endif // TWISS_H