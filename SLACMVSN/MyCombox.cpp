#include "stdafx.h"
#include "MyComBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMTILabel

MyComboBox::MyComboBox()
{
	m_bIsColor=FALSE;
	m_bOver=FALSE;
	m_iTxtHeight=14;
	m_iTxtWeight=FW_NORMAL;

}

MyComboBox::~MyComboBox()
{
}


BEGIN_MESSAGE_MAP(MyComboBox, CComboBox)
	//{{AFX_MSG_MAP(MyComboBox)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMTILabel message handlers

void MyComboBox::OnPaint() 
{
	CComboBox::OnPaint();

	CPaintDC dc(this); // device context for painting
	dc.SetTextColor(m_Color);
	CRect rect;
	GetClientRect(&rect);		//获得控件客户区矩形大小
    dc.SetBkColor(m_BgColor);
	dc.FillSolidRect(0,0,rect.Width(),rect.Height(),m_BgColor);
	//CFont font;
	//font.CreateFont(
	//	m_iTxtHeight,                        // nHeight
	//	0,                         // nWidth
	//	0,                         // nEscapement
	//	0,                         // nOrientation
	//	m_iTxtWeight,	                // nWeight
	//	FALSE,                     // bItalic
	//	FALSE,                     // bUnderline
	//	0,                         // cStrikeOut
	//	ANSI_CHARSET,              // nCharSet
	//	OUT_DEFAULT_PRECIS,        // nOutPrecision
	//	CLIP_DEFAULT_PRECIS,       // nClipPrecision
	//	DEFAULT_QUALITY,           // nQuality
	//	DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
	//	_T("Arial"));

	//GetWindowText(m_strText);
	//TEXTMETRIC tm;
	//dc.GetTextMetrics(&tm);
	//CFont* def_font = dc.SelectObject(&font);
	//dc.TextOut(2, (rect.Height()-tm.tmHeight)/2, m_strText.Left(20));
	//dc.SelectObject(def_font);	
	//// Done with the font.  Delete the font object.
	//font.DeleteObject();
}

VOID MyComboBox::SetColor(COLORREF Color,COLORREF BgColor)
{
	m_bIsColor=TRUE;
	m_Color=Color;
	m_BgColor=BgColor;	
}

VOID MyComboBox::SetTxtFont(int height,int weight)
{
	m_iTxtHeight=height;
	m_iTxtWeight=weight;
}

BOOL MyComboBox::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return CComboBox::OnEraseBkgnd(pDC);
}