#include "StdAfx.h"
#include "CMFilter.h"
#include "CMCtrolCenter.h"
#include "ActionHalcon.h"
CMFilter::CMFilter(void)
{
}
CMFilter::~CMFilter()
{
	TRACE1("\n--CNT %d-----\n",m_pDataList.size());
	while(!m_pDataList.empty())
	{
		delete m_pDataList.front();
		m_pDataList.pop_front();
	}
}
inline void CMFilter::DoFilter(CMData* pData)
{
	MandrillRegionOp::display(pData);
	MandrillRegionOp::action(pData);
}

DWORD CMFilter::Main()
{
	//SetThreadPriority(m_Handle,THREAD_PRIORITY_ABOVE_NORMAL);
	m_pCenter->GetCtrlCenter()->m_filterThrHandle = m_Handle;
	CMData* pData = 0;
	HANDLE EventHandle[2];
    EventHandle[1] = m_pCenter->GetCtrlCenter()->m_stopThreadEvent;
	EventHandle[0] = m_pCenter->GetCtrlCenter()->m_newImageEvent;
	HANDLE ContainerIsFreeEvnt = m_pCenter->GetCtrlCenter()->m_containerIsFreeEvent;
	HANDLE newResultEvent = m_pCenter->GetCtrlCenter()->m_newResultEvent;
    CRITICAL_SECTION * cs = &m_pCenter->GetCtrlCenter()->m_ReciveDataMutex;
	/*Halcon::HTuple T1,T2;*/
	MandrillRegionOp::display_init();
	while(WAIT_OBJECT_0 == WaitForMultipleObjects(2,EventHandle,FALSE,INFINITE))
	{
        EnterCriticalSection(cs);
		pData = m_pDataList.front();
		m_pDataList.pop_front();
		LeaveCriticalSection(cs);
		WaitForSingleObject(ContainerIsFreeEvnt,INFINITE);
		if(0!=pData)
		{
			/*Halcon::count_seconds(&T1);*/
		 	DoFilter(pData);
            /*Halcon::count_seconds(&T2);*/
			FilterData(pData);
		}
		SetEvent(newResultEvent);
		Sleep(0);
	}
    ResetEvent(newResultEvent);
	MandrillRegionOp::display_close();
	TRACE0("------------Filter Thread Exit-------------\n");
	return 0;
}