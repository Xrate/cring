#include "global.h"
#include "devices_2/common/Device.h"
#include "field_map/DeviceFieldMap.h"

class CBeam;
struct DeviceParameters;

class FDevice : public virtual Device
{
public:
    explicit      FDevice   (const DeviceParameters& params)               ;
    virtual      ~FDevice   (                              ){}
    virtual  void affectBeam(const shared_ptr<CBeam> beam  ) const override;
protected:
    unique_ptr<DeviceFieldMap> fieldMap;
};