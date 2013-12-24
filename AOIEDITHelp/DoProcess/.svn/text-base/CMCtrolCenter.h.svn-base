#pragma once
#include "CMRecvCenter.h"
#include "CMFilterCenter.h"
#include "CMReportCenter.h"
class CMCtrlCenter{
public:
	~CMCtrlCenter(void);
	static CMCtrlCenter& GetCtrlCenter();
private:
	CMCtrlCenter();
	CMReportCenter m_ReportCenter;
	CMFilterCenter m_FilterCenter;
	CMRecvCenter   m_RecvCenter;
public://threads something
	bool   m_bthreadsAreRun;
	bool m_bParamChanged;
	bool m_bSaveBtnClicked;
	HANDLE m_recvThrHandle;
	HANDLE m_filterThrHandle;
	HANDLE m_reportThrHandle;

	HANDLE m_newImageEvent;
	HANDLE m_newResultEvent;
	HANDLE m_containerIsFreeEvent;
	HANDLE m_stopThreadEvent;
	HANDLE m_pauseThreadEvent;
 
	CRITICAL_SECTION m_ReciveDataMutex;
	CRITICAL_SECTION m_ReportDataMutex;
public: //Display something
	HWND  m_SendMsgHWND;
	Hlong m_HalconWindowHD;
	CMData m_CurrentData;
public:
	void FilterData(CMData * pData);
	void ReportData(CMData * pData);
	void StartThreads();
	void StopThreads();
	void ShotGrab();
	CRITICAL_SECTION*  GetReciveDataMutex(){return &m_ReciveDataMutex;};
	CRITICAL_SECTION*  GetReportDataMutex(){return &m_ReportDataMutex;};

private:
	
};
