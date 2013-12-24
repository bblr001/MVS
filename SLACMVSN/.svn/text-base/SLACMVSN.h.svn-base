#pragma once

#ifndef __AFXWIN_H__
	#error "Please include "stdafx.h" before includeing this file to generate PCH file"
#endif

#include "resource.h"      
#include <vector>
#include "ConfigurationManager.h"

using namespace std;
//

#define WM_MOUSEONBUTTON   WM_USER+100 
#define WM_MOUSEOFFBUTTON  WM_USER+101
const int bkgndR = 200;
const int bkgndG = 220;
const int bkgndB = 250;
const int MAX_CHANNEL_COUNT = 8;

class CSLACMVSNApp : public CWinAppEx
{
public:
	CSLACMVSNApp();

public:
	virtual BOOL InitInstance();
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();

	DECLARE_MESSAGE_MAP()
};

extern CSLACMVSNApp theApp;
extern MvsConfigurationManager           gConfigManager;
extern std::vector<PROCESS_INFORMATION>  g_processInfo;
extern std::vector<HANDLE>               g_processHandle;
