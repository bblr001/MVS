// TabCtrlEx.cpp : implementation file
//

#include "stdafx.h"
#include "TabCtrlDoc.h"
#include "SLACMVSN.h"
#include "Resource.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabCtrlDoc

CTabCtrlDoc::CTabCtrlDoc()
{
	m_crSelColour     = RGB(0, 0, 255);
	m_crUnselColour   = RGB(50, 50, 50);
}

CTabCtrlDoc::~CTabCtrlDoc()
{
	m_SelFont.DeleteObject();
	m_UnselFont.DeleteObject();
}

BEGIN_MESSAGE_MAP(CTabCtrlDoc, CTabCtrl)
	//{{AFX_MSG_MAP(CTabCtrlDoc)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_RBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabCtrlDoc message handlers

int CTabCtrlDoc::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTabCtrl::OnCreate(lpCreateStruct) == -1) return -1;
	//ModifyStyle(0, TCS_OWNERDRAWFIXED);
	return 0;
}

void CTabCtrlDoc::PreSubclassWindow() 
{	
	CTabCtrl::PreSubclassWindow();
	//ModifyStyle(0, TCS_OWNERDRAWFIXED);
}
HBRUSH CTabCtrlDoc::OnCtlColor(CDC* pDC,CWnd* pWnd,UINT nCtlColor)
{
	HBRUSH hbr = CTabCtrl::OnCtlColor(pDC,pWnd,nCtlColor);
	switch(nCtlColor)
	{
	case CTLCOLOR_BTN:
		pDC->SetBkColor(RGB(bkgndR,bkgndG,bkgndB));
		break;
	case CTLCOLOR_DLG:
		pDC->SetBkColor(RGB(bkgndR,bkgndG,bkgndB));
		break;
	default:
		pDC->SetBkColor(RGB(bkgndR,bkgndG,bkgndB));
		break;
	}
	return hbr;

}
BOOL CTabCtrlDoc::OnEraseBkgnd(CDC* pDC)
{
	COLORREF   m_crBackground;   
	CBrush     m_wndbkBrush;    
	m_crBackground=RGB(bkgndR,bkgndG,bkgndB);//想要改成的颜色       
	m_wndbkBrush.CreateSolidBrush(m_crBackground);      
	CTabCtrl::OnEraseBkgnd(pDC);//这里要看基类是什么就用哪个类.   
	CRect rect;   
	GetClientRect(rect);   
	pDC->FillRect(&rect,&m_wndbkBrush);
	return TRUE;
}
void CTabCtrlDoc::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{	
	CTabCtrl::DrawItem(lpDrawItemStruct);
	CRect rect = lpDrawItemStruct->rcItem;
    int nTabIndex = lpDrawItemStruct->itemID;
    if (nTabIndex < 0) return;
    BOOL bSelected = (nTabIndex == GetCurSel());
 
    wchar_t label[64];
    TC_ITEM tci;
    tci.mask = TCIF_TEXT|TCIF_IMAGE;
    tci.pszText = label;     
  	tci.cchTextMax = 63;    	
    if (!GetItem(nTabIndex, &tci)) return;

	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	if (!pDC) return;
    int nSavedDC = pDC->SaveDC();
//
//	// For some bizarre reason the rcItem you get extends above the actual
//	// drawing area. We have to workaround this "feature".
    rect.top += ::GetSystemMetrics(SM_CYEDGE);
 
    pDC->SetBkMode(TRANSPARENT);
 	//pDC->FillSolidRect(rect, ::GetSysColor(COLOR_BTNFACE));
	pDC->FillSolidRect(rect, RGB(255,255,0));
	COLORREF   m_crBackground;   
	CBrush     m_wndbkBrush;    
	m_crBackground=RGB(255,0,0);//想要改成的颜色       
	m_wndbkBrush.CreateSolidBrush(m_crBackground);  
	pDC->FillRect(rect,&m_wndbkBrush);
    pDC->SetBkColor(m_crSelColour);
//
//	// Draw image
//	CImageList* pImageList = GetImageList();
//	if (pImageList && tci.iImage >= 0) 
//	{
//
//		rect.left += pDC->GetTextExtent(_T(" ")).cx;		// Margin
//
//		// Get height of image so we 
//		IMAGEINFO info;
//		pImageList->GetImageInfo(tci.iImage, &info);
//		CRect ImageRect(info.rcImage);
//		int nYpos = rect.top;
//
//		pImageList->Draw(pDC, tci.iImage, CPoint(rect.left, nYpos), ILD_TRANSPARENT);
//		rect.left += ImageRect.Width();
//	}
//
//	if (bSelected) 
//	{
//		pDC->SetTextColor(m_crSelColour);
//		pDC->SelectObject(&m_SelFont);
//		rect.top -= ::GetSystemMetrics(SM_CYEDGE);
////		pDC->DrawText(label, rect, DT_SINGLELINE|DT_VCENTER|DT_CENTER);
//	}
//	else 
//	{
//		pDC->SetTextColor(m_crUnselColour);
//		pDC->SelectObject(&m_UnselFont);
////		pDC->DrawText(label, rect, DT_SINGLELINE|DT_BOTTOM|DT_CENTER);
//	}
//
 	pDC->RestoreDC(nSavedDC);
}

/////////////////////////////////////////////////////////////////////////////
// CTabCtrlDoc operations

void CTabCtrlDoc::SetColours(COLORREF bSelColour, COLORREF bUnselColour)
{
	m_crSelColour = bSelColour;
	m_crUnselColour = bUnselColour;
	Invalidate();
}

void CTabCtrlDoc::SetFonts(CFont* pSelFont, CFont* pUnselFont)
{
	ASSERT(pSelFont && pUnselFont);

	LOGFONT lFont;
	int nSelHeight, nUnselHeight;

	m_SelFont.DeleteObject();
	m_UnselFont.DeleteObject();

	pSelFont->GetLogFont(&lFont);
	m_SelFont.CreateFontIndirect(&lFont);
	nSelHeight = lFont.lfHeight;

	pUnselFont->GetLogFont(&lFont);
	m_UnselFont.CreateFontIndirect(&lFont);
	nUnselHeight = lFont.lfHeight;

	SetFont((nSelHeight > nUnselHeight) ? &m_SelFont : &m_UnselFont);
}


void CTabCtrlDoc::SetFonts(int nSelWeight,   BOOL bSelItalic,   BOOL bSelUnderline, 
						   int nUnselWeight, BOOL bUnselItalic, BOOL bUnselUnderline)
{
	// Free any memory currently used by the fonts.
	m_SelFont.DeleteObject();
	m_UnselFont.DeleteObject();
	
	// Get the current font
	LOGFONT lFont;
	CFont* pFont = GetFont();
	if (pFont)
		pFont->GetLogFont(&lFont);
	else 
	{
		NONCLIENTMETRICS ncm;
		ncm.cbSize = sizeof(NONCLIENTMETRICS);
		VERIFY(SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0));
		lFont = ncm.lfMessageFont; 
	}

	// Create the "Selected" font
	lFont.lfWeight = nSelWeight;
	lFont.lfItalic = bSelItalic;
	lFont.lfUnderline = bSelUnderline;
	m_SelFont.CreateFontIndirect(&lFont);
	
	// Create the "Unselected" font
	lFont.lfWeight = nUnselWeight;
	lFont.lfItalic = bUnselItalic;
	lFont.lfUnderline = bUnselUnderline;
	m_UnselFont.CreateFontIndirect(&lFont);
	
	SetFont((nSelWeight > nUnselWeight) ? &m_SelFont : &m_UnselFont);
}

void CTabCtrlDoc::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// 当鼠标在CControlBar控件上按动右键时弹出浮动菜单
	POINT  ptScreen = point;
	// 转换鼠标坐标到屏幕坐标
//	ClientToScreen(&ptScreen);
	// 自定义类，从CMenu派生
	//CPopupMenu cMenu;
	// 创建弹出式浮动菜单
//	cMenu.CreatePopupMenu();
	// 添加菜单项，ID_VIEW_VIEWTAB是菜单命令ID值
		
	// 添加分隔符
	//cMenu.AppendMenu(MF_STRING, ID_FILE_CLOSE, _T("关闭本窗口"));
	//this->GetCurSel();
	//cMenu.LoadToolBarResource(IDR_TABVIEW_MENU);
	//cMenu.RemapMenu(&cMenu);
	//cMenu.EnableMenuItems(&cMenu, AfxGetMainWnd());
//	cMenu.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, ptScreen.x, ptScreen.y, AfxGetMainWnd());
}

void CTabCtrlDoc::OnSetFocus(CWnd* pOldWnd) 
{
	CTabCtrl::OnSetFocus(pOldWnd);
}
