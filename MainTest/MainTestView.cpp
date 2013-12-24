
// MainTestView.cpp : CMainTestView 类的实现
//

#include "stdafx.h"
#include "MainTest.h"

#include "MainTestDoc.h"
#include "MainTestView.h"
#include "MainFrm.h"
#include "ChangeMode.h"
#include "PropSheet.h"
#include "SettingPropSheetFrame.h"
#include "MI_DataConfig.h"
#include "MI_PanelCenter.h"
#include "MI_ControlCenter.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainTestView

IMPLEMENT_DYNCREATE(CMainTestView, CFormView)

BEGIN_MESSAGE_MAP(CMainTestView, CFormView)
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID_FULL_SCREEN_MODE, OnFullScreenMode)
	ON_UPDATE_COMMAND_UI(ID_FULL_SCREEN_MODE, OnUpdateFullScreenMode)

	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_SWITCH_MODEL, &CMainTestView::OnSwitchModel)
	ON_COMMAND(ID_SETTING, &CMainTestView::OnSetting)
	ON_UPDATE_COMMAND_UI(ID_SETTING, &CMainTestView::OnUpdateSetting)
END_MESSAGE_MAP()

// CMainTestView 构造/析构

CMainTestView::CMainTestView()
	: CFormView(CMainTestView::IDD)
{
	// TODO: 在此处添加构造代码
	isFull = false;
    m_pSettingPropFrame = NULL;
	ContextMenu= new CMenu();
	if(!ContextMenu->LoadMenu(IDR_MENU_VIEW)){
		AfxMessageBox(_T("Fail to create context menu"));
	}
}

CMainTestView::~CMainTestView()
{
}

void CMainTestView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CMainTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
			
}

void CMainTestView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	Sleep(1000);
	OnFullScreenMode();

}
void CMainTestView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CMainTestView 诊断

#ifdef _DEBUG
void CMainTestView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMainTestView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMainTestDoc* CMainTestView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMainTestDoc)));
	return (CMainTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CMainTestView 消息处理程序
void CMainTestView::OnClose()
{
	if (isFull)
	{
		OnFullScreenMode();
	}
	
	CFormView::OnClose();
}
HBRUSH CMainTestView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
 	CRect rect; 
 	//CWnd*   hWndChild = ::GetWindow(m_hWnd,   GW_CHILD); 
 	CWnd*   hWndChild = GetWindow(GW_CHILD); 
 	while(hWndChild) 
 	{
 		if(hWndChild->GetDlgCtrlID()==331 && nCtlColor== CTLCOLOR_STATIC) 
 		{ 
 			COLORREF backColor = RGB(236, 233, 216);//这个颜色为Formview默认的面板颜色		
 			hWndChild->GetClientRect(&rect);
 			pDC->FillSolidRect(&rect,backColor);
 			pDC->SetBkColor(backColor);
 			return CreateSolidBrush(backColor);//创建背景刷子
 		}
 		hWndChild   =   hWndChild-> GetNextWindow(); 
 	} 
	
	return hbr;
}

void CMainTestView::OnFullScreenMode() 
{

	// TODO: Add your command handler code here
	if(!isFull){
		//Zaznaczam, 縠 przechodze do trybu pe硁oekranowego
		isFull=true;
		CMI_PanelCenter::GetPanelCenter().UpdatePanel(FALSE);
		CMI_ControlCenter::GetInstance().SetIsFullScreen(TRUE);
		// zapamietuje adres okna, w ktorym byl umieszczony widok (pewnie ramka)
		saveParent=this->GetParent();
		// przypisuje widokowi nowego rodzica - czyli desktop
		this->SetParent(GetDesktopWindow());
		CRect rect;// chodzi o wymiary desktop'u-pulpitu
		GetDesktopWindow()->GetWindowRect(&rect);
		// Ustawiam okno na pulpicie
		this->SetWindowPos(&wndTopMost,rect.left,rect.top,rect.right,rect.bottom,SWP_SHOWWINDOW);
		saveFullParent=this->GetParent();


	}else
	{
		CChangeMode mod;
		mod.DoModal();
		wstring Gruop= CMI_DataConfig::GetDataConfig().GetUserGroupName();

 		if (!(_stricmp("OPERATOR",ws2s(Gruop).c_str())))
 		{
			;
			msg.Format(_T("请输入工程师或管理员帐号密码. 退出全屏. 当前帐号是 %s"),Gruop.c_str());
			AfxMessageBox(msg);		
			this->SetParent(GetDesktopWindow());
			CRect rect;
			GetDesktopWindow()->GetWindowRect(&rect);
			this->SetWindowPos(&wndTopMost,rect.left,rect.top,rect.right,rect.bottom,SWP_SHOWWINDOW);
 			return;
 		}
		// wylaczenie trybu pelnoekranowego
		isFull=false;
		CMI_PanelCenter::GetPanelCenter().UpdatePanel(TRUE);
		CMI_ControlCenter::GetInstance().SetIsFullScreen(FALSE);
		// przypisuje widokowi starego rodzica
		this->SetParent( saveParent);
		// pobieram wskaznik do ramki
		// aby ja uaktualnic - zeby okno ktore traci status pelnoekranowy
		// zostalo w niej w odpowiednim miejscu ustawione
		// Robie tak dlatego, 縠 nie wiem jak zapamietac ustawienia
		// okna w ramce - a ulegaja one zmianie gdy wlaczam pelny ekran
		// Sposob prosty - Wyswietlenie jakiegokolwiek ControlBaru
		// bez zmiany jego ustawien - to wiaze sie z wstawienie mojego okna
		// tak jak bylo poprzednio !! ??

		//trza include CMainFrame zrobic
// 		CMainFrame *frm=(CMainFrame *)AfxGetMainWnd();
// 		//frm->ShowControlBars();
// 		frm->RecalcLayout();
// 		frm->UpdateWindow();

		::SetWindowPos(GetSafeHwnd(),HWND_NOTOPMOST,20,20,744,540,SWP_SHOWWINDOW);
		//this->SetWindowPos(&wndBottom,20,20,1044,740,SWP_SHOWWINDOW);
		((CMainFrame *)AfxGetMainWnd())->RecalcLayout();


		//frm->ShowControlBar(&frm->m_wndToolBar, frm->m_wndToolBar.IsVisible(), FALSE);
	}

	//isFull =!isFull;
}

void CMainTestView::OnUpdateFullScreenMode(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(isFull);
}
void CMainTestView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值


	// TODO: Add your message handler code here and/or call default
	ClientToScreen(&point);
	if(ContextMenu->GetSubMenu(0)){
		CMenu *pSubMenu= ContextMenu->GetSubMenu(0);

		if(isFull){
			pSubMenu->CheckMenuItem(ID_FULL_SCREEN_MODE,MF_CHECKED );
			//pSubMenu->EnableMenuItem(ID_CHANGE_TEXT_COLOR,MF_GRAYED);
			//pSubMenu->EnableMenuItem(ID_CHANGE_BACKGROUND_COLOR,MF_GRAYED);
		}
		else{
			pSubMenu->CheckMenuItem(ID_FULL_SCREEN_MODE,MF_UNCHECKED );
			//pSubMenu->EnableMenuItem(ID_CHANGE_TEXT_COLOR,MF_ENABLED);
			//pSubMenu->EnableMenuItem(ID_CHANGE_BACKGROUND_COLOR,MF_ENABLED);
		}
		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
			point.x,point.y,this);
	}

	CFormView::OnRButtonDown(nFlags, point);
}
void CMainTestView::OnSwitchModel()
{
	// TODO: 在此添加命令处理程序代码
	CChangeMode mod;
 	if (mod.DoModal()==IDOK)
 	{
// 		this->SetParent( saveParent);
// 		((CMainFrame *)AfxGetMainWnd())->RecalcLayout();
		if (isFull)
		{
			OnFullScreenMode();
		}
 	}
 	else
 	{
// 		this->SetParent( saveFullParent);
// 		((CMainFrame *)AfxGetMainWnd())->RecalcLayout();
 		if (isFull)
 		{
			this->SetParent(GetDesktopWindow());
			CRect rect;// chodzi o wymiary desktop'u-pulpitu
			GetDesktopWindow()->GetWindowRect(&rect);
			this->SetWindowPos(&wndTopMost,rect.left,rect.top,rect.right,rect.bottom,SWP_SHOWWINDOW);
 		}
	
 	}
	mod.DestroyWindow();
	
	//::RedrawWindow(NULL,NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

}
void CMainTestView::OnSetting()
{
	// TODO: 在此添加命令处理程序代码
	/*m_pModalSettingPropSheet = new CModalSettingPropSheet;
	if (m_pModalSettingPropSheet->DoModal() == IDOK)
	{
		GetDocument()->SetModifiedFlag();
		GetDocument()->UpdateAllViews(NULL);
	}
	delete m_pModalSettingPropSheet;
	m_pModalSettingPropSheet = NULL;*/
	// If mini frame does not already exist, create a new one.
	// Otherwise, unhide it
	CChangeMode dlLogin;
	dlLogin.DoModal();

	wstring Gruop= CMI_DataConfig::GetDataConfig().GetUserGroupName();

	if ((_stricmp("ADMINISTRATOR",ws2s(Gruop).c_str())))
	{
		AfxMessageBox(_T("请输入管理员帐号进行用户管理"));

		return;
	}
	

	if (m_pSettingPropFrame == NULL)
	{
		m_pSettingPropFrame = new CSettingPropSheetFrame;
		CRect rect(0, 0, 0, 0);
		CString strTitle;
		strTitle.LoadString(IDS_OBJECT_PROPERTIES);
		if (!m_pSettingPropFrame->Create(NULL, strTitle,
			WS_POPUP | WS_CAPTION | WS_SYSMENU, rect, this))
		{
			m_pSettingPropFrame = NULL;
			return;
		}
		m_pSettingPropFrame->CenterWindow();
	}
	// Before unhiding the modeless property sheet, update its
	// settings to reflect the currently selected shape.
	/*CShapesView* pView =
		STATIC_DOWNCAST(CShapesView, MDIGetActive()->GetActiveView());
	ASSERT_VALID(pView);
	if (pView->m_pShapeSelected != NULL)
	{
	   m_pShapePropFrame->m_pModelessShapePropSheet->
		   SetSheetPropsFromShape(pView->m_pShapeSelected);
	}*/
	if (m_pSettingPropFrame != NULL && !m_pSettingPropFrame->IsWindowVisible())
		m_pSettingPropFrame->ShowWindow(SW_SHOW);
}
void CMainTestView::OnUpdateSetting(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(m_pSettingPropFrame != NULL)
	pCmdUI->Enable(!m_pSettingPropFrame->IsWindowVisible());
}