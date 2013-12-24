// UserAddIn.h : header file
#include "Resource.h"
#include "afxwin.h"
#include "afxcmn.h"
#include  "list"
#ifndef __GROUPADDIN__
#define __GROUPADDIN__
class CGroupAddIn : public CPropertyPage
{
public:
	CGroupAddIn();
	~CGroupAddIn();
    // Dialog Data
	//{{AFX_DATA(CStylePage)
	enum { IDD = IDD_GROUP };
	//}}AFX_DATA
	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CStylePage)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
// Attributes
public:
// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CStylePage)
	virtual BOOL OnInitDialog();
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CListBox m_lbGroup;
	std::list<CString> * rst;
};
#endif