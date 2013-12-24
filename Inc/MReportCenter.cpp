#pragma once
#include "StdAfx.h"
#include "MCtrlCenter.h"
#include "MConfigCenter.h"
#include "MReportCenter.h"

#pragma warning(disable:4005)

#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG

CMReportCenter::CMReportCenter( void )
{
	m_isExit           = false;
	m_bIsSaveFailImage = false;
	m_bHasFrame = false;
}

CMReportCenter::~CMReportCenter(void)
{
	m_vReport.clear();
}

void CMReportCenter::Pause()
{
	if(m_bHasMainUI)
	{
		m_reportMainView.Pause();
	}
	m_reportFile.Pause();
	m_reportView.Pause();
	::SuspendThread(m_hThread);
}

void CMReportCenter::Stop()
{
	::WaitForSingleObject(CMCtrlCenter::GetSingletonCtrlCenter()->m_filterCenter.m_hThread, INFINITE);
	if(m_bHasMainUI)
	{
		m_reportMainView.Stop();
	}
	m_reportFile.Stop();
	m_reportView.Stop();
	m_vReport.clear();
	m_isExit = true;
	CloseHandle(m_hThread);
	m_hThread = NULL;
}

void CMReportCenter::OnClickWarning()
{
	m_reportView.OnClickWarning();
}
BOOL CMReportCenter::Init()
{
	m_vReport.clear();
	m_vReport.push_back((IMReport*)&m_reportFile);
	m_bHasMainUI = (CMCtrlCenter::GetSingletonCtrlCenter()->m_bSelfRunMode == false);
	if(m_bHasMainUI)
	{
		m_vReport.push_back((IMReport*)&m_reportMainView);
	}
	m_vReport.push_back((IMReport*)&m_reportView);
	m_bIsSaveFailImage = CMConfigCenter::GetSingletonConfigCenter()->GetSaveFailImageStatus();

	if (!m_reportView.Init(this))
	{
		AfxMessageBox(_T("Initialize Report View Failed!"));
		return FALSE;
	}
	if(m_bHasMainUI)
	{
		if (!m_reportMainView.Init(this))
		{
			AfxMessageBox(_T("Initialize Main Report View Failed!"));
			return FALSE;
		}
	}
	if (!m_reportFile.Init(this))
	{
		AfxMessageBox(_T("Initialize Report File Failed!"));
		return FALSE;
	}
	return TRUE;
}

UINT CMReportCenter::Main()
{
	m_isExit = false;
	auto pCtrlCenter   = CMCtrlCenter::GetSingletonCtrlCenter();
	auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();
	CMData retData;
	while (!m_isExit)
	{
		if(!pCtrlCenter->m_f_buffer_r.is_not_empty())
		{
			if (m_isExit)
			{
				break;
			}
			Sleep(1);
			continue;
		}
 		pCtrlCenter->m_f_buffer_r.pop_back(&retData);
		count_seconds(&retData.m_displayStartTime);

		std::for_each(m_vReport.begin(), m_vReport.end(), [&](IMReport* reportPtr)
		{
			if(reportPtr != nullptr)
			{
				reportPtr->ReceiveData(retData);
			}
		});

		if(pConfigCenter->GetHasFrameFlag() == false)
		{
			pConfigCenter->SetHasFrameFlag(true);
		}

		m_currentData = retData;
		m_bHasFrame=true;
	}
	return 0;
}

void CMReportCenter::Start()
{
	m_reportView.Run();
	if(CMCtrlCenter::GetSingletonCtrlCenter()->m_bSelfRunMode == false)
	{
		m_reportMainView.Run();
	}
	m_reportFile.Run();
	this->Run();
}
