

#include "stdafx.h"
#include "afxwinappex.h"
#include "AOIEditVer3.h"
#include "MainFrm.h"
#include <memory>
#include <atlconv.h>
#include <string>
#include <boost\algorithm\string.hpp>
#include "MCtrlCenter.h"


using namespace std;
using namespace boost;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAOIEditVer3App
BEGIN_MESSAGE_MAP(CAOIEditVer3App, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CAOIEditVer3App::OnAppAbout)
END_MESSAGE_MAP()

CAOIEditVer3App::CAOIEditVer3App()
{
	m_bHiColorIcons = TRUE;
 	m_strProgramName = _T("");
 	m_strUser        = _T("OPERATOR");
 	m_strStaionID    = _T("NULL");
}

CAOIEditVer3App::~CAOIEditVer3App()
{
	::DeleteCriticalSection(&g_critical_section);
}

CAOIEditVer3App theApp;
//ConfigurationManager gConfigManager;
CRITICAL_SECTION g_critical_section;


BOOL CAOIEditVer3App::InitInstance()
{
	CWinAppEx::InitInstance();
	InitializeCriticalSection(&g_critical_section);

	SetRegistryKey(_T("Suzhou SLAC Pricision Equipment Co.,Ltd. Vision Inspection Version 1.0.3"));

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_clrText = RGB(61,0,0);
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL, RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	TCHAR exeFullPath[MAX_PATH]; // MAX_PATH
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);

	CString cmd = GetCommandLine();
	cmd.TrimRight();
	if(cmd.GetLength() > 0 && cmd != exeFullPath)
	{
		USES_CONVERSION;
		std::string strCmd = T2CA(cmd);
		std::vector<string> vRslt;
		boost::split(vRslt, strCmd, boost::is_any_of("$"),boost::token_compress_on);
		if(vRslt.size() >= 4)
		{
			m_strStaionID    = A2CT(vRslt[1].c_str());
			m_strProgramName = A2CT(vRslt[2].c_str());
			m_strUser        = A2CT(vRslt[3].c_str());
		}
	}
     
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	pFrame->LoadFrame(IDR_MAINFRAME,WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,NULL);

 	pFrame->ShowWindow(SW_MAXIMIZE);
 	pFrame->UpdateWindow();

	UpdateTitle();
	pFrame->UpdateWindow();
	if (m_strProgramName != "")
	{
		CMainFrame* pMainFrm = (CMainFrame*)::AfxGetMainWnd(); 
		CMCtrlCenter::GetSingletonCtrlCenter()->m_bSelfRunMode = false;
		Sleep(500);
		m_pMainWnd->ShowWindow(SW_HIDE);
		pMainFrm->RunInAutoMode();		
		m_pMainWnd->UpdateWindow();
	}
	//Check the capacity of the disk.
	ULARGE_INTEGER nFreeBytesAvailable;
	ULARGE_INTEGER nTotalNumberOfBytes;
	ULARGE_INTEGER nTotalNumberOfFreeBytes;
	if (GetDiskFreeSpaceEx(_T("D:"),&nFreeBytesAvailable,&nTotalNumberOfBytes, &nTotalNumberOfFreeBytes))
	{
		if(double((nTotalNumberOfFreeBytes.QuadPart)/1024/1024/1024)<(2)) //小于2G
		{
#ifdef _ENGLISH
			AfxMessageBox(_T("The space of D driver is not enough, please delete the image file from program folder."));
#else
			AfxMessageBox(_T("D:盘剩余磁盘空间不足. 请删除相应程式资料夹下的错误图片以释放空间。"));
#endif
			exit(1);
		}
	}
	HANDLE hd = GetCurrentProcess();
	SetPriorityClass(hd,REALTIME_PRIORITY_CLASS);
	CloseHandle(hd);
	return TRUE;
}

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

protected:
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_Ver;
	CButton m_OK;
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	BOOL bNameValid;
	CString strName;
#ifdef _ENGLISH
	bNameValid = strName.LoadString(IDS_ABOUT_VESRION_ENG);
#else
	bNameValid = strName.LoadString(IDS_ABOUT_VESRION);
#endif
	ASSERT(bNameValid);
	m_Ver.SetWindowText(strName);
#ifdef _ENGLISH
	bNameValid = strName.LoadString(IDS_ABOUT_TITLE_ENG);
#else
	bNameValid = strName.LoadString(IDS_ABOUT_TITLE);
#endif
	ASSERT(bNameValid);
	SetWindowText(strName);
#ifdef _ENGLISH
	m_OK.SetWindowText(_T("Confirm"));
#else
	m_OK.SetWindowText(_T("确定"));
#endif
	return TRUE;
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VERSION_TEXT, m_Ver);
	DDX_Control(pDX, IDOK, m_OK);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

void CAOIEditVer3App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

void CAOIEditVer3App::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
#ifdef _ENGLISH
	bNameValid = strName.LoadString(IDS_EDIT_MENU_ENG);
#else
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
#endif
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
#ifdef _ENGLISH
	bNameValid = strName.LoadString(IDS_EXPLORER_ENG);
#else
	bNameValid = strName.LoadString(IDS_EXPLORER);
#endif
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CAOIEditVer3App::LoadCustomState()
{
	m_dateLastRun = GetString(EntryDate);
	SYSTEMTIME tm;
	GetLocalTime(&tm);
#ifdef _ENGLISH
		m_dateCurrRun.Format(_T(" Last startup time: %d-%d-%d %d:%d:%d 。"),tm.wYear,tm.wMonth,tm.wDay,tm.wHour,tm.wMinute,tm.wSecond);
#else
	    m_dateCurrRun.Format(_T(" 上次启动时间: %d-%d-%d %d:%d:%d 。"),tm.wYear,tm.wMonth,tm.wDay,tm.wHour,tm.wMinute,tm.wSecond);
#endif
}

void CAOIEditVer3App::SaveCustomState()
{
	WriteString(EntryDate,m_dateCurrRun);
}

void CAOIEditVer3App::UpdateTitle()
{
	CString title;

#ifdef _ENGLISH
	title.Format(_T("SLAC SMVS -- Program:%s / Channel:%s / UserGroup:%s"),m_strProgramName, m_strStaionID, m_strUser);
#else
	title.Format(_T("SLAC SMVS -- 程式名:%s / 通道:%s / 用户组:%s"),m_strProgramName, m_strStaionID, m_strUser);
#endif
	CMainFrame* pFrame = (CMainFrame*)m_pMainWnd;
	pFrame->SetTitle(title);
	
}

