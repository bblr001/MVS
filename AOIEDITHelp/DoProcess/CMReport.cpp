#include "StdAfx.h"
#include "CMReport.h"
#include "CMCtrolCenter.h"
#include "ActionHalcon.h"
CMReport::CMReport(void):m_MsgHWND(0)
{
}
CMReport::~CMReport()
{
	TRACE1("\n--RCNT %d-----\n",m_pDataList.size());
	while(!m_pDataList.empty())
	{
		delete m_pDataList.front();
		m_pDataList.pop_front();
	}
}
inline void CMReport::DoReport(CMData* pData)
{
	SendMessage(m_MsgHWND,MSG_REPORT,(WPARAM)&(pData->m_vSubTestResult),(LPARAM)0);
}
DWORD CMReport::Main()
{
	CMData* pData=0;

	HANDLE EventHandle[2];
	m_pCenter->GetCtrlCenter()->m_reportThrHandle = this->m_Handle;
    EventHandle[1] = m_pCenter->GetCtrlCenter()->m_stopThreadEvent;
	EventHandle[0] = m_pCenter->GetCtrlCenter()->m_newResultEvent;
	HANDLE ContainerIsFreeEvnt = m_pCenter->GetCtrlCenter()->m_containerIsFreeEvent;
	HANDLE pauseEvent = m_pCenter->GetCtrlCenter()->m_pauseThreadEvent;
	CRITICAL_SECTION * cs = &m_pCenter->GetCtrlCenter()->m_ReportDataMutex;
	m_MsgHWND = m_pCenter->GetCtrlCenter()->m_SendMsgHWND;
	while(WAIT_OBJECT_0 == WaitForMultipleObjects(2,EventHandle,FALSE,INFINITE))
	{

		EnterCriticalSection(cs);
		pData = m_pDataList.front();
		LeaveCriticalSection(cs);
		CMCtrlCenter::GetCtrlCenter().m_CurrentData = *pData;
		m_pDataList.pop_front();
	    SetEvent(ContainerIsFreeEvnt);
	    //if(pData->m_isDebug)
	   
		//disp_obj(pData->m_ErrorRegist,pData->m_ShowHWindow);
	   
	   
	   DoReport(pData);
	   if(0!=pData) delete pData;
	   Sleep(0);
	}
    SetEvent(ContainerIsFreeEvnt);
	TRACE0("------------Report Thread Exit-------------\n");
	return 0;
}