// UserManagePage.h : header file
#if !defined(AFX_ListHdrDLG_H__31281828_D350_11D0_8286_00C04FD73634__INCLUDED_)
#define AFX_ListHdrDLG_H__31281828_D350_11D0_8286_00C04FD73634__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include "MyListCtrl.h"
#include "Resource.h"
#include "UserManagePage.h"
#include <list>
class CUserManagePage : public CPropertyPage
{
	// Construction 
public:
    CUserManagePage();
   ~CUserManagePage();
	// Dialog Data
	//{{AFX_DATA(CUserManagePage)
	enum{ IDD = IDD_USERMANAGE };
	//}}AFX_DATA
	CMyListCtrl m_listctrl;
	CComboBox     m_box_role;
	CComboBox     m_box_user;
	CStatic       m_msg;
	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CUserManagePage)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL
	// Implementation
protected:
	void ModifyHeaderItems();
public:
	void FillListCtrl();

	// Generated message map functions
	//{{AFX_MSG(CListHdrDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedConfirm();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ListHdrDLG_H__31281828_D350_11D0_8286_00C04FD73634__INCLUDED_)