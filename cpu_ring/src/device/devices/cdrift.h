#ifndef CDRIFT_H
#define CDRIFT_H

#include "../CDevice.h"
#include "../DeviceParameters.h"

class CDrift : public CDevice
{
public:
	explicit CDrift(const shared_ptr<const DeviceParameters> params);
    virtual void initMatrices() override;
};

#endif // CDRIFT_H
