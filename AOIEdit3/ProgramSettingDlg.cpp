// CProgramSettingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AOIEditver3.h"
#include "ProgramSettingDlg.h"
#include "MConfigCenter.h"
#include "MCtrlCenter.h"
#include "MainFrm.h"
// CProgramSettingDlg 对话框

IMPLEMENT_DYNAMIC(CProgramSettingDlg, CDialog)

CProgramSettingDlg::CProgramSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProgramSettingDlg::IDD, pParent)
{ 
}

CProgramSettingDlg::~CProgramSettingDlg()
{
}

void CProgramSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_PROSETTING, m_TabCtrl_ProSetting);
	DDX_Control(pDX, IDC_CHECK_AUTOINIT, m_InitCurrentPro);
}

BEGIN_MESSAGE_MAP(CProgramSettingDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CProgramSettingDlg::OnBnClickedOk)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_PROSETTING, &CProgramSettingDlg::OnTcnSelchangeTabProsetting)
	ON_WM_CTLCOLOR()
	ON_WM_DRAWITEM()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDCANCEL, &CProgramSettingDlg::OnBnClickedCancel)
END_MESSAGE_MAP()

void CProgramSettingDlg::OnBnClickedOk()
{
	if (!(m_RejectTab.OnBnClickedMyOk()&&m_CameraTab.OnBnClickedOk()&&m_BaseTab.OnBnClickedOk()))
	{
		return;
	}
	CDialog::OnOK();
}

BOOL CProgramSettingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
#ifdef _ENGLISH
	m_TabCtrl_ProSetting.InsertItem(0,_T("Basic Setting"));
	m_TabCtrl_ProSetting.InsertItem(1,_T("Camera & Light Setting"));
	m_TabCtrl_ProSetting.InsertItem(2,_T("Rejection Setting"));
#else
	m_TabCtrl_ProSetting.InsertItem(0,_T("基本设置"));
	m_TabCtrl_ProSetting.InsertItem(1,_T("相机及光源设置"));
	m_TabCtrl_ProSetting.InsertItem(2,_T("排盖设置"));
#endif

	m_BaseTab.Create(IDD_DIALOG_PROSET_BASE,GetDlgItem(IDC_TAB_PROSETTING));
	m_CameraTab.Create(IDD_DIALOG_PROSET_CAMERA,GetDlgItem(IDC_TAB_PROSETTING));
	m_RejectTab.Create(IDD_DIALOG_PROSET_REJECT,GetDlgItem(IDC_TAB_PROSETTING));

	m_InitCurrentPro.SetCheck(BST_CHECKED);

	//获得IDC_TABTEST客户区大小
	CRect rs;
	m_TabCtrl_ProSetting.GetClientRect(&rs);
	//调整子对话框在父窗口中的位置
	rs.top+=20; 
	rs.bottom-=0; 
	rs.left+=2; 
	rs.right-=2; 


	//设置子对话框尺寸并移动到指定位置
	m_BaseTab.MoveWindow(&rs);
	m_CameraTab.MoveWindow(&rs);
	m_RejectTab.MoveWindow(&rs);

	m_CameraTab.ShowWindow(true);
	m_RejectTab.ShowWindow(true);
	//分别设置隐藏和显示
	m_BaseTab.ShowWindow(true);
	m_CameraTab.ShowWindow(false);
	m_RejectTab.ShowWindow(false);

	//设置默认的选项卡
	m_TabCtrl_ProSetting.SetCurSel(0);

	//CRect cRect;
	//GetClientRect(&cRect);
	//m_denyRect.left = cRect.right - 52;
	//m_denyRect.top = cRect.bottom - 44;
	//m_denyRect.right = cRect.right - 20;
	//m_denyRect.bottom = cRect.bottom - 12;

	//m_acceptRect.left = m_denyRect.left - 40;
	//m_acceptRect.top = m_denyRect.top;
	//m_acceptRect.right = m_denyRect.right - 40;
	//m_acceptRect.bottom = m_denyRect.bottom;
	return TRUE;
}

void CProgramSettingDlg::OnTcnSelchangeTabProsetting(NMHDR *pNMHDR, LRESULT *pResult)
{
	int CurSel = m_TabCtrl_ProSetting.GetCurSel();
	m_CameraTab.ShowWindow(false);
	m_RejectTab.ShowWindow(false);
	m_BaseTab.ShowWindow(false);

	switch(CurSel)
	{
	case 0:
		m_BaseTab.ShowWindow(true);//page1显示
		break; 
	case 1:
		m_CameraTab.UpdateCheckBox_LightCtrl();
		m_CameraTab.ShowWindow(true);//page2显示
		break;
	case 2:
		m_RejectTab.ShowWindow(true);//page2显示
		break;
	default:
		break;
	}
	*pResult = 0;
}

void CProgramSettingDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	TCHAR    szTabText[100];
	TCITEM    tci;

	CTabCtrl *pTabCtrl = &m_TabCtrl_ProSetting; // My tab control.
	ASSERT( pTabCtrl );

	if (pTabCtrl->m_hWnd == lpDrawItemStruct->hwndItem)
	{
		memset(szTabText, '\0', sizeof(szTabText));
		tci.mask        = TCIF_TEXT;
		tci.pszText     = szTabText;
		tci.cchTextMax  = sizeof(szTabText)-1;

		pTabCtrl->GetItem(lpDrawItemStruct->itemID, &tci);
		CDC *dc = CDC::FromHandle(lpDrawItemStruct->hDC);

		///dc->FillRect(&lpDrawItemStruct->rcItem, &UI_DECORATOR.m_brushBk);
		dc->SetBkColor(RGB(11,122,193));
		dc->SetTextColor(RGB(255,255,255));

		long left = lpDrawItemStruct->rcItem.left;
		long top  = lpDrawItemStruct->rcItem.top;
		TextOut(lpDrawItemStruct->hDC, left, top, tci.pszText, lstrlen(tci.pszText));
	}
}

void CProgramSettingDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
}

void CProgramSettingDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonDown(nFlags, point);
}

void CProgramSettingDlg::OnBnClickedCancel()
{
	CDialog::OnCancel();
}
