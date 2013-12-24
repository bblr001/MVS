// MTITip.h: interface for the CMTITip class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

class CMTITip:public CWnd
{
public:
	void Show(CString szText, CPoint *pt);
	CMTITip();
	BOOL Create(CWnd* pParentWnd);
	void Hide() { 
		KillTimer(m_nTimer);
		ShowWindow(SW_HIDE);
	};
	// Sets the delay for the tooltip
	void SetShowDelay(int nDelay) { m_nShowDelay = nDelay; };

	void SetIcon(HICON hIcon);

	// Sets the tooltip font
	void SetFont(CFont *pFont) 
	{ 
		m_pFont = pFont; 
		if (IsWindow(m_hWnd))
			RedrawWindow();
	};
	virtual ~CMTITip();
protected:
	BOOL GetWindowRegion(CDC *pDC, HRGN* hRegion, CSize* Size = NULL);
protected:	
		// Timer identifiers
	enum
	{
		timerShow			= 100,								// Show timer
		timerHide			= 101								// Hide timer
	};
	LPCTSTR		m_szClass;										// Window class
	int			m_nShowDelay;									// Show delay
	CPoint		m_ptOrigin;										// Popup origin
	CString		m_szText;										// Tip text
	UINT		m_nTimer;										// Show/hide timer
	HICON		m_hIcon;										// Tip icon
	CSize		m_IconSize;										// Tip icon size
	CFont		*m_pFont;										// Tip font	
protected:
	//{{AFX_MSG(CMTITip)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

