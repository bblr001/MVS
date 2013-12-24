// OverViewPage.cpp : 实现文件
//

#include "stdafx.h"
#include "SLACMVSN.h"
#include "OverViewPage.h"
#include "TypeCent.h"
#include "PanelManager.h"

// COverViewPage 对话框

IMPLEMENT_DYNAMIC(COverViewPage, CPropertyPage)

COverViewPage::COverViewPage()
	: CPropertyPage(COverViewPage::IDD)
{}
COverViewPage::~COverViewPage()
{}
BOOL COverViewPage::OnEraseBkgnd(CDC* pDC)
{
	COLORREF   m_crBackground;   
	CBrush     m_wndbkBrush;    
	m_crBackground=RGB(bkgndR,bkgndG,bkgndB);//想要改成的颜色       
	m_wndbkBrush.CreateSolidBrush(m_crBackground);      
	CPropertyPage::OnEraseBkgnd(pDC);//这里要看基类是什么就用哪个类.   
	CRect rect;   
	GetClientRect(rect);   
	pDC->FillRect(&rect,&m_wndbkBrush);
	return TRUE;
}
void COverViewPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(COverViewPage, CPropertyPage)
	 //{{AFX_MSG_MAP(COverViewPage)
	 ON_WM_ERASEBKGND()
	//}}
END_MESSAGE_MAP()
// COverViewPage 消息处理程序
