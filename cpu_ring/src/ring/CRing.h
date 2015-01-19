#ifndef CRING_H
#define CRING_H
#include "../global.h"
#include "RingConfig.h"
#include "../device/CDevice.h"

class CRing
{
public:
	static CRing * getInstance(RingConfig* config);
	static CRing * getInstance();
	static void destroyInstance();
	void setConf(RingConfig* config);
	const vector<CDevice*>& getDevices() const;
	void affectBeam(CBeam* beam, size_t nTurns);
	
private:
	explicit CRing(RingConfig* config);
	~CRing();
	static CRing* instance;
	size_t numDevices;
	vector<CDevice*> devices;
};

#endif // CRING_H
