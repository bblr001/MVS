#include "StdAfx.h"
#include "CMRecv.h"
#include "CMCtrolCenter.h"
#include "CMData.h"
#include "ActionHalcon.h"
CMRecv::CMRecv(void)
{
}
inline void CMRecv::DoRecv(CMData* pData)
{
	AAction::Acquirsition::acquire(pData);
}
DWORD CMRecv::Main()
{
	m_pCenter->GetCtrlCenter()->m_recvThrHandle = this->m_Handle;
	HANDLE stopEvent = m_pCenter->GetCtrlCenter()->m_stopThreadEvent;
	HANDLE newImageEvent = m_pCenter->GetCtrlCenter()->m_newImageEvent;
	HANDLE pauseEvent = m_pCenter->GetCtrlCenter()->m_pauseThreadEvent;
	Hlong  Halcon_WndID = m_pCenter->GetCtrlCenter()->m_HalconWindowHD;
	AAction::Acquirsition::InitializeRead();
	while(WAIT_OBJECT_0 != WaitForSingleObject(stopEvent,0))
	{
		 CMData* pData = new CMData();
		 pData->m_ShowHWindow = Halcon_WndID;
		 pData->m_isDebug=true;
		 WaitForSingleObject(pauseEvent,INFINITE);
		 DoRecv(pData);
		 RecvData(pData);
		 SetEvent(newImageEvent);
	     Sleep(0);
	}
    ResetEvent(newImageEvent);
	TRACE0("------------Recv Thread Exit-------------\n");
	return 0;
}