
#ifndef __VISIONDETECTION_CMFILTER__
#define __VISIONDETECTION_CMFILTER__
#include "IMActiveObj.h"
#include "IMFilter.h"
#include <list>
class CMFilter : public IMFilter,IActiveObj
{
	 CMFilter(void);
	~CMFilter();
private:
	friend class CMFilterCenter;
 	virtual DWORD Main();
	virtual void DoFilter(CMData* pData);
private:
	std::list<CMData*> m_pDataList;
};
#endif