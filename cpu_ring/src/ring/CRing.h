#ifndef CRING_H
#define CRING_H
#include "RingConf.h"
#include "../device/CDevice.h"

class CRing
{
public:
	static CRing * getInstance(RingConf config);
	static CRing * getInstance();
	void setConf(const RingConf& config);
private:
	explicit CRing(const RingConf& config);
	CRing(const CRing&){}

	static CRing* instance;
	size_t numDevices;
	vector<CDevice*> devices;
};

#endif // CRING_H
