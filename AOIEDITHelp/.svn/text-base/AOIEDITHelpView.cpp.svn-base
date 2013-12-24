
// AOIEDITHelpView.cpp : CAOIEDITHelpView 类的实现
//

#include "stdafx.h"
#include "AOIEDITHelp.h"
#include "MainFrm.h"
#include "AOIEDITHelpDoc.h"
#include "AOIEDITHelpView.h"
#include "DoProcess/CMCfgCenter.h"
#include "DoProcess/CMCtrolCenter.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAOIEDITHelpView

IMPLEMENT_DYNCREATE(CAOIEDITHelpView, CFormView)

BEGIN_MESSAGE_MAP(CAOIEDITHelpView, CFormView)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_MOVING()
	ON_WM_SIZE()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// CAOIEDITHelpView 构造/析构

CAOIEDITHelpView::CAOIEDITHelpView()
	: CFormView(CAOIEDITHelpView::IDD),m_bRBtnDB(false)
{
	// TODO: 在此处添加构造代码

}

CAOIEDITHelpView::~CAOIEDITHelpView()
{
}
void CAOIEDITHelpView::OnMoving(UINT nSide, LPRECT lpRect)
{
	CFormView::OnMoving(nSide,lpRect);
}
void CAOIEDITHelpView::OnDraw(CDC* pDC)
{
	CFormView::OnDraw(pDC);
}
void CAOIEDITHelpView::OnPaint()
{
	CFormView::OnPaint();
}
void CAOIEDITHelpView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_GRAB_IMAGE, m_halconDispWnd);
}

BOOL CAOIEDITHelpView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	return CFormView::PreCreateWindow(cs);
}
void CAOIEDITHelpView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType,cx,cy);
}
void CAOIEDITHelpView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
    SysInit();
}
void CAOIEDITHelpView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CFormView::OnUpdate(pSender,lHint,pHint);
}
void CAOIEDITHelpView::SysInit()
{
}
void CAOIEDITHelpView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	using namespace Halcon;
	if (m_bRBtnDB)
	{
		long width, height;
		CMCfgCenter::GetCfgCenter().GetImageSize(width, height);
		set_part(CMCfgCenter::GetCfgCenter().GetHCWnd(),0,0,height-1,width-1);
		CMCtrlCenter::GetCtrlCenter().ShotGrab();
		m_bRBtnDB = false;
	}
}
void CAOIEDITHelpView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	using namespace Halcon;
	if (!m_bRBtnDB)
	{
		HTuple  Row1, Column1, Row2, Column2;
		draw_rectangle1(CMCfgCenter::GetCfgCenter().GetHCWnd(), &Row1, &Column1, &Row2, &Column2);
		set_part(CMCfgCenter::GetCfgCenter().GetHCWnd(),Row1, Column1, Row2, Column2);
		CMCtrlCenter::GetCtrlCenter().ShotGrab();
		m_bRBtnDB = true;
	}
}
void CAOIEDITHelpView::OnDestroy()
{
	CFormView::OnDestroy();
}
// CAOIEDITHelpView 诊断

#ifdef _DEBUG
void CAOIEDITHelpView::AssertValid() const
{
	CFormView::AssertValid();
}

void CAOIEDITHelpView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CAOIEDITHelpDoc* CAOIEDITHelpView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAOIEDITHelpDoc)));
	return (CAOIEDITHelpDoc*)m_pDocument;
}
#endif //_DEBUG


// CAOIEDITHelpView 消息处理程序
