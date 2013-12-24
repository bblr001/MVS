#pragma once
#include "stdafx.h"
#include "MData.h"
#include "MReportFile.h"
#include "MReportCenter.h"
#include "MConfigCenter.h"
#include "MainFrm.h"
#include <direct.h>
#include "TLog.h"
#include "Tools.h"
#include <atlconv.h>
#include <algorithm>
using namespace std;

#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG


CMReportFile::CMReportFile()
	:m_dataToBeReported(MAX_DATA_REPOSITORY_SIZE)
{
	m_isExit = false;
	m_bSaveFailedImage = false;
	m_ErrorFileCount = 0;
	m_nPassFileCount = 0;
}

CMReportFile::~CMReportFile()
{
}

BOOL CMReportFile::Init(CMReportCenter * pReportCent)
{
	
	return TRUE;
}

UINT CMReportFile::Main()
{
	auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();
	if(pConfigCenter == nullptr) return FALSE;

	m_LocalLogPath = pConfigCenter->GetTestProgramPath();
	m_LocalLogPath+=_T("\\");
	m_LocalLogPath+=s2ws(pConfigCenter->GetProgramName());

	m_LocalLogPath+=_T("\\SLAC_LOG");

	m_bSaveFailedImage = pConfigCenter->GetSaveFailImageStatus();
	m_bSavePassImage = pConfigCenter->GetSavePassImageStatus();

	if (!_wmkdir(m_LocalLogPath.c_str()))
	{
		TLOG_WARNING(_T("Can't creat m_LocalLogPath"));
	}


	m_CurrentLocalLogPath = m_LocalLogPath;
	m_CurrentLocalLogPath += _T("\\")+CTime(time(NULL)).Format("%Y-%m-%d_%H-%M-%S");	
	_wmkdir(m_CurrentLocalLogPath.c_str());
	
	m_LogPassImagePath = m_CurrentLocalLogPath + _T("\\PASS\\");
	_wmkdir(m_LogPassImagePath.c_str());
	m_LogFailImagePath = m_CurrentLocalLogPath + _T("\\FAIL\\");
	_wmkdir(m_LogFailImagePath.c_str());

	m_LogFileName=m_CurrentLocalLogPath;	
	m_LogFileName+= _T("\\testlog.dat");

	_wunlink(m_LogFileName.c_str());
	
	m_ErrorFileCount = 0;
	m_nPassFileCount = 0;
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
		Sleep(10);
		DoReport();
	}
	return 0;
}

void CMReportFile::Stop()
{
	m_isExit = true;
	CloseHandle(m_hThread);
	m_hThread = NULL;
}

void CMReportFile::DoReport()
{
	m_dataToBeReported.pop_back(&m_currentData);

	if (m_currentData.m_isFail)
	{
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ShowErrorLogPic(&m_currentData);
	}

	USES_CONVERSION;
	wstring fileName;
	TCHAR temp[256];
	if (m_currentData.m_isFail)
	{		
		if (m_bSaveFailedImage)
		{
			fileName = m_LogFailImagePath;
			swprintf_s(temp, _T("%s%d%s"), m_LogFailImagePath.c_str(),m_ErrorFileCount%1000,_T(".tiff"));
 			string ff(T2CA(temp));
			if (!m_currentData.m_isDebug)
			{
				write_image(m_currentData.m_Image,"tiff", 0, ff.c_str());
			}
 			m_ErrorFileCount++;
		}	
	}
	else
	{
		if (m_bSavePassImage && m_nPassFileCount < 512)
		{
			swprintf_s(temp, _T("%s%d%s"), m_LogPassImagePath.c_str(),m_currentData.m_reciveCount,_T(".tiff"));
			string ff(T2CA(temp));
			write_image(m_currentData.m_Image,"tiff", 0, ff.c_str());
			m_nPassFileCount++;
		}
	}
	m_currentData.m_isFail = false;
}

void CMReportFile::ReceiveData(CMData& data)
{
	if(m_dataToBeReported.is_not_full())
	{
		m_dataToBeReported.push_front(data);
	}
}


