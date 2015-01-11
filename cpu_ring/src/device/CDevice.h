#ifndef CDEVICE_H
#define CDEVICE_H
#include <string>

using namespace std;

class CDevice
{
public:
	explicit CDevice(const string& name_);
	virtual ~CDevice(){}
protected:
	void generateTwissM();
	virtual void initMatrices() = 0;

	string name;
	double mX_P[3][3];
	double mY_P[3][3];
	double mX_T[3][3];
	double mY_T[3][3];
	double length;
	double step;
	double appertureX;
	double appertureY;
	size_t nSteps;
};
#endif // CDEVICE_H
