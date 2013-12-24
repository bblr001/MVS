#include "StdAfx.h"
#include "CMFilterCenter.h"
#include "CMCtrolCenter.h"
inline void CMFilterCenter::FilterData(CMData* pData)
{
   m_pCtrlCenter->ReportData(pData);
}
inline void CMFilterCenter::DoFilter(CMData* pData)
{
	if (m_Filter->m_pDataList.size()<NUM_BUFFER )
	{
		m_Filter->m_pDataList.push_back(pData);
	}
	else
	{
		delete pData;
	}
}
CMFilterCenter::CMFilterCenter():m_Filter(0)
{
	if(0==m_Filter)
		m_Filter = new CMFilter;
	m_Filter->RegisterCenter(this);
}
CMFilterCenter::~CMFilterCenter()
{
	if(0!=m_Filter)
		delete m_Filter;
	m_Filter =0;
}