// TLog.cpp: implementation of the TLog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TLog.h"
#include <direct.h>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TLog* TLog::s_pLog=NULL;

TLog::TLog()
{
	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0; //删除文件名，只获得路径
	m_sLogPath = szFilePath;
	m_sLogPath += "\\SLAC_LOG";
	if (!_wmkdir(m_sLogPath))
	{
		CString msg(_T("Can't creat m_sLogPath"));
		TLOG_WARNING(msg);
	}
	m_sLogPath += _T("\\")+CTime(time(NULL)).Format("%Y-%m-%d_%H-%M.log");	
}

TLog::~TLog()
{
}
void TLog::Log( LOG_TYPE eType, LPCTSTR szMsg, LPCTSTR szFile, int nLine )
{
	CString strLogType;
	CString strTime = CTime(time(NULL)).Format("(%Y-%m-%d %H:%M:%S)");
	CString strPos;
	strPos.Format(_T(" %s,%d "),szFile,nLine);
	
	switch(eType)
	{
	case LOG_ERROR:
		strLogType = _T("[ERROR]  : ");
		break;
	case LOG_WARNING:
		strLogType = _T("[WARNING]: ");
		break;
	case LOG_NOTICE:
		strLogType = _T("[NOTICE] : ");
	    break;
	case LOG_DEBUG:
		strLogType = _T("[DEBUG]  : ");
	    break;
	default:
		ASSERT(FALSE);
	    break;
	}
	
	Out(strLogType + szMsg + _T("\r\n  \t ") + strTime+strPos);
		
}

void TLog::Out( const wchar_t* szLog )
{
//	AfxMessageBox(szLog);
	FILE* fp = NULL;
	_wfopen_s(&fp, m_sLogPath, _T("a"));
	if (fp != NULL)
	{
		fputws(szLog,fp);
		fputws(_T("\r\n"),fp);
		fclose(fp);
	}
}

TLog* TLog::Get()
{
	if (s_pLog==NULL)
	{
		static TLog _tlog;
		s_pLog=&_tlog;
	}
	return s_pLog;
}
