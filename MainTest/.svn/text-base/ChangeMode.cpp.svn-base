// ChangeMode.cpp : 实现文件
//

#include "stdafx.h"
#include "MainTest.h"
#include "ChangeMode.h"
#include "MI_DataConfig.h"


// CChangeMode 对话框

IMPLEMENT_DYNAMIC(CChangeMode, CDialog)

CChangeMode::CChangeMode(CWnd* pParent /*=NULL*/)
	: CDialog(CChangeMode::IDD, pParent)
	, m_vMsg(_T(""))
{

}

CChangeMode::~CChangeMode()
{
}

void CChangeMode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_USERID, m_userid);
	DDX_Control(pDX, IDC_PSWD, m_pswd);
	DDX_Text(pDX, IDC_MSG, m_vMsg);
}

// CChangeMode 消息处理程序


BOOL CChangeMode::OnInitDialog()
{
	::SetWindowPos(AfxGetMainWnd()->m_hWnd,HWND_TOPMOST, -1,-1,-1,-1,SWP_NOMOVE|SWP_NOSIZE);
	CDialog::OnInitDialog();
	return TRUE;
}
BEGIN_MESSAGE_MAP(CChangeMode, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CChangeMode::OnBnClickedButton1)
END_MESSAGE_MAP()

void CChangeMode::OnBnClickedButton1()
{
	this->UpdateData();
	CString value("");
	m_userid.GetWindowText(value);
	wstring un=value.GetBuffer();
	if (value=="")
	{
		m_vMsg = _T("提示:请输入用户名.");
		this->UpdateData(false);
		return;
	}

	m_pswd.GetWindowText(value);
	wstring up = value.GetBuffer();
	if (value=="")
	{
		m_vMsg = _T("提示:请输入密码.");
		this->UpdateData(false);
		return;
	}
	if (!_wcsicmp(un.c_str(),_T("SLACADMIN")))
	{
		if (!_wcsicmp(up.c_str(),_T("SLACADMIN1!")))
		{
			CMI_DataConfig::GetDataConfig().SetUserGroup(SADMIN);
			OnOK();
			return;
		}
	}
	
	char sqlbuf[MAX_PATH];
	sprintf_s(sqlbuf, "select USERNAME from user where user.USERNAME = '%s'",ws2s(un).c_str());
	list<CString> rst = CDbsource::GetDB().GetResult(sqlbuf,1);
	if(rst.empty())
	{//insert	
		m_vMsg = _T("提示:用户名错误.");
		this->UpdateData(false);
		return;
	}
	sprintf_s(sqlbuf, "select USERNAME from user where user.USERNAME = '%s' and user.PASSWORD='%s';",ws2s(un).c_str(),ws2s(up).c_str());
	rst = CDbsource::GetDB().GetResult(sqlbuf,1);
	if(rst.empty())
	{
		m_vMsg = _T("提示:密码错误.");
		this->UpdateData(false);
		return;
	}

	sprintf_s(sqlbuf, "select USERGROUP.GROUPNAME from user join USERGROUP on USERGROUP.GROUPID=USER.USERGROUPID where user.USERNAME = '%s' and user.PASSWORD='%s' and USERGROUP.GROUPNAME= 'ADMINISTRATOR' ;",ws2s(un).c_str(),ws2s(up).c_str());
	rst = CDbsource::GetDB().GetResult(sqlbuf,1);
	if(!rst.empty())
	{
		CMI_DataConfig::GetDataConfig().SetUserGroup(ADMIN);
		OnOK();
		return;
	}

	sprintf_s(sqlbuf, "select USERGROUP.GROUPNAME from user join USERGROUP on USERGROUP.GROUPID=USER.USERGROUPID where user.USERNAME = '%s' and user.PASSWORD='%s' and USERGROUP.GROUPNAME= 'ENGINEER' ;",ws2s(un).c_str(),ws2s(up).c_str());
	rst = CDbsource::GetDB().GetResult(sqlbuf,1);
	if(!rst.empty())
	{
		CMI_DataConfig::GetDataConfig().SetUserGroup(ENGINEER);
		OnOK();
		return;
	}
	else
	{
		CMI_DataConfig::GetDataConfig().SetUserGroup(OPERATOR);
		OnOK();
		return;
	}
}
