#ifndef  __VISIONDETECT_CMREPORTCENTER__
#define  __VISIONDETECT_CMREPORTCENTER__
#include "IMReport.h"
#include "CMReport.h"
class CMReportCenter : IMReportCenter
{
	  CMReportCenter();
	~CMReportCenter();
private:
	friend class CMCtrlCenter;
	CMReport * m_Report;
private:
	void StartReportThreads(){ASSERT(0!=m_Report);m_Report->Run();}
	virtual void DoReport(CMData* pData);
};
#endif