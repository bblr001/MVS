#include "StdAfx.h"
#include "CMReportCenter.h"

inline void CMReportCenter::DoReport(CMData* pData)
{
    m_Report->m_pDataList.push_back(pData);
}
CMReportCenter::CMReportCenter():m_Report(0)
{
	if(0==m_Report)
		m_Report = new CMReport;
	m_Report->RegisterCenter(this);
}
CMReportCenter::~CMReportCenter()
{
	if(0!=m_Report)
		delete m_Report;
	m_Report =0;
}