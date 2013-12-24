#ifndef  __VISIONDETECT_CMRECVCENTER__
#define  __VISIONDETECT_CMRECVCENTER__
#include "IMRecv.h"
#include "CMRecv.h"
class CMRecvCenter : IMRecvCenter
{
	  CMRecvCenter();
	~CMRecvCenter();
private:
	friend class CMCtrlCenter;
    CMRecv* m_Recv;
private:
	void StartRecvThreads(){ASSERT(0!=m_Recv);m_Recv->Run();}
    virtual void RecvData(CMData* pData) ;
};
#endif