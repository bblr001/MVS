
// SLACMVSNView.cpp : CSLACMVSNView 类的实现
//

#include "stdafx.h"
#include "SLACMVSN.h"
#include "SLACMVSNDoc.h"
#include "SLACMVSNView.h"
#include "MyPanel.h"
#include "SettingPropSheetFrame.h"
#include "resource.h"
#include "PanelManager.h"
#include "MainFrm.h"
#include "LoginDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CSLACMVSNView

IMPLEMENT_DYNCREATE(CSLACMVSNView, CFormView)

BEGIN_MESSAGE_MAP(CSLACMVSNView, CFormView)
	//{{AFX_MSG_MAP(CSLACMVSNView)
	//ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CSLACMVSNView::OnTcnSelchangeTabCtrol)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	//ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_EXIT, &CSLACMVSNView::OnBnClickedExit)
	ON_BN_CLICKED(IDC_USER, &CSLACMVSNView::OnBnClickedUser)
	ON_BN_CLICKED(IDC_BUT_LOGIN, &CSLACMVSNView::OnBnClickedLogin)
	ON_BN_CLICKED(IDC_BUT_LOGOUT, &CSLACMVSNView::OnBnClickedButLogout)
END_MESSAGE_MAP()

// CSLACMVSNView 构造/析构

CSLACMVSNView::CSLACMVSNView()
	: CFormView(CSLACMVSNView::IDD)
{
	cfont.CreateFont( 
		32,                                                 //   nHeight 
		0,                                                   //   nWidth 
		0,                                                   //   nEscapement 
		0,                                                   //   nOrientation 
		FW_HEAVY,                                   //   nWeight 
		FALSE,                                           //   bItalic 
		FALSE,                                           //   bUnderline 
		0,                                                   //   cStrikeOut 
		ANSI_CHARSET,                             //   nCharSet 
		OUT_DEFAULT_PRECIS,                 //   nOutPrecision 
		CLIP_DEFAULT_PRECIS,               //   nClipPrecision 
		DEFAULT_QUALITY,                       //   nQuality 
		DEFAULT_PITCH   |   FF_SWISS,     //   nPitchAndFamily 
		_T("Arial "));
	timefont.CreateFont( 
		23,                                                 //   nHeight 
		0,                                                   //   nWidth 
		0,                                                   //   nEscapement 
		0,                                                   //   nOrientation 
		FW_BOLD,                                   //   nWeight 
		FALSE,                                           //   bItalic 
		FALSE,                                           //   bUnderline 
		0,                                                   //   cStrikeOut 
		ANSI_CHARSET,                             //   nCharSet 
		OUT_DEFAULT_PRECIS,                 //   nOutPrecision 
		CLIP_DEFAULT_PRECIS,               //   nClipPrecision 
		DEFAULT_QUALITY,                       //   nQuality 
		DEFAULT_PITCH   |   FF_SWISS,     //   nPitchAndFamily 
		_T("Arial "));
		m_pSettingPropFrame = NULL;
}

void CSLACMVSNView::OnDraw(CDC* pDC)
{
	CFormView::OnDraw(pDC);
	CBitmap   Bitmap; 
	Bitmap.LoadBitmap(IDB_BITMAP_LOG); 
	CDC   dcComp; 
	dcComp.CreateCompatibleDC(pDC); 
	dcComp.SelectObject(&Bitmap); 
	BITMAP   Bmlinfo; 
	Bitmap.GetBitmap(&Bmlinfo); 
	pDC-> BitBlt(20,15,Bmlinfo.bmWidth,Bmlinfo.bmHeight,&dcComp,0,0,SRCCOPY); 
	this->GetClientRect(&m_rtArea);
	CFont * oldFont = pDC->SelectObject(&timefont);
	pDC->SetTextColor(RGB(0,0,230));
	pDC->SetBkColor(RGB(bkgndR,bkgndG,bkgndB));
	pDC->SelectObject(oldFont);
	::ReleaseDC(NULL,dcComp);
}
void CSLACMVSNView::OnClose()
{
}

void CSLACMVSNView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	CRect rt;
	this->GetClientRect(rt);
}

CSLACMVSNView::~CSLACMVSNView()
{
}

void CSLACMVSNView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MAIN, m_MainTable);
	DDX_Control(pDX, IDC_USERNAME_GROUP, m_lbUSER);
}

BOOL CSLACMVSNView::OnEraseBkgnd(CDC* pDC)
{
	COLORREF   m_crBackground;   
	CBrush     m_wndbkBrush;    
	m_crBackground=RGB(bkgndR,bkgndG,bkgndB);//想要改成的颜色       
	m_wndbkBrush.CreateSolidBrush(m_crBackground);      
	CFormView::OnEraseBkgnd(pDC);//这里要看基类是什么就用哪个类.   
	CRect rect;   
	GetClientRect(rect);   
	pDC->FillRect(&rect,&m_wndbkBrush);
	return TRUE;
}

BOOL CSLACMVSNView::PreCreateWindow(CREATESTRUCT& cs)
{
	//  CREATESTRUCT cs 来修改窗口类或样式
	BOOL bRet = CFormView::PreCreateWindow(cs);
	CRect rect;
	GetDesktopWindow()->GetWindowRect(&rect);
	cs.cx = rect.Width();
	cs.cy = rect.Height();
	return bRet;
}

HBRUSH CSLACMVSNView::OnCtlColor(CDC* pDC,CWnd* pWnd,UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC,pWnd,nCtlColor);
	switch(nCtlColor)
	{
	case CTLCOLOR_BTN:
		pDC->SetBkMode(TRANSPARENT);
		break;
	case CTLCOLOR_DLG:
		pDC->SetBkMode(TRANSPARENT);
		break;
	default:
		pDC->SetBkMode(TRANSPARENT);
		break;
	}
	return hbr;
}

int CSLACMVSNView::OnCreate(LPCREATESTRUCT lpcs)
{
	if(CFormView::OnCreate(lpcs)==-1)
	{
		return -1;
	}
	if(!m_btnMenu.LoadBitmaps(IDB_BITMAP_PRONAMEDOWN,IDB_BITMAP_PRONAMEUP))
	{
		TRACE0("Failed to load bitmaps for buttons\n");
		AfxThrowResourceException();
	}
	ShowWindow(SW_HIDE);
	return 0;
}

void CSLACMVSNView::UpdateUserInfo(CString username, eUSER_GROUP userGroup)
{
	bool bAccess = false;
	CString strGroup;
	if(userGroup == ADMIN)
	{
		strGroup = _T("ADMIN");
		bAccess = true;
	}
	if(userGroup == ENGINEER) 
		strGroup = _T("ENGINEER");
	if(userGroup == OPERATOR)
		strGroup = _T("OPERATOR");
	if(userGroup == SADMIN)
	{
		strGroup = _T("SADMIN");
		bAccess = true;
	}

	m_btnLogin.ShowWindow(SW_HIDE);
	m_btnLogout.ShowWindow(SW_SHOWNORMAL);
	m_btnLogout.BringWindowToTop();
	CString strDisplay = username;
	strDisplay.Append(_T(" | "));
	strDisplay.Append(strGroup);
	CRect btnRect;
	m_lbUSER.SetWindowText(strDisplay);
	m_lbUSER.SetTxtFont(20,FW_BOLD);
	m_lbUSER.Invalidate(TRUE);

	if(bAccess)
	{
		m_btnUser.EnableWindow(TRUE);
		m_btnUser.SetBitmaps(IDB_USER,RGB(123,123,123),IDB_USER_IN,RGB(223,123,123),IDB_USER,RGB(223,123,123));
		m_btnExit.EnableWindow(TRUE);
		m_btnExit.SetBitmaps(IDB_EXIT,RGB(123,123,123),IDB_EXIT_IN,RGB(223,123,123),IDB_EXIT,RGB(223,123,123));
	}
	else
	{
		m_btnUser.EnableWindow(FALSE);
	}
}

void CSLACMVSNView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();    
	VERIFY(m_btnMenu.SubclassDlgItem(IDC_BTN_MENU,this));
	CSLACMVSNApp * pApp = (CSLACMVSNApp *)AfxGetApp();

	// Login button
	m_btnLogin.SubclassDlgItem(IDC_BUT_LOGIN,this);
#ifdef _ENGLISH
	m_btnLogin.SetTooltipText(_T("Login"));
#else
	m_btnLogin.SetTooltipText(_T("登录系统"));
#endif
	m_btnLogin.SetBitmaps(IDB_LOGIN,RGB(123,123,123),IDB_LOGIN1,RGB(223,123,123),IDB_LOGIN,RGB(223,123,123));
	m_btnLogin.DrawBorder(FALSE);

	// Logout button
	m_btnLogout.SubclassDlgItem(IDC_BUT_LOGOUT, this);
#ifdef _ENGLISH
	m_btnLogout.SetTooltipText(_T("Logout"));
#else
	m_btnLogout.SetTooltipText(_T("登出系统"));
#endif

	m_btnLogout.SetBitmaps(IDB_BITMAP_LOGOUT,RGB(123,123,123),IDB_BITMAP_LOGOUT_IN,RGB(223,123,123),IDB_BITMAP_LOGOUT,RGB(223,123,123));
	m_btnLogout.DrawBorder(FALSE);

	// Exit button
	m_btnExit.SubclassDlgItem(IDC_EXIT,this);
#ifdef _ENGLISH
	m_btnExit.SetTooltipText(_T("Exit"));
#else
	m_btnExit.SetTooltipText(_T("退出系统"));
#endif
	m_btnExit.SetBitmaps(IDB_BITMAP_EXIT_DISABLE,RGB(123,123,123),IDB_BITMAP_EXIT_DISABLE,RGB(223,123,123),IDB_BITMAP_EXIT_DISABLE,RGB(223,123,123));
	m_btnExit.DrawBorder(FALSE);
	m_btnExit.EnableWindow(FALSE);

	m_btnUser.SubclassDlgItem(IDC_USER,this);
#ifdef _ENGLISH
	m_btnUser.SetTooltipText(_T("User Manager"));
#else
	m_btnUser.SetTooltipText(_T("用户管理"));
#endif
	m_btnUser.SetBitmaps(IDC_USER_MANAGER_DISABLE,RGB(123,123,123),IDC_USER_MANAGER_DISABLE,RGB(223,123,123),IDC_USER_MANAGER_DISABLE,RGB(223,123,123));
	m_btnUser.DrawBorder(FALSE);
	m_btnUser.EnableWindow(FALSE);

	m_lbUSER.SetWindowText(_T("Not Login"));
	m_lbUSER.SetColor(RGB(0,0,0),RGB(200,220,245));
	m_lbUSER.SetTxtFont(20,FW_BOLD);
	CRect parentRt;
	GetClientRect(parentRt);
	CRect btnRt;
	m_btnUser.GetClientRect(&btnRt);
	m_btnLogin.MoveWindow(parentRt.right - btnRt.Width()*4 - 40,parentRt.top + 10,btnRt.Width(),btnRt.Height());
	m_btnLogout.MoveWindow(parentRt.right - btnRt.Width()*4 - 40,parentRt.top + 10,btnRt.Width(),btnRt.Height());
    m_btnUser.MoveWindow(parentRt.right - btnRt.Width()*3 - 30,parentRt.top + 10,btnRt.Width(),btnRt.Height()); 
	m_btnExit.MoveWindow(parentRt.right - btnRt.Width()*2 - 20,parentRt.top + 10,btnRt.Width(),btnRt.Height()); 

	m_lbUSER.GetClientRect(&btnRt);
	m_lbUSER.MoveWindow(parentRt.right - btnRt.Width() + 15,parentRt.top + btnRt.Height() + 5,btnRt.Width(),btnRt.Height());
	m_sCustomerTile.SubclassDlgItem(IDC_STATIC_CUSTOMINFO,this);
	m_sCustomerTile.SetWindowText(gConfigManager.GetBasicSetting(L"CUSTOMISED_TITLE").c_str());
    m_sCustomerTile.SetColor(RGB(10,10,115),RGB(bkgndR,bkgndG,bkgndB));
	m_sCustomerTile.SetTxtFont(50,FW_BOLD);//n.
	m_sCustomerTile.GetClientRect(&btnRt);
	m_sCustomerTile.MoveWindow(parentRt.Width()/2 - btnRt.Width()/2,parentRt.top + 2,btnRt.Width(),btnRt.Height());
	m_overView.Create(IDD_PROPPAGE_OVERVIEWPAGE,GetDlgItem(IDC_TAB_MAIN));
	((CMainFrame*)AfxGetMainWnd())->SOverViewWnd = &m_overView;
	CRect rect;
	GetDesktopWindow()->GetWindowRect(&rect);
	m_MainTable.CenterWindow();
	m_MainTable.MoveWindow(1,rect.top + 90,rect.right - 1,rect.bottom - 1);
	CRect rs;
	m_MainTable.GetClientRect(&rs);
	rs.top += 15; 
	rs.right -= 1; 
	m_overView.MoveWindow(&rs);
	m_overView.ShowWindow(true);
	m_MainTable.SetCurSel(0);
}

void CSLACMVSNView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSLACMVSNView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}
// CSLACMVSNView 诊断
#ifdef _DEBUG
void CSLACMVSNView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSLACMVSNView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CSLACMVSNDoc* CSLACMVSNView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSLACMVSNDoc)));
	return (CSLACMVSNDoc*)m_pDocument;
}

#endif //_DEBUG
void CSLACMVSNView::OnBnClickedExit()
{
	CSLACMVSNApp *theApp = (CSLACMVSNApp*)::AfxGetApp();
	CMainFrame * MainFrm = (CMainFrame *)theApp->m_pMainWnd;
	MainFrm->OnClose();
	PostQuitMessage(0);
}

void CSLACMVSNView::OnBnClickedLogin()
{
	CLoginDlg loginDlg;
	loginDlg.DoModal();
	loginDlg.DestroyWindow();
	m_lbUSER.SetColor(RGB(0,0,0),RGB(200,220,245));			
	m_lbUSER.Invalidate(TRUE);
}

void CSLACMVSNView::OnBnClickedUser()
{
	if (m_pSettingPropFrame == NULL)
	{
		m_pSettingPropFrame = new CSettingPropSheetFrame;
		size_t sz = sizeof(CSettingPropSheetFrame);
		CRect rect(0, 0, 0, 0);
#ifdef _ENGLISH
		CString strTitle(_T("Access Control"));
#else
		CString strTitle(_T("系统权限分配"));
#endif

		if (!m_pSettingPropFrame->Create(NULL, strTitle,WS_POPUP | WS_CAPTION | WS_SYSMENU, rect, this))
		{
			m_pSettingPropFrame = NULL;
			return;
		}
		m_pSettingPropFrame->CenterWindow();
		m_pSettingPropFrame->EnableWindow();
		m_pSettingPropFrame->ShowWindow(SW_SHOW);
	}
	if (m_pSettingPropFrame != NULL)
	{
		if(!m_pSettingPropFrame->IsWindowVisible())
		{
			m_pSettingPropFrame->ShowWindow(SW_SHOW);
		}
	}
}

void CSLACMVSNView::OnBnClickedButLogout()
{
	CPanelManager::GetPanelManager().SetUserGroup(OPERATOR);
	CPanelManager::GetPanelManager().UpdatePanelUserGroup(OPERATOR);
	m_lbUSER.SetWindowText(_T("Not Login"));
	m_lbUSER.SetColor(RGB(0,0,0),RGB(200,220,245));			
	m_lbUSER.Invalidate(TRUE);
	// Show up the Login button and hide the logout button
	m_btnLogout.ShowWindow(SW_HIDE);
	m_btnLogin.ShowWindow(SW_SHOWNORMAL);
	m_btnLogin.BringWindowToTop();
	// Disable the User Manager button.
	m_btnUser.EnableWindow(FALSE);
	m_btnUser.SetBitmaps(IDC_USER_MANAGER_DISABLE,RGB(123,123,123),IDC_USER_MANAGER_DISABLE,RGB(223,123,123),IDC_USER_MANAGER_DISABLE,RGB(223,123,123));

	m_btnExit.EnableWindow(FALSE);
	m_btnExit.SetBitmaps(IDB_BITMAP_EXIT_DISABLE,RGB(123,123,123),IDB_BITMAP_EXIT_DISABLE,RGB(223,123,123),IDB_BITMAP_EXIT_DISABLE,RGB(223,123,123));
}
