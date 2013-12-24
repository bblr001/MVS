
// SLACMVSN.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "SLACMVSN.h"
#include "MainFrm.h"
#include "LoginDlg.h"
#include "SLACMVSNDoc.h"
#include "SLACMVSNView.h"
#include "PanelManager.h"
#include "Splash.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSLACMVSNApp

BEGIN_MESSAGE_MAP(CSLACMVSNApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CSLACMVSNApp::OnAppAbout)
	// 基于文件的标准文档命令
	//ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	//ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


// CSLACMVSNApp 构造

CSLACMVSNApp::CSLACMVSNApp()
{
	m_bHiColorIcons = TRUE;
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CSLACMVSNApp 对象

CSLACMVSNApp theApp;
MvsConfigurationManager           gConfigManager;
std::vector<PROCESS_INFORMATION>  g_processInfo;
std::vector<HANDLE>               g_processHandle;

// CSLACMVSNApp 初始化

BOOL CSLACMVSNApp::InitInstance()
{
	CString strErrMsg;
	if(!CheckProcess(_T("AOIEDIT.EXE"),strErrMsg))
	{
		AfxMessageBox(strErrMsg);
		exit(-1);
	}
	CWinAppEx::InitInstance();

	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(0);  // 加载标准 INI 文件选项(包括 MRU)

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);
  
	CPanelManager::GetPanelManager().InitAllChannelProcess();
	Sleep(200);
	CPanelManager::GetPanelManager().CreateAllPanels();

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSLACMVSNDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CSLACMVSNView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	m_nCmdShow   =   SW_SHOWMAXIMIZED;   
	if   (!ProcessShellCommand(cmdInfo)) 
		return   FALSE; 
    
	Sleep(300);
    CPanelManager::GetPanelManager().InitAllPanels();
	Sleep(300);
	CPanelManager::GetPanelManager().StartAllPanels();

	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED); 
	m_pMainWnd->UpdateWindow(); 
	return TRUE;
}
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()
// 用于运行对话框的应用程序命令
void CSLACMVSNApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}
// CSLACMVSNApp 自定义加载/保存方法

void CSLACMVSNApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}
void CSLACMVSNApp::LoadCustomState()
{
}
void CSLACMVSNApp::SaveCustomState()
{
}
// CSLACMVSNApp 消息处理程序




