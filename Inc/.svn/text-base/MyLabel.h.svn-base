#pragma once
#include "TypeCent.h"

struct ui_decorator;

class CMyLabel : public CStatic
{
// Construction
public:
	CMyLabel();

// Attributes
public:
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMTILabel)
	//}}AFX_VIRTUAL

// Implementation
public:
	VOID SetTxtFont(int height,int weight);
	VOID ClearColor();
	VOID SetColor(COLORREF Color,COLORREF BgColor);
	virtual ~CMyLabel();
	void UpdateSytemStatusSymbol(eMTI_GUI_STATE state);
	void SetPtr2UiDecorator(ui_decorator* ptrUiDecorator = nullptr);
	// Generated message map functions
protected:
	CString  m_strText;
	BOOL	 m_bOver;
	BOOL	 m_bIsColor;
	COLORREF m_Color;
	COLORREF m_BgColor;
	int m_iTxtHeight;
	int m_iTxtWeight;
	//{{AFX_MSG(CMTILabel)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CImage* m_ptrImage;
	ui_decorator* m_ptrUiDecorator;
};