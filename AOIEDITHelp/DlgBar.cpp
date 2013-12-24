// DlgBar.cpp : 实现文件
//
#include "stdafx.h"
#include "AOIEDITHelp.h"
#include "DlgBar.h"
#include "DoProcess/CMData.h"

// CDlgBar

IMPLEMENT_DYNAMIC(CDlgBar, CDialogBar)

CDlgBar::CDlgBar()
{

}

CDlgBar::~CDlgBar()
{
}
LRESULT CDlgBar::CHGTitle(WPARAM wp, LPARAM)
{
	 if (m_staTextInfo.GetSafeHwnd())
	 {
		   m_staTextInfo.SetWindowText((wchar_t*)wp);
	 }
	 return 0;
}
int CDlgBar::OnCreate(LPCREATESTRUCT lpcs)
{
	if (CDialogBar::OnCreate(lpcs)==-1)
	{
		return -1;
	}
	CRect rectDummy;
	rectDummy.SetRectEmpty();
	if(!m_staTextInfo.Create(_T(""),WS_VISIBLE|WS_CHILD,rectDummy,this))
	{
		return -1;
	}
	return 0;
}
void CDlgBar::OnSize(UINT nType, int cx, int cy)
{
	CDialogBar::OnSize(nType, cx, cy);

	if (m_staTextInfo.GetSafeHwnd())
	{
		CRect rc ;
		m_staTextInfo.GetWindowRect( &rc ) ;
		ScreenToClient( &rc ) ;
		m_staTextInfo.SetWindowPos( NULL, 1, 5, cx-2, cy - 2,
			SWP_NOACTIVATE|SWP_NOZORDER ) ;
	}
}
BEGIN_MESSAGE_MAP(CDlgBar, CDialogBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(MSG_CHGTITLE, CDlgBar::CHGTitle)
END_MESSAGE_MAP()



// CDlgBar 消息处理程序


