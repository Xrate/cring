#pragma once

#include "../global.h"
#include "DeviceParameters.h"
#include "../beam/CBeam.h"
#include "../field_maps/FieldMap.h"

class CDevice
{
public:
	static shared_ptr<CDevice> createDevice(const DeviceParameters& params);
	explicit CDevice(const string& name_, const string& mapFileName_);
	virtual ~CDevice(){}
	virtual void affectBeam(const shared_ptr<CBeam> beam) const;
protected:
	void generateTwissMatrices();
	virtual void initDevice() = 0;

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

	shared_ptr<const FieldMap> fieldMap;
	bool hasMap;
private:
	void affectParticle1stOrder(Particle& particle) const;
	void affectParticleWithMap(Particle& particle) const;
};
