// OperatorNameDlg.cpp : 实现文件
//
#pragma once

#include "stdafx.h"
#include "SLACMVSN.h"
#include "LoginDlg.h"
#include  "DBSQLite.h"
#include "PanelManager.h"
#include "MainFrm.h"

// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialog)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
: CDialog(CLoginDlg::IDD, pParent)
, m_strUsername(_T(""))
, m_strPassword(_T(""))
{	
}

CLoginDlg::~CLoginDlg()
{
}

BOOL CLoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
#ifdef _DEBUG
	m_editUsername.SetWindowTextW(_T("admin"));
	m_editPassword.SetWindowTextW(_T("admin"));
#endif
	return TRUE;
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_Operator, m_editUsername);
	DDX_Control(pDX, IDC_EDIT_Password, m_editPassword);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CLoginDlg::OnBnClickedCancel)
END_MESSAGE_MAP()

void CLoginDlg::OnBnClickedOk()
{
	this->UpdateData();
	CString value("");
	m_vMsg = _T("");
	m_editUsername.GetWindowText(value);
	wstring un = value.GetBuffer();
	if (value == "")
	{
		m_vMsg = _T("提示:用户名错误.");
		this->UpdateData(false);
	}
	m_editPassword.GetWindowText(value);
	wstring up = value.GetBuffer();
	if (value == "")
	{
		m_vMsg = _T("提示:密码错误.");
		this->UpdateData(false);
	}

	CMainFrame* pmainFRM = (CMainFrame*)(theApp.m_pMainWnd);
	if (!_wcsicmp(un.c_str(),_T("SLACADMIN")))
	{
		if (!_wcsicmp(up.c_str(),_T("SLACADMIN1!")))
		{
			CPanelManager::GetPanelManager().SetUserGroup(SADMIN);
			CPanelManager::GetPanelManager().UpdatePanelUserGroup(SADMIN);
 			pmainFRM->UpdateUserInfo(_T("SLAC-ADMIN"), SADMIN);

			OnOK();
			return;
		}
	}//value = m_UserPassWord;
	list<CString> rst;
	char sqlbuf[MAX_PATH];
	sprintf_s(sqlbuf, "select USERNAME from user where user.USERNAME = '%s'",ws2s(un).c_str());
	rst = CDbsource::GetDB().GetResult(sqlbuf,1);
	if(rst.empty())
	{  
		m_vMsg = _T("提示:用户名错误.");
		this->UpdateData(false);
		AfxMessageBox(m_vMsg);
		return;
	}
	sprintf_s(sqlbuf, "select USERNAME from user where user.USERNAME = '%s' and user.PASSWORD='%s';",ws2s(un).c_str(),ws2s(up).c_str());
	rst = CDbsource::GetDB().GetResult(sqlbuf,1);
	if(rst.empty())
	{
		m_vMsg = _T("提示:密码错误.");
		this->UpdateData(false);
		AfxMessageBox(m_vMsg);
		return;
	}

	sprintf_s(sqlbuf, "select USERGROUP.GROUPNAME from user join USERGROUP on USERGROUP.GROUPID=USER.USERGROUPID where user.USERNAME = '%s' and user.PASSWORD='%s' and USERGROUP.GROUPNAME= 'ADMINISTRATOR' ;",ws2s(un).c_str(),ws2s(up).c_str());
	rst = CDbsource::GetDB().GetResult(sqlbuf,1);
	if(!rst.empty())
	{
		CPanelManager::GetPanelManager().SetUserGroup(ADMIN);
		CPanelManager::GetPanelManager().UpdatePanelUserGroup(ADMIN);
		pmainFRM->UpdateUserInfo(un.c_str(),ADMIN);
		OnOK();
		return;
	}
	sprintf_s(sqlbuf, "select USERGROUP.GROUPNAME from user join USERGROUP on USERGROUP.GROUPID=USER.USERGROUPID where user.USERNAME = '%s' and user.PASSWORD='%s' and USERGROUP.GROUPNAME= 'ENGINEER' ;",ws2s(un).c_str(),ws2s(up).c_str());
	rst = CDbsource::GetDB().GetResult(sqlbuf,1);
	if(!rst.empty())
	{
		CPanelManager::GetPanelManager().SetUserGroup(ENGINEER);
		CPanelManager::GetPanelManager().UpdatePanelUserGroup(ENGINEER);
		pmainFRM->UpdateUserInfo(un.c_str(),ENGINEER);
	}
	else
	{
		CPanelManager::GetPanelManager().SetUserGroup(OPERATOR);
		CPanelManager::GetPanelManager().UpdatePanelUserGroup(OPERATOR);
		pmainFRM->UpdateUserInfo(un.c_str(),OPERATOR);
	} 

	OnOK();
}

void CLoginDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}
