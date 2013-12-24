
// AOIEDITHelp.h : AOIEDITHelp 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号

#include <string>
// CAOIEDITHelpApp:
// 有关此类的实现，请参阅 AOIEDITHelp.cpp
//
#define IDB_FIRST       IDB_QUESTION
#define BMINDEX(x)      (x - IDB_FIRST)
class CMainFrame;
class CAOIEDITHelpDoc;
class CAOIEDITHelpApp : public CWinApp
{
public:
	CAOIEDITHelpApp();

    CImageList    m_images ;
	void LoadBitmaps(BOOL fFree);
	void FreeBitmaps();
public:
	virtual BOOL InitInstance();
    virtual int ExitInstance();
	afx_msg void OnAppAbout();
	afx_msg void OnMyFileOpen();
	DECLARE_MESSAGE_MAP()
public:
	std::wstring m_processID;
	std::wstring m_TLSFileName;
	std::string  m_szTLSFileName;
	std::wstring m_ImageFileName;
	std::wstring m_ProgramName;
	std::wstring m_user;
	CString m_file_path;
    CMainFrame* m_pFrmWnd;
	CAOIEDITHelpDoc * m_currentDocument;
};

extern CAOIEDITHelpApp theApp;
