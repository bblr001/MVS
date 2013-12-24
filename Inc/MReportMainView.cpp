#pragma once
#include "stdafx.h"
#include "MData.h"
#include "MReportMainView.h"
#include "MReportCenter.h"
#include "Tools.h"
#include "AOIEditVer3.h"
#include "MCtrlCenter.h"

#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG

CMReportMainView::CMReportMainView()
	:m_dataToBeReported(MAX_DATA_REPOSITORY_SIZE)
{
	//m_isExit = false;
}

CMReportMainView::~CMReportMainView()
{
}

BOOL CMReportMainView::Init(CMReportCenter * pReportCent)
{
	m_pReportCenter = pReportCent;
	return TRUE;
}

UINT CMReportMainView::Main()
{
	wstring tmp = theApp.m_strStaionID;
	m_isExit = false;
	while(!m_isExit)
	{
		if(!m_dataToBeReported.is_not_empty())
		{
			if (m_isExit)
			{
				break;
			}
			Sleep(5);
			continue;
		}
		DoReport();
		Sleep(20);
	}
	return 0;
}

void CMReportMainView::Stop()
{
	m_isExit = true;
	CloseHandle(m_hThread);
	m_hThread = nullptr;
}

void CMReportMainView::DoReport()
{
	m_dataToBeReported.pop_back(&m_currentData);

#ifdef EOE_INSPECTION
	CMCtrlCenter::GetSingletonCtrlCenter()->UpdateMainWndImage(&m_currentData.m_Image);
#endif
}

void CMReportMainView::ReceiveData(CMData& data)
{
	if(m_dataToBeReported.is_not_full())
	{
		m_dataToBeReported.push_front(data);
	}
}


