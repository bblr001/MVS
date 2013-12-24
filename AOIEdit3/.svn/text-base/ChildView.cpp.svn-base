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

// ChildView.cpp : CChildView 类的实现
//

#include "stdafx.h"
#include "AOIEditVer3.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView():m_hoHWindCLS(""),m_bInitHalconW(false)
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CChildView 消息处理程序

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, ::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}
int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    int iRet = CWnd::OnCreate(lpCreateStruct);
	return iRet;
}
void CChildView::InitHalconWindow()
{
	 if(m_bInitHalconW)return;
	 m_bInitHalconW = true;
	 m_hoHWindCLS.OpenWindow(0,0,m_wndWidth,m_wndHeigth,(Hlong)m_hWnd,"visible");
	 m_hoHWindCLS.SetPart(0,0,m_wndWidth-1,m_wndHeigth-1);
}
void CChildView::InitImageWindow(Halcon::HByteImage& byteImg)
{
	
    if(m_wndWidth > byteImg.Width())
	{
      m_wndWidth = byteImg.Width();
	}
	m_wndHeigth =  m_wndWidth * byteImg.Height() / byteImg.Width(); 
	InitHalconWindow();
}
void CChildView::InitImageWindow(Halcon::Hobject& objImg)
{	
	char     lpcsType[MAX_STRING];
	Hlong    lPointer;
	Hlong Width,Heigth;
	Halcon::get_image_pointer1(objImg,&lPointer,lpcsType,&Width,&Heigth);
	if(m_wndWidth > Width)
	{
		m_wndWidth = Width;
	}
	m_wndHeigth =  m_wndWidth * Heigth / Width; 
	InitHalconWindow();
}
void CChildView::OnClose()
{
    if(m_bInitHalconW)m_hoHWindCLS.CloseWindow();
	CWnd::OnClose();
}
void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType,cx,cy);
	m_wndWidth = cx;
	m_wndHeigth= cy;
}
void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 用于绘制的设备上下文
}

