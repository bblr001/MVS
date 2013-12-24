#ifndef __VISIONDETECT_IMRECV__
#define __VISIONDETECT_IMRECV__
#include "CMData.h"
class IMRecvCenter{
public:
        IMRecvCenter(void){}
     ~IMRecvCenter(void){}
public:
    friend class CMCtrlCenter;
	virtual void RecvData(CMData* pData) = 0;
	CMCtrlCenter *GetCtrlCenter(){return m_pCtrlCenter;}
protected:
	CMCtrlCenter * m_pCtrlCenter;
	void RegCtrlCenter(CMCtrlCenter * pCtrlCenter){ASSERT(0!=pCtrlCenter);m_pCtrlCenter = pCtrlCenter;}
};
class IMRecv{
public:
       IMRecv(void);
	 ~IMRecv(void);
public:
	void RegisterCenter(IMRecvCenter* pCenter)
	{ASSERT(pCenter);m_pCenter = pCenter;}
protected:
	IMRecvCenter* m_pCenter;
	virtual void DoRecv(CMData* pData)=0;
	inline void RecvData(CMData* pData)
	{ASSERT(m_pCenter);return m_pCenter->RecvData(pData);}
};
#endif