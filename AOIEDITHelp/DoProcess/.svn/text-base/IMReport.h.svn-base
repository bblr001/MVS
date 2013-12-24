#ifndef __VISIONDETECT_IMREPORT__
#define __VISIONDETECT_IMREPORT__
#include "CMData.h"
class IMReportCenter{
public:
	  IMReportCenter(void){}
	~IMReportCenter(void){}
public:
	friend class CMCtrlCenter;
	virtual void DoReport(CMData* pData) = 0;
	CMCtrlCenter *GetCtrlCenter(){return m_pCtrlCenter;}
protected:
    CMCtrlCenter * m_pCtrlCenter;
	void RegCtrlCenter(CMCtrlCenter * pCtrlCenter){ASSERT(0!=pCtrlCenter);m_pCtrlCenter = pCtrlCenter;}
};
class IMReport{
public:
       IMReport(void);
	~IMReport(void);
public:
	void RegisterCenter(IMReportCenter* pCenter)
	{ASSERT(pCenter);m_pCenter = pCenter;}
protected:
    IMReportCenter* m_pCenter;
	virtual void DoReport(CMData* pData)=0;
};
#endif