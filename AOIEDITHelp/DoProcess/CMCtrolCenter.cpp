#include "stdafx.h"
#include "CMCtrolCenter.h"
#include "CMData.h"

CMCtrlCenter::CMCtrlCenter():
    m_bParamChanged(false),
	m_bSaveBtnClicked(false)
{
	InitializeCriticalSection(&m_ReciveDataMutex);
	InitializeCriticalSection(&m_ReportDataMutex);
    m_newImageEvent =  CreateEvent(NULL,FALSE,FALSE,NULL);
	m_newResultEvent =  CreateEvent(NULL,FALSE,FALSE,NULL);
    m_containerIsFreeEvent =  CreateEvent(NULL,FALSE,TRUE,NULL);
    m_stopThreadEvent =  CreateEvent(NULL,TRUE,FALSE,NULL);
	m_pauseThreadEvent=  CreateEvent(NULL,FALSE,TRUE,NULL);
    m_bthreadsAreRun = false;
	m_ReportCenter.RegCtrlCenter(this);
	m_FilterCenter.RegCtrlCenter(this);
	m_RecvCenter.RegCtrlCenter(this);
}
CMCtrlCenter::~CMCtrlCenter(void)
{
	if(m_bthreadsAreRun)
	{
		SetEvent(m_pauseThreadEvent);
		SetEvent(m_stopThreadEvent);
		WaitForSingleObject(m_recvThrHandle,INFINITE);
		WaitForSingleObject(m_filterThrHandle,INFINITE);
		WaitForSingleObject(m_reportThrHandle,INFINITE);
	}
	CloseHandle(m_stopThreadEvent);
	CloseHandle(m_newImageEvent);
	CloseHandle(m_newResultEvent);
	CloseHandle(m_containerIsFreeEvent);
	
	CloseHandle(m_reportThrHandle);
	CloseHandle(m_filterThrHandle);
	CloseHandle(m_recvThrHandle);
	DeleteCriticalSection(&m_ReciveDataMutex);
	DeleteCriticalSection(&m_ReportDataMutex);
}
CMCtrlCenter& CMCtrlCenter::GetCtrlCenter()
{
	static CMCtrlCenter _ctrlCenter;
	return _ctrlCenter;
}
void CMCtrlCenter::StartThreads()
{
	if(!m_bthreadsAreRun)
	{
		ResetEvent(m_stopThreadEvent);
		ResetEvent(m_newImageEvent);
		ResetEvent(m_newResultEvent);
        SetEvent(m_containerIsFreeEvent);
		SetEvent(m_pauseThreadEvent);
	    m_ReportCenter.StartReportThreads();
		m_FilterCenter.StartFilterThreads();
		m_RecvCenter.StartRecvThreads();
		m_bthreadsAreRun = true;
		//ShotGrab();
	}
}
void CMCtrlCenter::ShotGrab()
{
	SetEvent(m_pauseThreadEvent);
}
void CMCtrlCenter::StopThreads()
{
	if(m_bthreadsAreRun)
	{
		SetEvent(m_pauseThreadEvent);
		SetEvent(m_stopThreadEvent);
		m_bthreadsAreRun = false;
	}
}
void CMCtrlCenter::FilterData(CMData * pData)
{
	EnterCriticalSection(&m_ReciveDataMutex);
     m_FilterCenter.DoFilter(pData);
	LeaveCriticalSection(&m_ReciveDataMutex);
}
void CMCtrlCenter::ReportData(CMData *pData)
{
	EnterCriticalSection(&m_ReportDataMutex);
    m_ReportCenter.DoReport(pData);
	LeaveCriticalSection(&m_ReportDataMutex);
}