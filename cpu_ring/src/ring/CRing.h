#ifndef CRING_H
#define CRING_H
#include "../global.h"
#include "RingConfig.h"
#include "../device/CDevice.h"

class CRing;
typedef shared_ptr<const CRing> CRingPtr;

class CRing
{
public:
	static shared_ptr<const CRing> createInstance(shared_ptr<const RingConfig> config);
	static shared_ptr<const CRing> getInstance();
	const vector<shared_ptr<const CDevice>>& getDevices() const;
	void affectBeam(shared_ptr<CBeam> beam) const;
private:
	explicit CRing(shared_ptr<const RingConfig> config);
	static shared_ptr<const CRing> instance;
	size_t numDevices;
	vector<shared_ptr<const CDevice>> devices;
};

#endif // CRING_H
