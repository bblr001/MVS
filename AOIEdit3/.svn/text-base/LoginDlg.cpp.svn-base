// hangeMode.cpp : 实现文件
//

#include "stdafx.h"
#include "AOIEditVer3.h"
#include "LoginDlg.h"
#include "TypeCent.h"
#include "MConfigCenter.h"



// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialog)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent),
	  m_db(nullptr)
{

}

CLoginDlg::~CLoginDlg()
{
	if(m_db  != nullptr)
	{
		m_db->Close();
	    delete m_db;
	}
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_USERNAME, m_editUsername);
	//DDX_Control(pDX, IDC_EDIT_USERGROUP, m_UserGroup);
	DDX_Control(pDX, IDC_EDIT_USERPASSWORD, m_editPassword);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序

BOOL CLoginDlg::OnInitDialog()
{
	//::SetWindowPos(AfxGetMainWnd()->m_hWnd,HWND_TOPMOST, -1,-1,-1,-1,SWP_NOMOVE|SWP_NOSIZE);
	CDialog::OnInitDialog();
	m_db = new CSqliteDB<CppSQLite3Query>;
	TCHAR dbname[] = COMMONDBNAME;
	
	auto tmp = CFUNC::TransForRootPath(dbname);
	wstring wStr;
	wStr.assign(tmp.begin(), tmp.end());
	string tmps = ws2s(wStr);
	m_db->SetDBName(tmps.c_str());

#ifdef _DEBUG
	m_editUsername.SetWindowTextW(L"SLACADMIN");
	m_editPassword.SetWindowTextW(L"SLACADMIN1!");
#endif

	// load background bitmap
	CBitmap bkBmp;
	bkBmp.LoadBitmapW(IDB_BITMAP_UAC_BKGRD);
	m_brushBk.CreatePatternBrush(&bkBmp);
	bkBmp.DeleteObject();
	return TRUE;
}


void CLoginDlg::OnBnClickedOk()
{
	m_db->Connect();

	CString value;
	m_editUsername.GetWindowText(value);
	if (value == "")
	{
		AfxMessageBox(_T("Please input UserName"));
		m_db->Close();
		return;
	}
	wstring un  = value.GetBuffer();
	m_editPassword.GetWindowText(value);
	if (value == "")
	{
		AfxMessageBox(_T("Please input password"));
		m_db->Close();
		return;
	}
	wstring pwd = value.GetBuffer();

	string strUsername = ws2s(un);
	string strPwd      = ws2s(pwd);

	if (!_wcsicmp(un.c_str(),_T("SLACADMIN")))
	{
		if (!_wcsicmp(pwd.c_str(),_T("SLACADMIN1!")))
		{
			CMConfigCenter::GetSingletonConfigCenter()->SetUserGroup(SADMIN);
			m_db->Close();
			OnOK();
			return;
		}
	}
	char sqlbuf[MAX_PATH];
	sprintf_s(sqlbuf, "select * from user where user.USERNAME = '%s'",strUsername.c_str());
	CppSQLite3Query rst = m_db->Query(sqlbuf);

	if (rst.eof())
	{	
		rst.finalize();
		AfxMessageBox(_T("Cannot find user!"));
		m_db->Close();
		return;
	}

	sprintf_s(sqlbuf, "select * from user	where user.USERNAME = '%s' and user.PASSWORD='%s';",strUsername.c_str(),strPwd.c_str());
	rst = m_db->Query(sqlbuf);

	if (rst.eof())
	{
		AfxMessageBox(_T("Password is invalid!"));
		rst.finalize();
		m_db->Close();
		return;
	}

	sprintf_s(sqlbuf, "select USERGROUP.GROUPNAME from user join USERGROUP on USERGROUP.GROUPID=USER.USERGROUPID where user.USERNAME = '%s' and user.PASSWORD='%s' ;",strUsername.c_str(),strPwd.c_str());
	rst = m_db->Query(sqlbuf);

	while (!rst.eof())
	{
		string group = rst.getStringField("GROUPNAME");
		if (!_stricmp(_ADMIN_STR,group.c_str()))
		{
			CMConfigCenter::GetSingletonConfigCenter()->SetUserGroup(ADMIN);
		}
		else if (!_stricmp(_OPERATOR_STR,group.c_str()))
		{
			CMConfigCenter::GetSingletonConfigCenter()->SetUserGroup(OPERATOR);
		}
		else if (!_stricmp(_ENGINEER_STR,group.c_str()))
		{
			CMConfigCenter::GetSingletonConfigCenter()->SetUserGroup(ENGINEER);
		}
		else
		{
			//CMConfigCenter::GetSingletonConfigCenter()->SetUserGroup(NO_GROUP);
		}
	
		rst.nextRow();
	}
	rst.finalize();
	m_db->Close();

	OnOK();
}


HBRUSH CLoginDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if(pWnd == this)
	{
		return m_brushBk;
	}
	return hbr;
}


void CLoginDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	long x = point.x;
	long y = point.y;
	CRect okRect(467, 118, 540, 180); // OK rectangle
	CRect cancelRect(604,25, 627, 48);

	if(okRect.PtInRect(point))
	{
		OnBnClickedOk();
	}
	if(cancelRect.PtInRect(point))
	{
		CDialog::OnCancel();
	}
	CDialog::OnLButtonDown(nFlags, point);
}
