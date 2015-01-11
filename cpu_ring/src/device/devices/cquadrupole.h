#ifndef CQUADRUPOLE_H
#define CQUADRUPOLE_H

#include "../CDevice.h"
#include "../DeviceParameters.h"

class CQuadrupole : public CDevice
{
public:
	CQuadrupole(const string& name, const DeviceParameters& params);
    virtual void initMatrices() override;
private:
    double force;
};

#endif // CQUADRUPOLE_H
