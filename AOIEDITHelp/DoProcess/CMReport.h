#ifndef  __VISIONDETECTION_CMREPORT__
#define __VISIONDETECTION_CMREPORT__
#include "IMActiveObj.h"
#include "IMReport.h"
#include <list>
class CMReport : public IMReport,IActiveObj
{
	  CMReport(void);
	~CMReport();
private:
	friend class CMReportCenter;
	virtual DWORD Main();
	virtual void DoReport(CMData* pData);
private:
	std::list<CMData*> m_pDataList;
	HWND    m_MsgHWND;
};
#endif