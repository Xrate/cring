#ifndef CRING_H
#define CRING_H
#include "RingConf.h"


class CRing
{
public:
	static CRing const* getInstance(RingConf config);
	static CRing const* getInstance();
	void setConf(const RingConf& config);
private:
	explicit CRing(const RingConf& config);

	CRing(const CRing&){}
	static CRing* instance;
};

#endif // CRING_H
