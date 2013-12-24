#pragma once

#include "stdafx.h"
#include "MyLabel.h"
#include "../SLACMVSN/ui_decorator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMTILabel

CMyLabel::CMyLabel()
{
	m_bIsColor=FALSE;
	m_bOver=FALSE;
	m_iTxtHeight=14;
	m_iTxtWeight=FW_NORMAL;
	m_ptrImage = nullptr;
	m_ptrUiDecorator = nullptr;
}

CMyLabel::~CMyLabel()
{
}


BEGIN_MESSAGE_MAP(CMyLabel, CStatic)
	//{{AFX_MSG_MAP(CMTILabel)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMTILabel message handlers

void CMyLabel::OnPaint() 
{
	if (!m_bIsColor)
		CStatic::OnPaint();
	
	CPaintDC dc(this); // device context for painting
	dc.SetTextColor(m_Color);
	CRect rect;
	GetClientRect(&rect);		//获得控件客户区矩形大小
	if(m_ptrImage != nullptr)
	{
		m_ptrImage->TransparentBlt(dc, rect, RGB(0,0,0));
		return;
	}
	dc.FillSolidRect(0,0,rect.Width(),rect.Height(),m_BgColor);
	CFont font;
	font.CreateFont(
		m_iTxtHeight,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		m_iTxtWeight,	                // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("Arial"));
	
	GetWindowText(m_strText);
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
	CFont* def_font = dc.SelectObject(&font);
	dc.TextOut(2, (rect.Height()-tm.tmHeight)/2, m_strText);
	dc.SelectObject(def_font);	
	// Done with the font.  Delete the font object.
	font.DeleteObject();
}

VOID CMyLabel::SetColor(COLORREF Color,COLORREF BgColor)
{
	m_bIsColor=TRUE;
	m_Color=Color;
	m_BgColor=BgColor;	
}

VOID CMyLabel::SetTxtFont(int height,int weight)
{
	m_iTxtHeight=height;
	m_iTxtWeight=weight;
}

BOOL CMyLabel::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return CStatic::OnEraseBkgnd(pDC);
}

void CMyLabel::SetPtr2UiDecorator(ui_decorator* ptrUiDecorator)
{
	m_ptrUiDecorator = ptrUiDecorator;
}

void CMyLabel::UpdateSytemStatusSymbol(eMTI_GUI_STATE state)
{
	SetColor(RGB(10,10,115),RGB(200,220,250));
	if(m_ptrUiDecorator == nullptr)
		return;
	if(state == MTI_GUI_IDLE || state == MTI_GUI_INIT)
	{
		m_ptrImage = &m_ptrUiDecorator->m_imgReady;
	}
	if(state == MTI_GUI_RUN)
	{
		m_ptrImage = &m_ptrUiDecorator->m_imgRun;
	}
	if(state == MTI_GUI_STOP)
	{
		m_ptrImage = &m_ptrUiDecorator->m_imgStop;
	}
	if(state == MTI_GUI_PAUSE)
	{
		m_ptrImage = &m_ptrUiDecorator->m_imgPause;
	}
	if(state == MTI_GUI_ALARM)
	{
		m_ptrImage = &m_ptrUiDecorator->m_imgAlarm;
	}
	// 
	Invalidate();
}