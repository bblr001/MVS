
// AOIEditVer3.h : AOIEditVer3 
//
#pragma once

#ifndef __AFXWIN_H__
	#error "Include this file before including stdafx.h to generate PCH file"
#endif
#include "resource.h"       
//
#include "ConfigurationManager.h"

const CString EntryDate = _T("LastDateRun");
class CAOIEditVer3App : public CWinAppEx
{
public:
	CAOIEditVer3App();
	~CAOIEditVer3App();
public:
	virtual BOOL InitInstance();
	CString m_strStaionID;
	CString m_strProgramName;
	CString m_strUser;
    CString m_dateLastRun;
	CString m_dateCurrRun;
public:
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	void UpdateTitle();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CAOIEditVer3App theApp;
//extern ConfigurationManager gConfigManager;
extern CRITICAL_SECTION g_critical_section;