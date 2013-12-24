// UserManager.h : header file
#include "Resource.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "MyListCtrl.h"
//#include "UserManagePage.h"
#include  <list>
#include <vector>
#include <string>

using namespace std;

struct UserInfo
{
	size_t m_nIndex;
	CString m_strUsername;
	CString m_strGroupName;
};

class CUserManagePage;
class CUserManager : public CPropertyPage
{
public:
	CUserManager();
	~CUserManager();
    // Dialog Data
	//{{AFX_DATA(CStylePage)
	enum { IDD = IDD_USERMANAGER};
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
	//CUserManagePage * usrmanage;
	CMyListCtrl m_userinfo;
	std::list<CString> rst;
	CImageList m_StateImageList;
	CString   userId;
	afx_msg void OnBnClickedModification();
	afx_msg void OnBnClickedButtonDelete();
	CComboBox m_ComboGroup;

	std::vector<UserInfo> m_vUserInfo;
	afx_msg void OnBnClickedButtonCreate();

private:
	void CleanupAllEditBoxes()
	{
		//Cleanup all the edit boxes
		SetDlgItemText(IDC_ID, _T(""));
		SetDlgItemText(IDC_NAME, _T(""));
		SetDlgItemText(IDC_PSW,_T(""));
		CComboBox *com =(CComboBox *)GetDlgItem(IDC_COMBO_GROUP);
		com->SetCurSel(3);
	}
};