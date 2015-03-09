#pragma once

#include "device/CDevice.h"

class CQuadrupole : public CDevice
{
public:
    explicit CQuadrupole(const DeviceParameters& params);
    virtual void initDevice() override;
    void affectBeam(const shared_ptr<CBeam> beam) const override;
private:
    double force;
    void generateMatrices(vector<double[6]> &MxP_all, vector<double[6]>& MyP_all, const shared_ptr<CBeam> beam) const;
};
