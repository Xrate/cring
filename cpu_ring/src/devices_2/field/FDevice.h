#include "global.h"
#include "devices_2/common/Device.h"
#include "field_map/DeviceFieldMap.h"

class CBeam;
class DeviceParameters;

class FDevice : public virtual Device
{
public:
    explicit      FDevice   (const string&          name_)               ;
    virtual      ~FDevice   (                            ){}
    virtual  void affectBeam(const shared_ptr<CBeam> beam) const override;
protected:
    unique_ptr<DeviceFieldMap> fieldMap;
};