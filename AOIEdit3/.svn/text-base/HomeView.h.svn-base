#if !defined(AFX_HOMEVIEW_H__0208450D_FB06_4F58_A083_080FA0D61D67__INCLUDED_)
#define AFX_HOMEVIEW_H__0208450D_FB06_4F58_A083_080FA0D61D67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CHomeFormView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHomeFormView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include "resource.h"
#include "MConfigCenter.h"
#include "MCtrlCenter.h"
class CHomeFormView : public CFormView
{
protected:
	//CHomeFormView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CHomeFormView)

	// Form Data
public:
	CHomeFormView();   
	enum { IDD = IDD_HOMEVIEW };

	void OnInitialUpdate();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual ~CHomeFormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	DECLARE_MESSAGE_MAP()

private:
	CMConfigCenter* m_pConfigCenter;
	CMCtrlCenter*   m_pCtrlCenter;
	double m_dRatio;
public:
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEXTFORMVIEW_H__0208450D_FB06_4F58_A083_080FA0D61D67__INCLUDED_)
