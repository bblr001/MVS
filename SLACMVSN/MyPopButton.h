#if !defined(AFX_MYPOPBUTTON_H__22191FF6_F152_4F6A_B0C6_4960AED8D391__INCLUDED_)
#define AFX_MYPOPBUTTON_H__22191FF6_F152_4F6A_B0C6_4960AED8D391__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyPopButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyPopButton window

class CMyPopButton : public CBitmapButton
{
// Construction
public:
	CMyPopButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyPopButton)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyPopButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyPopButton)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg void OnClicked();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPOPBUTTON_H__22191FF6_F152_4F6A_B0C6_4960AED8D391__INCLUDED_)
