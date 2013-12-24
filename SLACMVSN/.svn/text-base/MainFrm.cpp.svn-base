
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "SLACMVSN.h"
#include "MainFrm.h"
#include "SLACMVSNView.h"
#include "..\inc\Tools.h"
#include "MyPanel.h"
#include "PanelManager.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_WM_CLOSE()
	
		ON_MESSAGE(WM_MI_ENTER_MESSAGE,EnterStation)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// 启用 Visual Studio 2005 样式停靠窗口行为
	CDockingManager::SetDockingMode(DT_SMART);
	// 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	long style = GetWindowLong(m_hWnd,GWL_STYLE);   
	style     &= ~(WS_CAPTION);  
	SetWindowLong(m_hWnd,GWL_STYLE,style);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		pSysMenu->DeleteMenu(SC_CLOSE,MF_BYCOMMAND);
	}
	ShowWindow(SW_HIDE);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	cs.hMenu=NULL;
	//cs.cx = 1280;
	//cs.cy = 1024;
	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* 扫描菜单*/);
	pDlgCust->Create();
}

HBRUSH CMainFrame::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFrameWndEx::OnCtlColor(pDC,pWnd,nCtlColor);
	return hbr;
}
LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

void CMainFrame::OnClose()
{
	CPanelManager::GetPanelManager().CloseAllPanels();

	//CMI_DataConfig::GetDataConfig().Close();
	
	
	Sleep(500);
	if(!g_processHandle.empty())
	{
		size_t sz = g_processHandle.size();
		::WaitForMultipleObjects(sz, &g_processHandle[0], TRUE, 300);
	}
	CFrameWndEx::OnClose();
}

void CMainFrame::UpdateUserInfo(CString username, eUSER_GROUP userGroup)
{
	CSLACMVSNView   *pView=(CSLACMVSNView *)GetActiveView(); 
	pView->UpdateUserInfo(username, userGroup);
}

LRESULT CMainFrame::EnterStation(WPARAM wPanel,LPARAM Mylparamp)
{
	CHANNEL_SETTING* wMI =  (CHANNEL_SETTING*)wPanel;
	PROCESS_INFORMATION *pi = &(wMI->m_pi);
	HANDLE  hProcess = OpenProcess(PROCESS_QUERY_INFORMATION , FALSE, pi->dwProcessId);
	if(hProcess == NULL)
	{
		int ret = MessageBox(_T("This Channel is closed.Create channel again."),_T("Channel Error"),MB_YESNO);
		if (ret == IDYES)
		{
			wchar_t m_sCurrentPath[MAX_PATH];
			GetCurrentDirectory(MAX_PATH,m_sCurrentPath);
			CString ApplicationName;
			ApplicationName=m_sCurrentPath;
			ApplicationName+=_T("\\AOIEDIT.EXE");
			STARTUPINFO si;
			ZeroMemory(&si,sizeof(si)); 
			si.cb   =   sizeof   STARTUPINFO; 
			si.lpReserved=NULL;    
			si.lpDesktop=NULL;    
			si.lpTitle=NULL;    
			si.dwX=0;    
			si.dwY=0;    
			si.dwXSize=0;    
			si.dwYSize=0;    
			si.dwXCountChars=500;    
			si.dwYCountChars=500;    
			si.dwFlags=STARTF_USESHOWWINDOW|STARTF_USESTDHANDLES;    
			si.wShowWindow=SW_HIDE;    
			si.cbReserved2=0;    
			si.lpReserved2=NULL;    
			si.hStdInput=stdin;    
			si.hStdOutput=stdout;    
			si.hStdError=stderr;  

			CString cmd;
			eUSER_GROUP ug = CPanelManager::GetPanelManager().GetUserGroup();
			wstring strUserGroup = CPanelManager::GetPanelManager().MapUserGroup2String(ug);

			cmd.Format(_T("$%s$%s$%s$"),wMI->szStationID.c_str(),wMI->szProgramName.c_str(),strUserGroup.c_str());
			BOOL fRet = CreateProcess(ApplicationName,cmd.GetBuffer(),NULL,NULL,TRUE,NULL ,NULL,NULL,&si,&(wMI->m_pi));
			if(fRet==false)   
			{   
				AfxMessageBox(_T("Create process failed"));   
			}   
			else   
			{   
				WaitForInputIdle(wMI->m_pi.hProcess,0);   
				CloseHandle(wMI->m_pi.hThread);   
				CloseHandle(wMI->m_pi.hProcess);   
			}  
			Sleep(100);
			CMyPanel* panel = CPanelManager::GetPanelManager().GetPanel(wMI->szStationID);
			panel->ClickedOpenChanel(wMI->m_pi.dwProcessId);
			EnumThreadWindows(pi->dwThreadId,EnumThreadWndProc,MI_SHOW);
		}
		return 0;
	}
	EnumThreadWindows(pi->dwThreadId,EnumThreadWndProc,MI_SHOW);
	::CloseHandle(hProcess);
	return 0;
}
