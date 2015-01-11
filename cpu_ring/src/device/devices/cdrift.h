#ifndef CDRIFT_H
#define CDRIFT_H

#include "../CDevice.h"
#include "../DeviceParameters.h"

class CDrift : public CDevice
{
public:
    CDrift(const string& name, const DeviceParameters& params);
    virtual void initMatrices() override;
};

#endif // CDRIFT_H
