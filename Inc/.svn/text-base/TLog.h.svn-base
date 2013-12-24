// TLog: 系统错误日志类.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TLOG_H__D92B8E60_4515_46B9_B6D3_5DB7566B8A5E__INCLUDED_)
#define AFX_TLOG_H__D92B8E60_4515_46B9_B6D3_5DB7566B8A5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define TLOG_ERROR   TLog::TLogMsg(TLog::LOG_ERROR,__FILE__,__LINE__)
#define TLOG_WARNING TLog::TLogMsg(TLog::LOG_WARNING,__FILE__,__LINE__)
#define TLOG_NOTICE  TLog::TLogMsg(TLog::LOG_NOTICE,__FILE__,__LINE__)
#define TLOG_RECORD  TLog::TLogMsg(TLog::LOG_NOTICE,__TIME__,0)
#ifdef _DEBUG
#define TLOG_DEBUG   TLog::TLogMsg(TLog::LOG_DEBUG,__FILE__,__LINE__)
#else
#define TLOG_DEBUG   __noop
#endif

///<summary>
/// 系统错误日志类
///</summary>
class TLog  
{
public:
	enum LOG_TYPE {LOG_ERROR,LOG_WARNING,LOG_NOTICE,LOG_DEBUG};
public:
	
	static TLog* Get();
	~TLog();

	void Log(LOG_TYPE eType,LPCTSTR szMsg,LPCTSTR szFile,int nLine);

protected:
	TLog();
	void Out(const wchar_t* szLog);
private:
	CString m_sLogPath;
	static TLog* s_pLog;

public:
	class TLogMsg
	{
	public:
		TLogMsg(LOG_TYPE logType,LPCSTR szFile,int nLine)
		{
			m_logType=logType;
			m_sFile=szFile;		
			m_nLine=nLine;
		}
		
		void _cdecl operator()(const wchar_t *pszFmt, ...)
		{		
			va_list ptr;
			va_start(ptr, pszFmt);
			m_sMsg.FormatV(pszFmt,ptr);			
			va_end(ptr);
			TLog::Get()->Log(m_logType,m_sMsg,m_sFile,m_nLine);
		}

		~TLogMsg(){};
			
	private:
		LOG_TYPE		m_logType;
		CString			m_sMsg;
		CString			m_sFile;
		int				m_nLine;
	};
};


#endif // !defined(AFX_TLOG_H__D92B8E60_4515_46B9_B6D3_5DB7566B8A5E__INCLUDED_)
