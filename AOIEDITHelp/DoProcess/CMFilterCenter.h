#ifndef  __VISIONDETECT_CMFILTERCENTER__
#define  __VISIONDETECT_CMFILTERCENTER__
#include "IMFilter.h"
#include "CMFilter.h"
class CMFilterCenter : IMFilterCenter
{
	CMFilterCenter();
  ~CMFilterCenter();
private:
	friend class CMCtrlCenter;
	CMFilter * m_Filter;
private:
	void StartFilterThreads(){ASSERT(0!=m_Filter);m_Filter->Run();}
	virtual void FilterData(CMData* pData) ;
	virtual void DoFilter(CMData* pData);
};
#endif