#ifndef  __VISIONDETECTION_CMRECV__
#define __VISIONDETECTION_CMRECV__
#include "IMActiveObj.h"
#include "IMRecv.h"
class CMRecv : public IMRecv,IActiveObj
{
public: 
	CMRecv(void);
private:
	friend class CMRecvCenter;
	DWORD Main();
	virtual void DoRecv(CMData* pData);
	};
#endif