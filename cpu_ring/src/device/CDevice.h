#ifndef CDEVICE_H
#define CDEVICE_H
#include "../global.h"
#include "DeviceParameters.h"
#include "../beam/CBeam.h"

class CDevice
{
public:
	static CDevice* createDevice(DeviceParameters* params);
	explicit CDevice(const string& name_);
	virtual ~CDevice(){}
	void affectBeam(CBeam* beam);
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
