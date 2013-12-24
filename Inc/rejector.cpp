#pragma once


#include "stdafx.h"
#include "rejector.h"
#include "TLog.h"
#include "PanelManager.h"
#include <time.h>
#include "ConfigurationManager.h"

extern MvsConfigurationManager           gConfigManager;

UINT CAlarmSentry::Main()
{
	m_bExit = false;
	while(!m_bExit)
	{
		if(!m_alarmSignals.is_not_empty())
		{
			if (m_bExit)
			{
				break;
			}
			Sleep(2);
			continue;
		}
		int alarmPort = -1;
		m_alarmSignals.pop_back(&alarmPort);
		if(0 <= alarmPort && alarmPort <= 15)
		{
			/// poll the dismissing alarm port of PCI
			if(CPanelManager::GetPanelManager().GetPortST(0))
			{
				// dismiss the current alarm
				TLOG_NOTICE(_T("dismiss the current alarm"));
				CPanelManager::GetPanelManager().SetPortST(alarmPort, ALL_CLEAR);
				CPanelManager::GetPanelManager().CloseAllAlarm();
			}
			else
			{
				if (m_alarmSignals.is_not_full())
				{
					m_alarmSignals.push_front(alarmPort);
				}
			}
		}
		Sleep(10);
	}

	return 0;
}

CRejector::CRejector():m_signalTimestamp(256)
{
	m_isExit = false;
	m_bPciIsReady = false;
	m_nRejectPort = -1;
	m_nAlarmPort  = -1;
	m_Reject_Delay = 10;
	m_Encoder2ARTCard=false;
}

CRejector::~CRejector()
{
	if(m_bPciIsReady)
	{
		PCI2312_ReleaseSystemEvent(m_hEventInt);

		PCI2312_ReleaseDeviceInt(m_hPCI2312Device);	// 释放中断资源
		PCI2312_ReleaseDevice(m_hPCI2312Device);		// 释放设备对象
	}
}

bool CRejector::Init()
{
	try
	{
		m_hPCI2312Device = PCI2312_CreateDevice(0);	// 创建设备对象
 		if(m_hPCI2312Device == INVALID_HANDLE_VALUE)
 		{
 			TLOG_ERROR(_T("Create PCI2312 Device Error..."));
			return false;
 		}

 		m_hEventInt = PCI2312_CreateSystemEvent(); // 创建中断事件句柄
		if(m_hEventInt == INVALID_HANDLE_VALUE)
		{
			TLOG_ERROR(_T("CreateSystemEvent Error..."));
			return false;
		}
		if(!PCI2312_InitDeviceInt(m_hPCI2312Device, m_hEventInt))// 初始化中断
		{
			TLOG_ERROR(_T("PCI2312_InitDeviceInt Error..."));
			return false;
		}
		m_bPciIsReady = true;


	}
	catch(...)
	{
		return false;
	}
	return true;
}

void CRejector::TriggerRejectionSignal(int port,int delaycounts,int rejectSignal)
{
	if(rejectSignal == ENABLE_REJECT)
	{

		if (m_Encoder2ARTCard)
		{
			m_rejectData.startSite = PCI2312_GetDeviceIntCount(m_hPCI2312Device);
			m_rejectData.singDelayCounts = delaycounts;
			m_rejectData.step = INIT_SITE;
			//TLOG_NOTICE(_T("INIT SITE INT COUNT %d"),m_rejectData.startSite);
		}
		else
		{
			m_bDOSts[port] = rejectSignal;
			PCI2312_SetDeviceDO(m_hPCI2312Device,m_bDOSts);
			LARGE_INTEGER  bgn;  
			QueryPerformanceCounter(&bgn);  
			m_rejectData.bgn=bgn;
			last_bgn[port]=bgn; // last reject time
			m_rejectData.step = START_REJECT;
		}

		m_rejectData.port = port;
		if (m_signalTimestamp.is_not_full())
		{
			m_signalTimestamp.push_front(m_rejectData);
		}
		
		

	}
}

void CRejector::SetPortST(int port,BYTE st)
{
	m_bDOSts[port] = st;
	PCI2312_SetDeviceDO(m_hPCI2312Device,m_bDOSts);
}

BYTE CRejector::GetPortST(int port)
{
	PCI2312_GetDeviceDI(m_hPCI2312Device,m_bDISts);
	return m_bDISts[port];
}

UINT CRejector::Main()
{
	m_Reject_Delay = _wtoi( gConfigManager.GetBasicSetting(_T("REJECT_DURATION_TIME")).c_str());
	wstring st = gConfigManager.GetBasicSetting(_T("ENCODER_TO_ARTCARD"));
	if (!wcsicmp(st.c_str(),_T("YES")))
	{
		m_Encoder2ARTCard = true;
	}
	else
		m_Encoder2ARTCard = false; 


	if(!m_bPciIsReady)
	{
		TLOG_NOTICE(_T("PCI2312  Not Ready"));	
	}
	m_isExit = false;

	m_alarmSentry.Run();
	
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	double dFreq = (double)freq.QuadPart;

	RejectData rejectData;
	while(!m_isExit)
	{
		if(!m_signalTimestamp.is_not_empty())
		{
			if (m_isExit)
			{
				break;
			}
			Sleep(1);
			continue;
		}
		m_signalTimestamp.pop_back(&rejectData);
		switch(rejectData.step)
		{
			case INIT_SITE:
				{
					long nowsite  = PCI2312_GetDeviceIntCount(m_hPCI2312Device);
					//long nowsite=rejectData.startSite+510;
					if(abs(nowsite - rejectData.startSite )  >= rejectData.singDelayCounts)
					{
						m_bDOSts[rejectData.port] = ENABLE_REJECT;
						PCI2312_SetDeviceDO(m_hPCI2312Device,m_bDOSts);
						LARGE_INTEGER  bgn;  
						QueryPerformanceCounter(&bgn);  
						rejectData.bgn=bgn;
						last_bgn[rejectData.port]=bgn; // last reject time
						rejectData.step = START_REJECT;	
						//TLOG_NOTICE(_T("now  ENABLE_REJECT"));
					}
					if (m_signalTimestamp.is_not_full())
					{
						m_signalTimestamp.push_front(rejectData);
					}


					break;
				}
			case START_REJECT:
				{
					LARGE_INTEGER now;
					QueryPerformanceCounter(&now);

					if((now.QuadPart - rejectData.bgn.QuadPart) * 1000 / dFreq >= m_Reject_Delay)
					{
						//TLOG_NOTICE(_T(" now time %I64d  > reject delay time %d"),(now.QuadPart - rejectData.bgn.QuadPart) * 1000,m_Reject_Delay);
						if((last_bgn[rejectData.port].QuadPart!=rejectData.bgn.QuadPart)&&(last_bgn[rejectData.port].QuadPart-rejectData.bgn.QuadPart)* 1000 / dFreq <= m_Reject_Delay) //最后一次更新和当前的是同一个排除信号
						{
							//m_signalTimestamp.push_front(rejectData); //后面还有最新的排除信号。之前的这个信号可以不复位处理
							//TLOG_NOTICE(_T("continue"));
							continue;
						}
						else
						{
							m_bDOSts[rejectData.port]=DISABLE_REJECT;
							PCI2312_SetDeviceDO(m_hPCI2312Device,m_bDOSts);
							//TLOG_NOTICE(_T("now  disable reject"));
						}			
					}
					else
					{
						if (m_signalTimestamp.is_not_full())
						{
							m_signalTimestamp.push_front(rejectData);
						}
						//TLOG_NOTICE(_T(" wait reject end"));
					}
					break;
				}
			case END_REJECT:
				{
					break;
				}
		}
		
		
	}
	return 0;
}

void CRejector::Stop()
{	
	m_alarmSentry.Stop();
	Sleep(100);
	m_isExit = true;
}

