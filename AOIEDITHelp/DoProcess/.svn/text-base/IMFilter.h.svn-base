#ifndef __VISIONDETECT_IMFILTER__
#define __VISIONDETECT_IMFILTER__
#include "CMData.h"
class IMFilterCenter{
public:
	  IMFilterCenter(void){}
	~IMFilterCenter(void){}
public:
	friend class CMCtrlCenter;
	virtual void FilterData(CMData* pData) = 0;
	virtual void DoFilter(CMData* pData) = 0;
	CMCtrlCenter *GetCtrlCenter(){return m_pCtrlCenter;}
protected:
	CMCtrlCenter * m_pCtrlCenter;
	void RegCtrlCenter(CMCtrlCenter * pCtrlCenter){ASSERT(0!=pCtrlCenter);m_pCtrlCenter = pCtrlCenter;}
};
class IMFilter{

public:
       IMFilter(void);
	~IMFilter(void);
public:
	void RegisterCenter(IMFilterCenter* pCenter)
	{ASSERT(pCenter);m_pCenter = pCenter;}
protected:
	IMFilterCenter* m_pCenter;
	virtual void DoFilter(CMData* pData)=0;
    inline void   FilterData(CMData* pData)
	{ASSERT(m_pCenter);return m_pCenter->FilterData(pData);}
};
#endif