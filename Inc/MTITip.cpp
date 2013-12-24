// MTITip.cpp: implementation of the CMTITip class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MTITip.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define CX_ROUNDED				12		// Tip horizontal roundness
#define CY_ROUNDED				10		// Tip vertical roundness
#define CX_LEADER				25		// Width of tip lead
#define CY_LEADER				25		// Height of tip lead
#define CX_ICON_MARGIN			5		// Width of margin between icon and tip text
#define DEFAULT_SHOW_DELAY		500		// Default show delay (ms)
#define TIMER_HIDE				25000	// Hide timer (ms)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMTITip::CMTITip()
{
	m_szClass		= AfxRegisterWndClass(0);
	m_hIcon			= NULL;
	// Set the delay defaults
	m_nShowDelay	= DEFAULT_SHOW_DELAY;
	m_IconSize		= CSize(0, 0);
	m_ptOrigin		= CPoint(0, 0);
}

CMTITip::~CMTITip()
{

}
// Message map
BEGIN_MESSAGE_MAP(CMTITip, CWnd)
	//{{AFX_MSG_MAP(CXInfoTip)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
BOOL CMTITip::Create(CWnd* pParentWnd)
{
    m_pFont = CFont::FromHandle((HFONT)::GetStockObject(DEFAULT_GUI_FONT));
    return(CreateEx(NULL, m_szClass, NULL, WS_POPUP, 0, 0, 0, 0, pParentWnd->GetSafeHwnd(), NULL, NULL));
}
int CMTITip::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if ( CWnd::OnCreate( lpCreateStruct ) == -1 )
      return -1;
   
   return 0;
}
void CMTITip::OnPaint()
{
	CPaintDC dc( this ); // device context for painting

	CRect	rc;
	CBrush	WindowBrush;
	CBrush	FrameBrush;
	CBrush	InnerFrameBrush;
	HRGN	hRegion;
	CRgn	*pRegion;
	CFont	*pSysFont;

	// Get the client rectangle
	GetClientRect(rc);

	// Create the brushes
	InnerFrameBrush.CreateSolidBrush(::GetSysColor(COLOR_SCROLLBAR));
	FrameBrush.CreateSolidBrush(::GetSysColor(COLOR_WINDOWTEXT));
	WindowBrush.CreateSolidBrush(::GetSysColor(COLOR_WINDOW));

	// Get the window region
	GetWindowRegion(&dc, &hRegion);
	pRegion = CRgn::FromHandle(hRegion);

	// Draw the frame
	dc.FillRgn(pRegion, &WindowBrush);
	dc.FrameRgn(pRegion, &InnerFrameBrush, 3, 3);
	dc.FrameRgn(pRegion, &FrameBrush, 1, 1);

	// Adjust the area for the icon
	rc.DeflateRect(CX_ROUNDED, CY_ROUNDED, 0, 0);
	if (m_hIcon != NULL)
		rc.left = rc.left + m_IconSize.cx + CX_ICON_MARGIN;
	
	// Set the font
	pSysFont = (CFont *)dc.SelectObject(m_pFont);
	// Draw the tip text	
	dc.SetBkMode( TRANSPARENT );
	dc.DrawText(m_szText, &rc, DT_TOP | DT_LEFT);

	// Draw the icon
	if (m_hIcon != NULL)
		DrawIconEx(dc.m_hDC, CX_ROUNDED, CY_ROUNDED, m_hIcon, m_IconSize.cx, m_IconSize.cy, 0, NULL, DI_NORMAL);

	// Clean up GDI
	::DeleteObject(hRegion);
	dc.SelectObject(pSysFont);
}
void CMTITip::OnTimer(UINT nIDEvent)
{
	HRGN	hRegion;
	CSize	WindowSize;
	CDC		*pDC;
	CPoint	ptCursor;

	switch (nIDEvent)
	{
	/////////////////////////////////////////////////////////////////////
	// Show the tip window
	/////////////////////////////////////////////////////////////////////
	case timerShow:
		KillTimer(m_nTimer);

		pDC = GetDC();
		GetWindowRegion(pDC, &hRegion, &WindowSize);
		ReleaseDC(pDC);

		::SetWindowRgn(m_hWnd, hRegion, TRUE);

		SetWindowPos(&wndTop, m_ptOrigin.x - WindowSize.cx + CX_ROUNDED, m_ptOrigin.y - WindowSize.cy + CY_ROUNDED, WindowSize.cx, WindowSize.cy, SWP_NOACTIVATE | SWP_SHOWWINDOW);
		if(TIMER_HIDE)
			m_nTimer = SetTimer(timerHide, TIMER_HIDE, NULL);
		break;
	/////////////////////////////////////////////////////////////////////
	// Hide the tip window
	/////////////////////////////////////////////////////////////////////
	case timerHide:
		GetCursorPos(&ptCursor);
		if (ptCursor != m_ptOrigin)
		{
			KillTimer(m_nTimer);
			ShowWindow(SW_HIDE);
		}

		break;
	}

	CWnd::OnTimer(nIDEvent);
}
void CMTITip::OnDestroy()
{
		KillTimer(m_nTimer);

	CWnd::OnDestroy();
}

void CMTITip::Show(CString szText, CPoint *pt)
{
	if (pt != NULL)
		m_ptOrigin	= *pt;
	else
		GetCursorPos(&m_ptOrigin);
	
	m_szText	= szText;
	// Start the show timer
	m_nTimer = SetTimer(timerShow, m_nShowDelay, NULL);
}
BOOL CMTITip::GetWindowRegion(CDC* pDC, HRGN* hRegion, CSize *Size /* = NULL */)
{
	CRect	rcWnd;
	POINT	ptLeader[3];
	CRgn	LeaderRegion;
	CRgn	CaptionRegion;
	CFont	*pSysFont;
	
	ASSERT(pDC != NULL);
	ASSERT(hRegion != NULL);

	// Calculate the are for the tip text
	pSysFont = (CFont *)pDC->SelectObject(m_pFont);
	pDC->DrawText(m_szText, &rcWnd, DT_CALCRECT);
	pDC->SelectObject(pSysFont);

	// Adjust for the rounded corners
	rcWnd.InflateRect(CX_ROUNDED, CY_ROUNDED);

	// Adjust for icon
	if (m_hIcon != NULL)
		rcWnd.right = rcWnd.right + m_IconSize.cx + CX_ICON_MARGIN;
	if (rcWnd.Height() < m_IconSize.cy)
		rcWnd.bottom = rcWnd.top + m_IconSize.cy;

	// Calculate the leader triangle coordinates

	ptLeader[0].x	= rcWnd.Width() - CX_ROUNDED;
	ptLeader[0].y	= rcWnd.Height() - CY_ROUNDED;

	ptLeader[1].x	= ptLeader[0].x;
	ptLeader[1].y	= ptLeader[0].y + CY_LEADER;

	ptLeader[2].x	= ptLeader[0].x - CX_LEADER;
	ptLeader[2].y	= rcWnd.Height() - CY_ROUNDED;

	// Create the caption region
	CaptionRegion.CreateRoundRectRgn(0, 0, rcWnd.Width(), rcWnd.Height(), CX_ROUNDED, CY_ROUNDED);
	// Create the leader region
	LeaderRegion.CreatePolygonRgn(ptLeader, 3, ALTERNATE);
	// Create window region
	*hRegion =  ::CreateRectRgn(0, 0, rcWnd.Width(), rcWnd.Height() + CY_LEADER);
	// Combine the regions
	CombineRgn(*hRegion, CaptionRegion.operator HRGN(), LeaderRegion.operator HRGN(), RGN_OR);

	// Set the window size
	if (Size != NULL)
	{
		Size->cx	= rcWnd.Width();
		Size->cy	= rcWnd.Height() + CY_LEADER;
	}

	return TRUE;
}
void CMTITip::SetIcon(HICON hIcon) 
{
	ICONINFO	IconInfo;

	m_hIcon = hIcon; 

	if (hIcon == NULL)
	{
		m_IconSize = CSize(0, 0);
		return;
	}
	
	// Get the icon sizes	
	ZeroMemory(&IconInfo, sizeof(ICONINFO));
	::GetIconInfo(m_hIcon, &IconInfo);

	m_IconSize.cx = (BYTE)(IconInfo.xHotspot * 2);
	m_IconSize.cy = (BYTE)(IconInfo.yHotspot * 2);
    
	::DeleteObject(IconInfo.hbmMask);
	::DeleteObject(IconInfo.hbmColor);

	if (IsWindow(m_hWnd))
		RedrawWindow();
}