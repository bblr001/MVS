// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// ("Fluent UI")，该示例仅作为参考资料提供， 
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有 (C) Microsoft Corporation
// 保留所有权利。

// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "AOIEditVer3.h"
#include "HomeView.h"
#include "NextFormView.h"
#include "ProgramSelectorDlg.h"
#include "SaveProgram.h"
#include "MConfigCenter.h"
#include "MainFrm.h"
#include "MCtrlCenter.h"
#include "RibbonPagerCtrl.h"
#include <Excpt.h>
#include <assert.h>
#include "RibbonPage.h"

using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma data_seg("Shared")

#pragma data_seg()
#pragma  comment(linker,"/Section:Shared,RWS")
#define IDC_BTN_ID (IDC_BTN_OPER - BTN_MAX)
#define IDC_BTN_OPEN   IDC_BTN_ID
#define IDC_BTN_CFG    IDC_BTN_ID+1
#define IDC_BTN_RUN    IDC_BTN_ID+2
#define IDC_BTN_STOP   IDC_BTN_ID+3
#define IDC_BTN_PAUSE  IDC_BTN_ID+4
#define IDC_BTN_SHOT   IDC_BTN_ID+5
#define IDC_BTN_CONTI  IDC_BTN_ID+6
#define IDC_BTN_SAVE   IDC_BTN_ID+7
#define IDC_BTN_ZERO   IDC_BTN_ID+11
#define IDC_BTN_SAVESYS   IDC_BTN_ID+8
#define IDC_BTN_OPENCFG   IDC_BTN_ID+9
#define IDC_BTN_HOVER_OVER_FAILED_IMG IDC_BTN_ID+10
#define IDC_BTN_USER      IDC_BTN_OPER
#define ID_ENABLE(ID)    ((ID) - (IDC_BTN_ID))
// CMainFrame
#define CmdPara_Suffix   _T(" ")
IMPLEMENT_DYNAMIC(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_VIEW_CAPTION_BAR, &CMainFrame::OnViewCaptionBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CAPTION_BAR, &CMainFrame::OnUpdateViewCaptionBar)
	ON_UPDATE_COMMAND_UI_RANGE(IDC_BTN_ID,IDC_BTN_OPER,OnUpdateBtnCk)
	ON_CONTROL_RANGE(BN_CLICKED,IDC_BTN_ID,IDC_BTN_OPER,OnBtnClicked)
	ON_MESSAGE(AFX_WM_ON_CHANGE_RIBBON_CATEGORY, OnRibbonCategoryChanged)
	ON_REGISTERED_MESSAGE(AFX_WM_ON_CHANGE_RIBBON_CATEGORY, OnRibbonCategoryChanged)
	ON_MESSAGE(ON_WM_RIBBON_HEADER,OnRibbonHeaderDraw)
	ON_MESSAGE(WM_MI_TLSUPDATE_MESSAGE,OnReciveTLSUpdateMessage)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


CMainFrame::CMainFrame():
	m_user(OPERATOR),
	m_bInitPane(FALSE),
	m_wndAlgorithmParameter(ALGORITHM_PANE),
	m_wndLightParameter(LIGHT_PANE)
{
	for (int user = 0;user<GroupNum;++user)
	{
	    for(int iBTN = 0; iBTN < BTN_MAX; ++iBTN)
			m_btnEnable[user][iBTN] = false;
	    m_btnEnable[user][ID_ENABLE(IDC_BTN_USER)]    = true;
		m_btnEnable[user][ID_ENABLE(IDC_BTN_CONTI)]   = false;
		m_btnEnable[user][ID_ENABLE(IDC_BTN_OPENCFG)] = false;
		m_btnEnable[user][ID_ENABLE(IDC_BTN_OPEN)]    = true;
		m_btnEnable[user][ID_ENABLE(IDC_BTN_SAVESYS)] = false;
		m_btnEnable[m_user][ID_ENABLE(IDC_BTN_ZERO)]  = false;
		// second tab
		m_btnEnable[m_user][ID_ENABLE(IDC_BTN_HOVER_OVER_FAILED_IMG)] = false;
	}
   	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_OPEN)] = true;
}

CMainFrame::~CMainFrame()
{
}

void CMainFrame::SetUserMode(eUSER_GROUP group)
{
	m_btnEnable[group][ID_ENABLE(IDC_BTN_OPEN)]  = m_btnEnable[m_user][ID_ENABLE(IDC_BTN_OPEN)];
	m_btnEnable[group][ID_ENABLE(IDC_BTN_CFG)]   = m_btnEnable[m_user][ID_ENABLE(IDC_BTN_CFG)];
	m_btnEnable[group][ID_ENABLE(IDC_BTN_RUN)]   = m_btnEnable[m_user][ID_ENABLE(IDC_BTN_RUN)];
	m_btnEnable[group][ID_ENABLE(IDC_BTN_STOP)]  = m_btnEnable[m_user][ID_ENABLE(IDC_BTN_STOP)];
	m_btnEnable[group][ID_ENABLE(IDC_BTN_PAUSE)] = m_btnEnable[m_user][ID_ENABLE(IDC_BTN_PAUSE)];
	m_btnEnable[group][ID_ENABLE(IDC_BTN_ZERO)] = FALSE;//m_btnEnable[m_user][ID_ENABLE(IDC_BTN_ZERO)];

	if(OPERATOR != m_user)
	{
		m_btnEnable[group][ID_ENABLE(IDC_BTN_SHOT)] = m_btnEnable[m_user][ID_ENABLE(IDC_BTN_SHOT)];
		m_btnEnable[group][ID_ENABLE(IDC_BTN_CONTI)]= m_btnEnable[m_user][ID_ENABLE(IDC_BTN_CONTI)];
		m_btnEnable[group][ID_ENABLE(IDC_BTN_SAVE)] = m_btnEnable[m_user][ID_ENABLE(IDC_BTN_SAVE)];
	}
	else
	{
      m_btnEnable[group][ID_ENABLE(IDC_BTN_SHOT)] = false;
	  m_btnEnable[group][ID_ENABLE(IDC_BTN_SAVE)] = false;
	  m_wndTestListView.EnableWindow(FALSE);
	}
	m_user = group;
	auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();
	auto pCtrlCenter   = CMCtrlCenter::GetSingletonCtrlCenter();
	// Home view
	if (GetActiveView()->IsKindOf(RUNTIME_CLASS(CHomeFormView)))
	{
		m_wndTestListView.ShowPane(TRUE,TRUE,TRUE);
		bool bShowFiles = (SADMIN == m_user);
		m_wndFileView.ShowPane(bShowFiles,FALSE,bShowFiles);

		BOOL bActivate = (ADMIN == m_user || SADMIN == m_user);
#ifdef NDEBUG
		if(pConfigCenter->GetImgSource() == CAMERA_SOURCE && pCtrlCenter->IsLightCtrollerConnected())
		{
#endif
			m_wndLightParameter.ShowPane(bActivate, FALSE, bActivate);
#ifdef NDEBUG
		}
#endif
		m_wndAlgorithmParameter.ShowPane(bActivate,FALSE,bActivate);
	}
	else // Second Tab
	{
		m_wndTestListView.ShowPane(FALSE,FALSE,FALSE);
		m_wndFileView.ShowPane(FALSE,FALSE,FALSE);
		m_wndAlgorithmParameter.ShowPane(FALSE,FALSE,FALSE);
		m_wndLightParameter.ShowPane(FALSE,FALSE,FALSE);
	}

	bool bDebugFlag = CMConfigCenter::GetSingletonConfigCenter()->GetDebugModeFlag();
	int status = CMCtrlCenter::GetSingletonCtrlCenter()->GetSysStatus();
	if(m_user != OPERATOR && (bDebugFlag == true || status != RUNNING))
	{
		m_wndTestListView.EnableWindow(TRUE);
	}
	else
	{
		m_wndTestListView.EnableWindow(FALSE);
	}

	if(m_user  != OPERATOR && status == RUNNING)
	{
		m_btnEnable[m_user][ID_ENABLE(IDC_BTN_SHOT)] = true;
	}
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;
	CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
	// 设置用于绘制所有用户界面元素的视觉管理器
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));

    SwitchToForm(IDD_NEXTFORM);
	SwitchToForm(IDD_HOMEVIEW);

	m_wndRibbonBar.Create(this);
#ifdef _ENGLISH
	InitializeRibbon_English();
#else
	InitializeRibbon();
#endif

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}

	CString strTitlePane1;
	CString strTitlePane2;
#ifdef _ENGLISH
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1_ENG);
#else
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
#endif
	ASSERT(bNameValid);
	SYSTEMTIME tm;
	GetLocalTime(&tm);
	strTitlePane2.Format(_T("%d-%d-%d  %d:%d"),tm.wYear,tm.wMonth,tm.wDay,tm.wHour,tm.wMinute);
	ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);
	// 启用 Visual Studio 2005 样式停靠窗口行为
	CDockingManager::SetDockingMode(DT_SMART);
	// 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// 创建标题栏:
	if (!CreateCaptionBar())
	{
		TRACE0("未能创建标题栏\n");
		return -1;      // 未能创建
	}

	// 加载菜单项图像(不在任何标准工具栏上):
	CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);

	// 创建停靠窗口
	if (!CreateDockingWindows())
	{
		TRACE0("未能创建停靠窗口\n");
		return -1;
	}
	m_wndFileView.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndFileView);
	bool bShowFiles = (SADMIN == m_user);
	m_wndFileView.ShowPane(bShowFiles,FALSE,bShowFiles);

	m_wndTestListView.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndTestListView);

	m_wndAlgorithmParameter.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndAlgorithmParameter);

	m_wndLightParameter.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndLightParameter);


	eUSER_GROUP ug = OPERATOR;
	if(theApp.m_strUser == _T("ADMIN"))    ug = ADMIN;
	if(theApp.m_strUser == _T("ENGINEER")) ug = ENGINEER;
	if(theApp.m_strUser == _T("OPERATOR")) ug = OPERATOR;
	if(theApp.m_strUser == _T("SADMIN"))   ug = SADMIN;

	SetUserMode(ug);
	return 0;
}

LPARAM  CMainFrame::OnReciveTLSUpdateMessage(WPARAM wParam, LPARAM lParam)
{
	bool DebugModel = CMConfigCenter::GetSingletonConfigCenter()->GetDebugModeFlag();

	CMConfigCenter::GetSingletonConfigCenter()->SetDebugModeFlag(true); //设定单张取图模式.
	CMCtrlCenter::GetSingletonCtrlCenter()->UpdateSingleFrame();
	Sleep(30);
	string m_tlsfilename = "D:\\SLACTST\\" + CMConfigCenter::GetSingletonConfigCenter()->GetProgramName();
	m_tlsfilename+="\\";
	m_tlsfilename+=CMConfigCenter::GetSingletonConfigCenter()->GetTLSFileName();

	m_wndTestListView.InitTestList(m_tlsfilename);//重新加检测算子文件到测试清单中
	
	CMCtrlCenter::GetSingletonCtrlCenter()->UpdateTestItem();
	Sleep(30);
	CMConfigCenter::GetSingletonConfigCenter()->SetDebugModeFlag(DebugModel);
	CMCtrlCenter::GetSingletonCtrlCenter()->UpdateSingleFrame();
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE | WS_THICKFRAME |WS_POPUP| WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_SYSMENU;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	try
	{
		cs.lpszClass = AfxRegisterWndClass(0);
	}
	catch (CResourceException* e)
	{
	    e->ReportError();
		e->Delete();
	}
	return TRUE;
}

#ifdef _ENGLISH
void CMainFrame::InitializeRibbon_English()
{
	CString strTemp;
    BOOL bNameValid = strTemp.LoadString(IDS_RIBBON_FILE_ENG);
	ASSERT(bNameValid);

	// 加载面板图像:
	m_PanelImages.SetImageSize(CSize(32, 32));
	m_PanelImages2.SetImageSize(CSize(16,16));
	m_PanelImages.Load(IDB_BUTTONS);
	m_PanelImages2.Load(IDB_BITMAP_PANEL);

	m_MainButton.SetText(_T("\nf"));
	m_MainButton.SetToolTipText(strTemp);
	m_wndRibbonBar.SetApplicationButton(&m_MainButton, CSize (55, 55));
	CMFCRibbonMainPanel* pMainPanel = m_wndRibbonBar.AddMainCategory(strTemp, IDB_FILESMALL, IDB_FILELARGE);

	bNameValid = strTemp.LoadString(IDS_RIBBON_HOME_ENG);
	ASSERT(bNameValid);
	m_pHomeCategory = m_wndRibbonBar.AddCategory(strTemp, IDB_OPERSMALL, IDB_OPERLARGE);
	
	bNameValid = strTemp.LoadString(IDS_RIBBON_OPER_ENG);
	ASSERT(bNameValid);
    CMFCRibbonPanel *pPaneOper = m_pHomeCategory->AddPanel(strTemp,m_PanelImages.ExtractIcon(28));
	
	bNameValid = strTemp.LoadString(IDS_OPER_OPEN_ENG);
	ASSERT(bNameValid);
	pBtnOPEN = new CMFCRibbonButton(IDC_BTN_OPEN,strTemp,0,0);
	pPaneOper->Add(pBtnOPEN);
	pPaneOper->AddSeparator();

	bNameValid = strTemp.LoadString(IDS_BTN_SAVESYS_ENG);
	ASSERT(bNameValid);
	pBtnSaveSYS= new CMFCRibbonButton(IDC_BTN_SAVESYS,strTemp,0,1);
	pPaneOper->Add(pBtnSaveSYS);
	pPaneOper->AddSeparator();

	bNameValid = strTemp.LoadString(IDS_OPER_CFG_ENG);
	ASSERT(bNameValid);
	pBtnCFG = new CMFCRibbonButton(IDC_BTN_CFG,strTemp,0,2);
	pPaneOper->Add(pBtnCFG);
	pPaneOper->AddSeparator();

	bNameValid = strTemp.LoadString(IDS_OPER_RUN_ENG);
	ASSERT(bNameValid);
	pBtnRUN = new CMFCRibbonButton(IDC_BTN_RUN,strTemp,0,3);
	pPaneOper->Add(pBtnRUN);
	pPaneOper->AddSeparator();

	bNameValid = strTemp.LoadString(IDS_OPER_STOP_ENG);
	ASSERT(bNameValid);
	pBtnSTOP = new CMFCRibbonButton(IDC_BTN_STOP,strTemp,0,4);
	pPaneOper->Add(pBtnSTOP);
	pPaneOper->AddSeparator();

	bNameValid = strTemp.LoadString(IDS_OPER_PAUSE_ENG);
	ASSERT(bNameValid);
	pBtnPAUSE = new CMFCRibbonButton(IDC_BTN_PAUSE,strTemp,0,5);
	pPaneOper->Add(pBtnPAUSE);

	bNameValid = strTemp.LoadString(IDS_RIBBON_DISP_ENG);
	ASSERT(bNameValid);
	CMFCRibbonPanel * pPaneDisp = m_pHomeCategory->AddPanel(strTemp);

	bNameValid = strTemp.LoadString(IDS_DISP_SHOT_ENG);
	ASSERT(bNameValid);
	pBtnSHOT = new CMFCRibbonButton(IDC_BTN_SHOT,strTemp,0,7);
	pPaneDisp->Add(pBtnSHOT);
	pPaneDisp->AddSeparator();

	bNameValid = strTemp.LoadString(IDS_DISP_CONTIN_ENG);
	ASSERT(bNameValid);
	pBtnCONTIN = new CMFCRibbonButton(IDC_BTN_CONTI,strTemp,0,6);
	pPaneDisp->Add(pBtnCONTIN);
	pPaneDisp->AddSeparator();

	bNameValid = strTemp.LoadString(IDS_DISP_SAVE_ENG);
	ASSERT(bNameValid);
	pBtnSAVE = new CMFCRibbonButton(IDC_BTN_SAVE,strTemp,0,1);
	pPaneDisp->Add(pBtnSAVE);
    pPaneDisp->AddSeparator();

	bNameValid = strTemp.LoadString(IDS_RIBBON_HEXT_ENG);
	ASSERT(bNameValid);
	m_pFilterCategory = m_wndRibbonBar.AddCategory(strTemp, IDB_OPERSMALL, IDB_OPERLARGE);
	
	bNameValid = strTemp.LoadString(IDS_LOGO);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelView = m_pFilterCategory->AddPanel(strTemp, m_PanelImages.ExtractIcon (28));
	m_pPanelHistData= m_pFilterCategory->AddPanel(strTemp, m_PanelImages.ExtractIcon (28));

	bNameValid = strTemp.LoadString(IDS_BTN_ERR_IMG_ENG);
	ASSERT(bNameValid);
	pBtnContinueGrab = new CMFCRibbonButton(IDC_BTN_HOVER_OVER_FAILED_IMG,strTemp,0,9);
	m_pPanelHistData->Add(pBtnContinueGrab);
	m_pPanelHistData->AddSeparator();

	bNameValid = strTemp.LoadString(IDS_BTN_OPENCFG_ENG);
	ASSERT(bNameValid);
	pBtnOpenCfg = new CMFCRibbonButton(IDC_BTN_OPENCFG,strTemp,0,10);
	m_pPanelHistData->Add(pBtnOpenCfg);
	
	bNameValid = strTemp.LoadString(IDS_USER_ENG);
	ASSERT(bNameValid);
	m_wndRibbonBar.AddToTabs(m_RibbonLbUser = new CMFCRibbonLabel(strTemp));
	m_wndRibbonBar.AddToTabs(new CMFCRibbonButton(IDC_BTN_USER, _T("\na"), m_PanelImages2.ExtractIcon (0)));
}

#else

void CMainFrame::InitializeRibbon()
{
	CString strTemp;
	BOOL bNameValid = strTemp.LoadString(IDS_RIBBON_FILE);
	ASSERT(bNameValid);
	// 加载面板图像:
	m_PanelImages.SetImageSize(CSize(32, 32));
	m_PanelImages2.SetImageSize(CSize(16,16));
	m_PanelImages.Load(IDB_BUTTONS);
	m_PanelImages2.Load(IDB_BITMAP_PANEL);

	m_MainButton.SetText(_T("\nf"));
	m_MainButton.SetToolTipText(strTemp);
	m_wndRibbonBar.SetApplicationButton(&m_MainButton, CSize (55, 55));
	CMFCRibbonMainPanel* pMainPanel = m_wndRibbonBar.AddMainCategory(strTemp, IDB_FILESMALL, IDB_FILELARGE);

	bNameValid = strTemp.LoadString(IDS_RIBBON_HOME);
	ASSERT(bNameValid);
	m_pHomeCategory = m_wndRibbonBar.AddCategory(strTemp, IDB_OPERSMALL, IDB_OPERLARGE);

	bNameValid = strTemp.LoadString(IDS_RIBBON_OPER);
	ASSERT(bNameValid);
    CMFCRibbonPanel *pPaneOper = m_pHomeCategory->AddPanel(strTemp,m_PanelImages.ExtractIcon(28));

	bNameValid = strTemp.LoadString(IDS_OPER_OPEN);
	ASSERT(bNameValid);
	pBtnOPEN = new CMFCRibbonButton(IDC_BTN_OPEN,strTemp,0,0);
	pPaneOper->Add(pBtnOPEN);
	pPaneOper->AddSeparator();

	bNameValid = strTemp.LoadString(IDS_BTN_SAVESYS);
	ASSERT(bNameValid);
	pBtnSaveSYS= new CMFCRibbonButton(IDC_BTN_SAVESYS,strTemp,0,1);
	pPaneOper->Add(pBtnSaveSYS);
	pPaneOper->AddSeparator();

	bNameValid = strTemp.LoadString(IDS_OPER_CFG);
	ASSERT(bNameValid);
	pBtnCFG = new CMFCRibbonButton(IDC_BTN_CFG,strTemp,0,2);
	pPaneOper->Add(pBtnCFG);
	pPaneOper->AddSeparator();

	bNameValid = strTemp.LoadString(IDS_OPER_RUN);
	ASSERT(bNameValid);
	pBtnRUN = new CMFCRibbonButton(IDC_BTN_RUN,strTemp,0,3);
	pPaneOper->Add(pBtnRUN);

	pPaneOper->AddSeparator();

	bNameValid = strTemp.LoadString(IDS_OPER_STOP);
	ASSERT(bNameValid);
	pBtnSTOP = new CMFCRibbonButton(IDC_BTN_STOP,strTemp,0,4);
	pPaneOper->Add(pBtnSTOP);

	pPaneOper->AddSeparator();
	bNameValid = strTemp.LoadString(IDS_OPER_PAUSE);

	ASSERT(bNameValid);
	pBtnPAUSE = new CMFCRibbonButton(IDC_BTN_PAUSE,strTemp,0,5);
	pPaneOper->Add(pBtnPAUSE);

	bNameValid = strTemp.LoadString(IDS_RIBBON_DISP);
	ASSERT(bNameValid);
	CMFCRibbonPanel * pPaneDisp = m_pHomeCategory->AddPanel(strTemp);

	bNameValid = strTemp.LoadString(IDS_DISP_SHOT);
	ASSERT(bNameValid);
	pBtnSHOT = new CMFCRibbonButton(IDC_BTN_SHOT,strTemp,0,7);
	pPaneDisp->Add(pBtnSHOT);
	pPaneDisp->AddSeparator();

	bNameValid = strTemp.LoadString(IDS_DISP_CONTIN);
	ASSERT(bNameValid);
	pBtnCONTIN = new CMFCRibbonButton(IDC_BTN_CONTI,strTemp,0,6);
	pPaneDisp->Add(pBtnCONTIN);
	pPaneDisp->AddSeparator();

	bNameValid = strTemp.LoadString(IDS_DISP_SAVE);
	ASSERT(bNameValid);
	pBtnSAVE = new CMFCRibbonButton(IDC_BTN_SAVE,strTemp,0,1);
	pPaneDisp->Add(pBtnSAVE);
    pPaneDisp->AddSeparator();

	//bNameValid = strTemp.LoadString(IDS_DISP_ZERO);
	//ASSERT(bNameValid);
	//pBtnZERO = new CMFCRibbonButton(IDC_BTN_ZERO,strTemp,0,8);
	//pPaneDisp->Add(pBtnZERO);
	// 创建和添加图”面板:

	bNameValid = strTemp.LoadString(IDS_RIBBON_HEXT);
	ASSERT(bNameValid);
	m_pFilterCategory = m_wndRibbonBar.AddCategory(strTemp, IDB_OPERSMALL, IDB_OPERLARGE);

	bNameValid = strTemp.LoadString(IDS_LOGO);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelView = m_pFilterCategory->AddPanel(strTemp, m_PanelImages.ExtractIcon (28));
	m_pPanelHistData= m_pFilterCategory->AddPanel(strTemp, m_PanelImages.ExtractIcon (28));

	
	bNameValid = strTemp.LoadString(IDS_BTN_ERR_IMG);
	ASSERT(bNameValid);
	pBtnContinueGrab = new CMFCRibbonButton(IDC_BTN_HOVER_OVER_FAILED_IMG,strTemp,0,9);
	m_pPanelHistData->Add(pBtnContinueGrab);
	m_pPanelHistData->AddSeparator();

	bNameValid = strTemp.LoadString(IDS_BTN_OPENCFG);
	ASSERT(bNameValid);
	pBtnOpenCfg = new CMFCRibbonButton(IDC_BTN_OPENCFG,strTemp,0,10);
	m_pPanelHistData->Add(pBtnOpenCfg);

	bNameValid = strTemp.LoadString(IDS_USER);
	ASSERT(bNameValid);
	m_wndRibbonBar.AddToTabs(m_RibbonLbUser = new CMFCRibbonLabel(strTemp));
	m_wndRibbonBar.AddToTabs(new CMFCRibbonButton(IDC_BTN_USER, _T("\na"), m_PanelImages2.ExtractIcon (0)));
}
#endif


BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;

	// 创建测试清单视图
	CString strFileView;
#ifdef _ENGLISH
	bNameValid = strFileView.LoadString(IDS_FILE_VIEW_ENG);
#else
	bNameValid = strFileView.LoadString(IDS_FILE_VIEW);
#endif
	ASSERT(bNameValid);
	if (!m_wndFileView.Create(strFileView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_FILEVIEW, WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建“文件视图”窗口\n");
		return FALSE; // 未能创建
	}

	// 创建输出窗口
	CString strOutputWnd;
#ifdef _ENGLISH
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND_ENG);
#else
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
#endif
	ASSERT(bNameValid);
	if (!m_wndTestListView.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建输出窗口\n");
		return FALSE; // 未能创建
	}
	// 创建属性窗口
	CString strPropertiesWnd;
#ifdef _ENGLISH
	bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND_ENG);
#else
	bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
#endif
	ASSERT(bNameValid);
	if (!m_wndAlgorithmParameter.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建算子参数窗口\n");
		return FALSE; // 未能创建
	}

	// 光源控制器窗口
	CString strLightCtrlWndTitle;
#ifdef _ENGLISH
	bNameValid = strLightCtrlWndTitle.LoadString(IDS_LIGHT_CTRL_WND_TITLE_ENG);
#else
	bNameValid = strLightCtrlWndTitle.LoadString(IDS_LIGHT_CTRL_WND_TITLE);
#endif
	ASSERT(bNameValid);
	if(!m_wndLightParameter.Create(strLightCtrlWndTitle, this, CRect(0,0,100,100), TRUE,ID_VIEW_LIGHT_CTRL_WND,WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("创建光源参数窗口失败！\n");
		return FALSE;
	}


	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	m_bInitPane = TRUE;
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hFileViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_FILE_VIEW_HC : IDI_FILE_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndFileView.SetIcon(hFileViewIcon, FALSE);

	HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndTestListView.SetIcon(hOutputBarIcon, FALSE);

	HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndAlgorithmParameter.SetIcon(hPropertiesBarIcon, FALSE);

	HICON hLightWndBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndLightParameter.SetIcon(hLightWndBarIcon, FALSE);
}

BOOL CMainFrame::CreateCaptionBar()
{
	if (!m_wndCaptionBar.Create(WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, this, ID_VIEW_CAPTION_BAR, -1, TRUE))
	{
		TRACE0("未能创建标题栏\n");
		return FALSE;
	}

	BOOL bNameValid;

	CString strTemp, strTemp2;
#ifdef _ENGLISH
	bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON_ENG);
#else
	bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON);
#endif
	ASSERT(bNameValid);
	m_wndCaptionBar.SetButton(strTemp, ID_TOOLS_OPTIONS, CMFCCaptionBar::ALIGN_LEFT, FALSE);
#ifdef _ENGLISH
	bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON_TIP_ENG);
#else
	bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON_TIP);
#endif
	ASSERT(bNameValid);
	m_wndCaptionBar.SetButtonToolTip(strTemp);
	strTemp = theApp.GetString(EntryDate);
	m_wndCaptionBar.SetText(strTemp, CMFCCaptionBar::ALIGN_LEFT);
	m_wndCaptionBar.SetBitmap(IDB_INFO, RGB(255, 255, 255), FALSE, CMFCCaptionBar::ALIGN_LEFT);
#ifdef _ENGLISH
	bNameValid = strTemp.LoadString(IDS_CAPTION_IMAGE_TIP_ENG);
#else
	bNameValid = strTemp.LoadString(IDS_CAPTION_IMAGE_TIP);
#endif
	ASSERT(bNameValid);
#ifdef _ENGLISH
	bNameValid = strTemp.LoadString(IDS_CAPTION_IMAGE_TEXT_ENG);
#else
	bNameValid = strTemp.LoadString(IDS_CAPTION_IMAGE_TEXT);
#endif
	ASSERT(bNameValid);
	m_wndCaptionBar.SetImageToolTip(strTemp, strTemp2);
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

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

LPARAM CMainFrame::OnRibbonCategoryChanged(WPARAM wp, LPARAM lp)
{
	//当切换Ribbon时，收到此消息！
	CMFCRibbonBar *pRibbonBar = (CMFCRibbonBar*)lp;
	CMFCRibbonCategory* pActiveCategory = pRibbonBar->GetActiveCategory();
	if(m_pActiveCategory == pActiveCategory) return 0;
	m_pActiveCategory = pActiveCategory;
	if (m_pFilterCategory==pActiveCategory)
	{
		if (!(GetActiveView()->IsKindOf(RUNTIME_CLASS(CNextFormView))))
		{
			SwitchToForm(IDD_NEXTFORM);

			m_wndFileView.SaveState();
			m_wndFileView.ShowPane(FALSE,FALSE,FALSE);

			m_wndAlgorithmParameter.SaveState();
			m_wndAlgorithmParameter.SetAutoHideMode(FALSE,CBRS_ALIGN_RIGHT);
			m_wndAlgorithmParameter.ShowPane(FALSE,FALSE,FALSE);

			m_wndLightParameter.SaveState();
			m_wndLightParameter.ShowPane(FALSE,FALSE,FALSE);

			m_wndTestListView.SaveState();
			m_wndTestListView.ShowPane(FALSE,FALSE,FALSE);
			
		}
	}
	else if (m_pHomeCategory==pActiveCategory)
	{
		if (!(GetActiveView()->IsKindOf(RUNTIME_CLASS(CHomeFormView))))
		{
			SwitchToForm(IDD_HOMEVIEW);

			m_wndFileView.LoadState();
			bool bShowAlgoFiles = (SADMIN == m_user);
			m_wndFileView.ShowPane(bShowAlgoFiles,FALSE,bShowAlgoFiles);

			m_wndAlgorithmParameter.LoadState();
			bool bShow = (m_user == ADMIN || m_user == SADMIN);
			m_wndAlgorithmParameter.ShowPane(bShow,FALSE,bShow);

			bool bDebug = CMConfigCenter::GetSingletonConfigCenter()->GetDebugModeFlag();
			m_wndLightParameter.EnableWindow(bShow && bDebug);

			m_wndLightParameter.LoadState();
			bool bLightCtrlConnected   = CMCtrlCenter::GetSingletonCtrlCenter()->IsLightCtrollerConnected();
			bool blightWndShow = (bShow && bLightCtrlConnected);
			m_wndLightParameter.ShowPane(blightWndShow,FALSE,blightWndShow);
			m_wndLightParameter.EnableWindow(blightWndShow && bDebug);

			m_wndTestListView.LoadState();
			m_wndTestListView.ShowPane(TRUE,FALSE,TRUE);
			if(m_user == OPERATOR)
			{
				m_wndTestListView.EnableWindow(FALSE);
			}
		}
	}
	return 0;
}

void CMainFrame::OnUpdateBtnCk(CCmdUI* pCmdUI)
{
	UINT nID = ID_ENABLE(pCmdUI->m_nID);
	pCmdUI->Enable(m_btnEnable[m_user][nID]);
	if (m_bInitPane)
	{
		BOOL bActivate = (OPERATOR != m_user);
		m_wndTestListView.ShowPane(FALSE,FALSE,bActivate);
		bool bShowAlgoFiles = (SADMIN == m_user);
		m_wndFileView.ShowPane(bShowAlgoFiles,FALSE,bShowAlgoFiles);
		m_wndAlgorithmParameter.ShowPane(FALSE,FALSE,bActivate);
		m_wndLightParameter.ShowPane(FALSE,FALSE,bActivate);

		m_wndFileView.SetAutoHideMode(FALSE,CBRS_ALIGN_LEFT);
		m_wndFileView.EnableToolTips(FALSE);

		m_wndAlgorithmParameter.SetAutoHideMode(FALSE,CBRS_ALIGN_BOTTOM);
		m_wndLightParameter.SetAutoHideMode(FALSE,CBRS_ALIGN_RIGHT);
		m_wndTestListView.SetAutoHideMode(FALSE,CBRS_ALIGN_RIGHT); 

	    m_bInitPane = FALSE;
	}
}

void CMainFrame::OnBtnClicked(UINT nCmdID)
{
   //IDC_BTN_ID
	__try
	{
		bool bRet = false;
		switch (nCmdID)
		{
		case IDC_BTN_OPEN://open
			bRet = SelectProgramDlg();
			break;
		case IDC_BTN_CFG://configuration
			bRet = CfgDlg();
			break;
		case IDC_BTN_RUN://run
			bRet = SysRun();
			if(OPERATOR==m_user)
				break;
			break;
		case IDC_BTN_STOP://stop
			bRet = SysStop();
			break;
		case IDC_BTN_PAUSE://pause
			bRet = SysPause();
			break;
		case IDC_BTN_SHOT://shot
			if(OPERATOR==m_user&&!m_btnEnable[m_user][ID_ENABLE(IDC_BTN_RUN)])
				break;
			bRet = ShotGrab();
			break;
		case IDC_BTN_CONTI://continue
			if(OPERATOR==m_user&&!m_btnEnable[m_user][2])
				break;
			bRet = ContinueGrab();
			m_btnEnable[m_user][6] = !bRet;
			m_btnEnable[m_user][5] =  bRet;
			m_btnEnable[m_user][7] = !bRet;
			break;
		case IDC_BTN_SAVE://save
			if(OPERATOR==m_user&&!m_btnEnable[m_user][2])break;
			 Save();
			 break;
		case IDC_BTN_ZERO:
			//if(OPERATOR==m_user&&m_btnEnable[m_user][ID_ENABLE(IDC_BTN_RUN)])
				break;
			 //Zero();
			 break;
		case IDC_BTN_SAVESYS:
			 SaveSys();
			 break;
		case IDC_BTN_OPENCFG:
			 OpenHelpTool();
			 break;
		case IDC_BTN_USER:
			 bRet = UserDlg();
			 break;
		case IDC_BTN_HOVER_OVER_FAILED_IMG:
			HoverOverErrorImages();
			break;
		default:
			break;
		}
	}
	__except(ExpFltr(GetExceptionInformation()))
	{
	}
}

LONG CMainFrame::ExpFltr(LPEXCEPTION_POINTERS pep)
{
	TCHAR szBuf[300],*p;
	PEXCEPTION_RECORD pER = pep->ExceptionRecord;
	DWORD dwExceptionCode = pER->ExceptionCode;
	wsprintfW(szBuf,TEXT("Code = %x,Address = %p"),dwExceptionCode,pER->ExceptionAddress);
	p=_tcschr(szBuf,TEXT('0'));
	if(dwExceptionCode == EXCEPTION_ACCESS_VIOLATION)
	{
		wsprintfW(p,TEXT("\n---> Attempt to %s data at address %p ."),pER->ExceptionInformation[0]?TEXT("write"):TEXT("read"),
		pER->ExceptionInformation[1]);
	}
	MessageBox(szBuf,TEXT("Exception"),MB_OK|MB_ICONEXCLAMATION);
	return(EXCEPTION_EXECUTE_HANDLER);
}

bool CMainFrame::CfgDlg()
{
	CProgramSettingDlg ps;
	if (ps.DoModal() == IDCANCEL)
	{
		return false;
	}
	OnSize(SIZE_RESTORED,20,31);
	ps.DestroyWindow();
	SendMessage(WM_SIZE,NULL,NULL);

	if(!CMCtrlCenter::GetSingletonCtrlCenter()->Init())
	{
		m_btnEnable[m_user][ID_ENABLE(IDC_BTN_OPEN)] = true;
		m_btnEnable[m_user][ID_ENABLE(IDC_BTN_CFG)] = false;
		m_btnEnable[m_user][ID_ENABLE(IDC_BTN_RUN)] = false;
		m_btnEnable[m_user][ID_ENABLE(IDC_BTN_SAVESYS)] = false;
		m_btnEnable[m_user][ID_ENABLE(IDC_BTN_SAVE)] = false;
		m_btnEnable[m_user][ID_ENABLE(IDC_BTN_SHOT)] = false;
	}
	else
	{
		m_btnEnable[m_user][ID_ENABLE(IDC_BTN_OPEN)] = true;
		m_btnEnable[m_user][ID_ENABLE(IDC_BTN_CFG)] = true;
		m_btnEnable[m_user][ID_ENABLE(IDC_BTN_RUN)] = true;
		m_btnEnable[m_user][ID_ENABLE(IDC_BTN_SAVESYS)] = true;
	}

	// Add Light Parameter into 'Light Parameter Window'
	auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();
	auto pCtrlCenter   = CMCtrlCenter::GetSingletonCtrlCenter();
	bool bShowPane = false;
	if(pConfigCenter->GetImgSource() == CAMERA_SOURCE && pCtrlCenter->IsLightCtrollerConnected())
	{
		auto pLightInfos = pConfigCenter->GetLightCtrlInfosPtr();
		m_wndLightParameter.SetLightParameters(pLightInfos);
		if(m_user == ADMIN || m_user == SADMIN)
		{
			bShowPane = true;
		}
	}
	m_wndLightParameter.ShowPane(bShowPane, FALSE, bShowPane);

   InitForm();
   return true;
}

bool CMainFrame::SelectProgramDlg()
{
    bool bRet = true;
	CProgramSelectorDlg openPro;
	auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();
	auto pCtrlCenter = CMCtrlCenter::GetSingletonCtrlCenter();
	if (openPro.DoModal() ==IDOK)
	{
		string filename;
		filename = ws2s(pConfigCenter->GetTestProgramPath());
		filename += pConfigCenter->GetProgramName();
		filename +="\\";
		filename += pConfigCenter->GetTLSFileName();
		wstring name = s2ws(pConfigCenter->GetProgramName());
		CString strName = name.c_str();
		theApp.m_strProgramName = strName;
		theApp.UpdateTitle();
		//pCtrlCenter->Init();
		m_wndTestListView.InitTestList(filename);
		m_btnEnable[m_user][ID_ENABLE(IDC_BTN_OPEN)] = true;
		m_btnEnable[m_user][ID_ENABLE(IDC_BTN_RUN)] = true;
		m_btnEnable[m_user][ID_ENABLE(IDC_BTN_CFG)] = true;
		m_btnEnable[m_user][ID_ENABLE(IDC_BTN_SAVESYS)] = false;

		m_wndTestListView.ShowPane(TRUE, FALSE, TRUE);
		if(m_user == OPERATOR)
		{
			m_wndTestListView.EnableWindow(FALSE);
		}
#ifdef _DEBUG
		m_wndLightParameter.ShowPane(TRUE, FALSE, TRUE);
#endif
		pConfigCenter->SetProgramChangedFlag(true);
	}
	else
	{
	   bRet = false;
	}
	openPro.DestroyWindow();
	return bRet;
}

bool CMainFrame::UserDlg()
{
	CLoginDlg loginDlg;
	if (loginDlg.DoModal() !=IDOK)
	{
		loginDlg.DestroyWindow();
		return false;
	}
	loginDlg.DestroyWindow();
	auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();
	eUSER_GROUP group = pConfigCenter->GetUserGroup();
	SetUserMode(group);
	
	switch(group)
	{
	case OPERATOR:
		theApp.m_strUser = _T("OPERATOR");
		m_RibbonLbUser->SetText(_T("OPERATOR"));
		theApp.UpdateTitle();	
		m_btnEnable[m_user][ID_ENABLE(IDC_BTN_SHOT)] = false;
		m_btnEnable[m_user][ID_ENABLE(IDC_BTN_ZERO)] = false;
		break;
	case ENGINEER:
		theApp.m_strUser = _T("ENGINEER");
		m_RibbonLbUser->SetText(_T("ENGINEER"));
		theApp.UpdateTitle();

		
		break;
	case ADMIN:
		theApp.m_strUser = _T("ADMIN");
		m_RibbonLbUser->SetText(_T("ADMIN"));
		theApp.UpdateTitle();
		break;
	case SADMIN:
		theApp.m_strUser = _T("ADMIN");
		m_RibbonLbUser->SetText(_T("ADMIN"));
		theApp.UpdateTitle();
		break;
	default:
		break;
	}

	m_RibbonLbUser->Redraw();
	auto pCtrlCenter = CMCtrlCenter::GetSingletonCtrlCenter();
	if (pCtrlCenter->GetSysStatus() == RUNNING && pConfigCenter->GetDebugModeFlag()==false)
	{
		m_btnEnable[m_user][ID_ENABLE(IDC_BTN_SHOT)] = (OPERATOR != m_user);
		//m_btnEnable[m_user][ID_ENABLE(IDC_BTN_ZERO)] = (OPERATOR != m_user);
		m_btnEnable[m_user][ID_ENABLE(IDC_BTN_ZERO)] = FALSE;
	}
	
	return true;
}

void CMainFrame::OnClose()
{
	m_wndFileView.CloseWindow();
	if (CMCtrlCenter::GetSingletonCtrlCenter()->m_bSelfRunMode)
	{
		this->SysStop();
		CFrameWndEx::OnClose();
	}
	else
	{
		theApp.m_pMainWnd->ShowWindow(SW_HIDE);
	}
}

void CMainFrame::InitForm()
{
	CRect* rect = CMConfigCenter::GetSingletonConfigCenter()->GetUISize();
	m_pHomeView->SetScrollSizes(MM_TEXT,CSize(rect->Width(),rect->Height()));
}

bool CMainFrame::SysRun()
{
	CMConfigCenter::GetSingletonConfigCenter()->SetDebugModeFlag(false);

	int status = CMCtrlCenter::GetSingletonCtrlCenter()->GetSysStatus();
	if(status == STOPPED)
	{
		CMCtrlCenter::GetSingletonCtrlCenter()->Start();
	}
	if(status == PAUSED)
	{
		CMCtrlCenter::GetSingletonCtrlCenter()->Resume();
	}
	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_STOP)] = true;
	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_PAUSE)] = true;
	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_SAVESYS)] = false;

	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_SHOT)] = (OPERATOR != m_user);
	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_ZERO)] = FALSE;
	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_RUN)] = false;
	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_OPENCFG)] = false;

	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_CONTI)] = false;
	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_SAVE)] = false;

	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_CFG)] = false;
	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_OPEN)] = false;
	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_HOVER_OVER_FAILED_IMG)] = false;

	m_wndAlgorithmParameter.EnableEditTestName(FALSE);
	m_wndAlgorithmParameter.EnableWindow(FALSE);
	m_wndLightParameter.EnableWindow(TRUE);
	m_wndTestListView.EnableWindow(FALSE);

    return true;
}

bool CMainFrame::SysPause()
{	
	CMCtrlCenter::GetSingletonCtrlCenter()->Pause();
	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_SAVESYS)] = true;
	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_OPEN)] = false;
	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_RUN)] = true;
	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_STOP)] = true;
	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_PAUSE)] = false;
	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_SHOT)] = false;
	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_CONTI)] = false;
	m_wndAlgorithmParameter.EnableEditTestName(TRUE);
	m_wndAlgorithmParameter.EnableWindow(TRUE);
	m_wndLightParameter.EnableWindow(TRUE);
	if(m_user != OPERATOR)
	{
		m_wndTestListView.EnableWindow(TRUE);
	}
	return true;
}

bool CMainFrame::SysStop()
{
	auto pCtrlCenter = CMCtrlCenter::GetSingletonCtrlCenter();
	if(pCtrlCenter->GetSysStatus() == STOPPED)
	{
		return true;
	}
	pCtrlCenter->Stop();
	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_CONTI)] = false;
	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_SAVE)] = false;
	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_OPEN)] = true;
	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_PAUSE)] = false;
	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_SHOT)] = false;
	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_RUN)] = false;
	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_OPENCFG)] = false;
	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_STOP)] = false;
	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_ZERO)] = false;
	m_wndAlgorithmParameter.EnableWindow(TRUE);
	m_wndAlgorithmParameter.EnableEditTestName(TRUE);
	m_wndLightParameter.EnableWindow(TRUE);
	if(m_user != OPERATOR)
	{
		m_wndTestListView.EnableWindow(TRUE);
	}
	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_SAVESYS)] = false;
	return true;
}

bool CMainFrame::SaveSys()
{
	m_wndTestListView.SaveTestList();
	SaveProgram savePro;
	if (savePro.DoModal() ==IDOK)
	{
		CMCtrlCenter::GetSingletonCtrlCenter()->UpdateChannelSettings();
	}
	return true;
}

bool CMainFrame::Zero()
{
	 CMCtrlCenter::GetSingletonCtrlCenter()->SetTestRecordDef();
	 return true;
}

bool CMainFrame::Save()
{
	auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();
	if (!pConfigCenter -> GetDebugModeFlag())
	{
		return false;
	}
	CMData data = CMCtrlCenter::GetSingletonCtrlCenter()->GetFrameFromReport();
	if(CMConfigCenter::GetSingletonConfigCenter()->GetHasFrameFlag())
	{
		CFileDialog   saveImgDlg(FALSE,NULL, _T("image.tiff"),OFN_OVERWRITEPROMPT, _T("image file(*.tiff)|*.tiff| "));
		CString defPath;
		defPath.Format(_T("d:\\SLACTST\\%s\\"),(s2ws(CMConfigCenter::GetSingletonConfigCenter()->GetProgramName())).c_str());
		saveImgDlg.m_ofn.lpstrInitialDir=defPath;
		if(saveImgDlg.DoModal() == IDOK) 
		{
			wstring tmp(saveImgDlg.GetPathName());
			string fileName = ws2s(tmp);
			write_image(data.m_Image,"tiff", 0, fileName.c_str());
		}
		saveImgDlg.DestroyWindow();
	}
	else
	{
		AfxMessageBox(_T("GetHasFrameFlag=FALAS"));
	}
	return true;
}

bool CMainFrame::ShotGrab()
{
	if(CMConfigCenter::GetSingletonConfigCenter()->GetUserGroup()==OPERATOR)
	{
		return false;
	}
	CMConfigCenter::GetSingletonConfigCenter()->SetDebugModeFlag(true);
	CMCtrlCenter::GetSingletonCtrlCenter()->UpdateSingleFrame();

    m_btnEnable[m_user][ID_ENABLE(IDC_BTN_SHOT)]  = false;
	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_CONTI)] = true;
	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_SAVE)]  = true;
	
	m_wndAlgorithmParameter.EnableEditTestName(TRUE);
	m_wndAlgorithmParameter.EnableWindow(TRUE);
	m_wndLightParameter.EnableWindow(TRUE);
	m_wndTestListView.EnableWindow(TRUE);

	return true;
}

bool CMainFrame::ContinueGrab()
{
	if(CMConfigCenter::GetSingletonConfigCenter()->GetUserGroup()==OPERATOR)
	{
		return false;
	}
	CMConfigCenter::GetSingletonConfigCenter()->SetDebugModeFlag(false);
	CMCtrlCenter::GetSingletonCtrlCenter()->UpdateSingleFrame();

	m_wndAlgorithmParameter.EnableEditTestName(FALSE);
	m_wndAlgorithmParameter.EnableWindow(FALSE);
	m_wndLightParameter.EnableWindow(TRUE);
	m_wndTestListView.EnableWindow(FALSE);
	return true;
}

void CMainFrame::GetCmdParameter(CString& strCmd)
{
	string m_programname = CMConfigCenter::GetSingletonConfigCenter()->GetProgramName();
	string m_imagefilename = "D:\\SLACTST\\"+m_programname;
	m_imagefilename+="\\tmp.tiff";

	string m_tlsfilename = "D:\\SLACTST\\" + m_programname +"\\";
	m_tlsfilename+=CMConfigCenter::GetSingletonConfigCenter()->GetTLSFileName();
	CString imagePath(m_imagefilename.c_str());
	CString tlsPath(m_tlsfilename.c_str());
	CString processID;
	processID.Format(_T("%d"),GetCurrentProcessId());
    strCmd=_T("AOIEDITHelp.exe");
	strCmd +=CmdPara_Suffix;
	strCmd +=imagePath;
	strCmd +=CmdPara_Suffix;
	strCmd +=tlsPath;
	strCmd +=CmdPara_Suffix;
	strCmd +=processID;

	CString user;
	strCmd +=CmdPara_Suffix;
	if(CMConfigCenter::GetSingletonConfigCenter()->GetUserGroup()==SADMIN)
	{
		user = _T("sadmin");
		strCmd +=user;
	}
	else
	{
		user=_T("normal");
		strCmd +=user;
	}
}

bool CMainFrame::OpenHelpTool()
{
	bool bRet = true;
	CString Cmd;
	int id = GetProcessIdFromName(_T("AOIEDITHelp.exe"));
	if (0 == id)
	{
		GetCmdParameter(Cmd);
		PROCESS_INFORMATION m_pi;
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
		si.dwFlags=STARTF_USESHOWWINDOW|STARTF_USESTDHANDLES|STARTF_FORCEONFEEDBACK;
		si.wShowWindow=SW_NORMAL;  
		si.cbReserved2=0;
		si.lpReserved2=NULL;
		si.hStdInput=stdin;
		si.hStdOutput=stdout;    
		si.hStdError=stderr;
		BOOL fRet=CreateProcess(NULL,Cmd.GetBuffer(),NULL,NULL,TRUE,NULL ,NULL,NULL,&si,&(m_pi));
		if(fRet)   
		{   
			WaitForInputIdle(m_pi.hProcess,0);   
			CloseHandle(m_pi.hThread);   m_pi.hThread = NULL; 
			CloseHandle(m_pi.hProcess);  m_pi.hProcess = NULL;
		}   
		else   
		{   
			AfxMessageBox(_T("打开调试窗口失败！"));  
			bRet = false;
		}  
	}
	Sleep(200);
	m_pNextView->OpenHelpTool();
	return bRet;
}

void CMainFrame::SwitchToForm(UINT nForm)
{
	CView * pOldFrmVw = static_cast<CView*>(GetActiveView());
	CView * pNewFrmVw = static_cast<CView*>(GetDlgItem(nForm));
	if (NULL == pNewFrmVw)
	{
		size_t sz = 0;
		if (IDD_HOMEVIEW == nForm)
		{
			pNewFrmVw = (CView*)(m_pHomeView = new CHomeFormView);	
			sz = sizeof(CHomeFormView);
		}
		else if ( IDD_NEXTFORM == nForm)
		{
			pNewFrmVw = (CView*)(m_pNextView =new CNextFormView);
		    sz = sizeof(CNextFormView);
		}
		pNewFrmVw->Create(NULL,NULL,0L,CFrameWnd::rectDefault,this,nForm);
	}
	if(0!=pOldFrmVw)
	{
		pOldFrmVw->ShowWindow(SW_HIDE);
		int ID = AFX_IDW_PANE_FIRST;
		if (pOldFrmVw->GetRuntimeClass() == RUNTIME_CLASS(CHomeFormView))
		{
			ID = IDD_HOMEVIEW;
		}
		else if (pOldFrmVw->GetRuntimeClass() == RUNTIME_CLASS(CNextFormView))
		{
			ID = IDD_NEXTFORM;
		}
		pOldFrmVw->SetDlgCtrlID(ID);
	}
	SetActiveView(pNewFrmVw);
	pNewFrmVw->ShowWindow(SW_SHOWDEFAULT);
	pNewFrmVw->SetDlgCtrlID(AFX_IDW_PANE_FIRST);
	RecalcLayout();
}

void CMainFrame::RunInAutoMode()
{
	auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();

 	if(!pConfigCenter->LoadProgramConfig(theApp.m_strProgramName.GetBuffer()))
 	{
 		return;
 	}
 	if (pConfigCenter->GetTriggerMode())
 	{
 		pConfigCenter->SetTriggerMode(true);
 	}
 	else
 	{
 		pConfigCenter->SetTriggerMode(false);
 	}
 	if (pConfigCenter->GetRejectMode())
 	{
 		pConfigCenter->SetRejectMode(true);
 		pConfigCenter->SetRejectPort(pConfigCenter->GetRejectPort());
 	}
 	else
 	{
 		pConfigCenter->SetRejectMode(false);
 	}
 	string TestProgramPath;
 	TestProgramPath = ws2s(pConfigCenter->GetTestProgramPath());
 	TestProgramPath += pConfigCenter->GetProgramName();
 	TestProgramPath +="\\";
 	string filename = TestProgramPath + pConfigCenter->GetTLSFileName();
 	if (_access(filename.c_str(),0))
 	{
 		CString msg;
 		msg.Format(_T("TLSFileName File No find %s"),s2ws(filename).c_str());
 		AfxMessageBox(msg);
 		return;
 	}

 	m_wndTestListView.InitTestList(filename);
 	EMDATA_SOURCE source = pConfigCenter->GetImgSource();
// 	if(IMG_FILES == source)
// 	{
// 		pConfigCenter->SetReciveFilesTimeInterval(500); // TODO: why??
// 	}
	
	for (int user = 0;user<GroupNum;++user)
	{
	    m_btnEnable[user][ID_ENABLE(IDC_BTN_USER)] = false;
	}

 	OnMainCtrlInit();
}

void CMainFrame::OnMainCtrlInit()
{
	m_btnEnable[m_user][0] = false;
	m_btnEnable[m_user][1] = false;
	m_btnEnable[m_user][2] = true;
	m_btnEnable[m_user][3] = false;
	m_btnEnable[m_user][4] = false;

	m_btnEnable[m_user][5] = false;
	m_btnEnable[m_user][6] = false;
	m_btnEnable[m_user][7] = false;

	if(!CMCtrlCenter::GetSingletonCtrlCenter()->Init())
	{
		m_btnEnable[m_user][0] = true;
		m_btnEnable[m_user][1] = false;
		m_btnEnable[m_user][2] = false;
		m_btnEnable[m_user][3] = false;
		m_btnEnable[m_user][4] = false;

		m_btnEnable[m_user][5] = false;
		m_btnEnable[m_user][6] = false;
		m_btnEnable[m_user][7] = false;
	}
}

LRESULT CMainFrame::OnRibbonHeaderDraw(WPARAM wp,LPARAM lp)
{
	return 0;
}

void CMainFrame::OnViewCaptionBar()
{
	m_wndCaptionBar.ShowWindow(m_wndCaptionBar.IsVisible() ? SW_HIDE : SW_SHOW);
	RecalcLayout(FALSE);
}

void CMainFrame::OnUpdateViewCaptionBar(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndCaptionBar.IsVisible());
}

bool CMainFrame::OneShotGrabErrPic()
{
	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_HOVER_OVER_FAILED_IMG)] = true;
	if(CMConfigCenter::GetSingletonConfigCenter()->GetUserGroup()!=OPERATOR)
	{
		m_btnEnable[m_user][ID_ENABLE(IDC_BTN_OPENCFG)] = true;
	}
	//CMConfigCenter::GetSingletonConfigCenter()->SetErrorImgPausedFlag(true);
	return true;
}

bool CMainFrame::HoverOverErrorImages()
{
	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_HOVER_OVER_FAILED_IMG)] = false;
	m_btnEnable[m_user][ID_ENABLE(IDC_BTN_OPENCFG)] = false;
	CMConfigCenter::GetSingletonConfigCenter()->SetErrorImgPausedFlag(false);
	return true;
}
