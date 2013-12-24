#pragma once
class MyComboBox:public CComboBox
{
	// Construction
public:
	MyComboBox();

	// Attributes
public:
	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MyComboBox)
	//}}AFX_VIRTUAL

	// Implementation
public:
	VOID SetTxtFont(int height,int weight);
	VOID ClearColor();
	VOID SetColor(COLORREF Color,COLORREF BgColor);
	virtual ~MyComboBox();
	// Generated message map functions
protected:
	CString  m_strText;
	BOOL	 m_bOver;
	BOOL	 m_bIsColor;
	COLORREF m_Color;
	COLORREF m_BgColor;
	int m_iTxtHeight;
	int m_iTxtWeight;
	//{{AFX_MSG(MyComboBox)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};