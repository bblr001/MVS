// UserAddIn.h : header file
#include "Resource.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "MyListCtrl.h"
#include "UserManagePage.h"
#include  "list"
class CUserManagePage;
class CUserAddIn : public CPropertyPage
{
public:
	CUserAddIn();
	~CUserAddIn();
    // Dialog Data
	//{{AFX_DATA(CStylePage)
	enum { IDD = IDD_USERADDIN };
	//}}AFX_DATA
	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CStylePage)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	void ModifyHeaderItems();
	void FillListCtrl(); 
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
	CUserManagePage * usrmanage;
	CMyListCtrl m_userinfo;
	std::list<CString> * rst;
	CImageList m_StateImageList;
	CString   userId;
	afx_msg void OnBnClickedConfirm();
	afx_msg void OnBnClickedCancel();
};