#include "stdafx.h"
#include "UserManager.h"
#include  "DBSQLite.h"
#include <iostream>
#include <sstream>
#include <atlconv.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

using namespace std;
/////////////////////////////////////////////////////////////////////////////
// CUserManager dialog
const int  NUM_COLUMNS = 3;
static _TCHAR *_gszColumnLabel[NUM_COLUMNS] =
{
#ifdef _ENGLISH
	_T("Index"), _T("Userame"), _T("Group")
#else
	_T("序号"), _T("用户名"), _T("群组")
#endif
};
static int _gnColumnFmt[NUM_COLUMNS] =
{
	LVCFMT_CENTER, LVCFMT_LEFT, LVCFMT_LEFT
};

static int _gnColumnWidth[NUM_COLUMNS] =
{
	80, 100, 100
};
CUserManager::CUserManager() : CPropertyPage(CUserManager::IDD)
{
	//{{AFX_DATA_INIT(CUserManager)

	//}}AFX_DATA_INIT
}
CUserManager::~CUserManager()
{
	//free(rst);
}
BOOL CUserManager::PreCreateWindow(CREATESTRUCT& cs)
{
	// default is report view and full row selection
	return(CPropertyPage::PreCreateWindow(cs));
}
void CUserManager::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_USERINFO, m_userinfo);
	DDX_Control(pDX, IDC_COMBO_GROUP, m_ComboGroup);
	
}
BOOL CUserManager::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	UpdateData(TRUE);
	m_StateImageList.Create(IDB_STATEICONS, 16, 1, RGB(255, 0, 0));
	m_userinfo.SetImageList(&m_StateImageList, LVSIL_STATE);
	ModifyHeaderItems();
	FillListCtrl();
    DWORD style=m_userinfo.GetExtendedStyle();
	m_userinfo.SetExtendedStyle(style|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_OWNERDRAWFIXED);

	GetDlgItem(IDC_MODIFICATION)->EnableWindow(FALSE);
	GetDlgItem(IDC_DELETE)->EnableWindow(FALSE);

	return TRUE;
}
void CUserManager::FillListCtrl()
{
	LV_ITEM lvi;
	m_vUserInfo.clear();
	m_userinfo.DeleteAllItems();
	char * query = "select USERID,USERNAME,(select groupname from usergroup where groupid = USERGROUPID) gName,USERGROUPID from user ";
    rst = CDbsource::GetDB().GetResult(query,NUM_COLUMNS);
    int i = 0;
	for(list<CString>::iterator It=rst.begin();It!=rst.end();It++)
	{
		lvi.mask = LVIF_TEXT | LVIF_STATE;
		lvi.iItem = i;
		lvi.iSubItem = 0;
		lvi.pszText = (*It).GetBuffer((*It).GetLength());
		lvi.stateMask = LVIS_STATEIMAGEMASK;
		lvi.state = INDEXTOSTATEIMAGEMASK(1);
		m_userinfo.InsertItem(&lvi);
		UserInfo userInfo;
		userInfo.m_nIndex = i;
		for(int j = 1; j < NUM_COLUMNS; j++)
		{
			if(j == 1)
			{
				userInfo.m_strUsername = (LPCTSTR)*(++It);
			}
			if(j == 2)
			{
				userInfo.m_strGroupName = (LPCTSTR)*(++It);
			}
			m_userinfo.SetItemText(i,j,(LPCTSTR)*(It));
		}

		m_vUserInfo.push_back(userInfo);
		i++;
	}

	CString item;
	item.Format(_T("%d"),i+1);

	lvi.mask = LVIF_TEXT | LVIF_STATE;
	lvi.iItem = i;
	lvi.iSubItem = 0;
	lvi.pszText = item.GetBuffer();
	lvi.stateMask = LVIS_STATEIMAGEMASK;
	lvi.state = INDEXTOSTATEIMAGEMASK(1);

	int colnum = 1;
	query  = "select USERGROUP.GROUPNAME from  USERGROUP";
	rst = CDbsource::GetDB().GetResult(query,colnum);
	m_ComboGroup.ResetContent();
	
	for(list<CString>::iterator It=rst.begin();It!=rst.end();It++)
	{
		m_ComboGroup.AddString((LPCTSTR)*It);
	}
	m_ComboGroup.SetCurSel(3);
}

void CUserManager::ModifyHeaderItems()
{
	int i;
	LV_COLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	for(i = 0; i<NUM_COLUMNS; i++)
	{
		lvc.iSubItem = i;
		lvc.pszText = _gszColumnLabel[i];
		lvc.cx = _gnColumnWidth[i];
		lvc.fmt = _gnColumnFmt[i];
		m_userinfo.InsertColumn(i,&lvc);
	}
}

BEGIN_MESSAGE_MAP(CUserManager, CPropertyPage)
	ON_BN_CLICKED(IDC_MODIFICATION, &CUserManager::OnBnClickedModification)
	ON_BN_CLICKED(IDC_DELETE, &CUserManager::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_CREATE, &CUserManager::OnBnClickedButtonCreate)
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CUserManager message handlers
void CUserManager::OnBnClickedModification()
{
	CString userName;
	this->GetDlgItemText(IDC_NAME,userName);
	if(userName.GetLength() <= 0)
 	{
#ifdef _ENGLISH
		 AfxMessageBox(_T("Please select a user!"));
#else
 		 AfxMessageBox(_T("选择用户!"));
#endif
 		 return ;
 	}
	CString userId;
	this->GetDlgItemText(IDC_ID,userId);

	CString psw;
	this->GetDlgItemText(IDC_PSW,psw);

	USES_CONVERSION;
	string str_userId  = T2CA(userId);
	string str_userNm  = T2CA(userName);
	string str_psw     = T2CA(psw);
	
	char sqlbuf[512];
	CString msg;
	sprintf_s(sqlbuf, "select * from user  where userid = %s ",str_userId.c_str());
	list<CString> rst = CDbsource::GetDB().GetResult(sqlbuf,1);
	if(rst.empty())
	{
#ifdef _ENGLISH
		msg.Format(_T("%s is not a valid user! Please click Create to add this user."), userName);
#else
		msg.Format(_T("%s不是一个有效的账户，请点击创建按钮创建此账户。"), userName);
#endif
		AfxMessageBox(msg);
		return ;
	}
	// Update an account
	// Group
	CComboBox* pCb =(CComboBox *)GetDlgItem(IDC_COMBO_GROUP);
	int index = pCb->GetCurSel();
	if(3 == index)
	{
#ifdef _ENGLISH
		AfxMessageBox(_T("Pleae select a group to which the user belong to."));
#else
		AfxMessageBox(_T("请选择用户组。"));
#endif
		return;
	}

	if(str_psw == "TESTTEST1!")
	{
		sprintf_s(sqlbuf, "update user set username = '%s' , status='Y',  usergroupid=%d where userid = %s  ",str_userNm.c_str(),m_ComboGroup.GetCurSel()+1,str_userId.c_str());
	}
	else
	{
		sprintf_s(sqlbuf, "update user set username = '%s' , status='Y' , password = '%s',usergroupid=%d where userid = %s  ",str_userNm.c_str(),str_psw.c_str(),m_ComboGroup.GetCurSel()+1,str_userId.c_str());
	}
#ifdef _ENGLISH
	msg = _T("Account is update successfully!");
#else
	msg = _T("更新用户成功！");
#endif
	if(CDbsource::GetDB().Update(sqlbuf))
	{
		AfxMessageBox(msg);
		FillListCtrl();
		CleanupAllEditBoxes();
		GetDlgItem(IDC_DELETE)->EnableWindow(FALSE);
		GetDlgItem(IDC_MODIFICATION)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_CREATE)->EnableWindow(TRUE);
	}
}

void CUserManager::OnBnClickedButtonDelete()
{ 
	CString userId;
	this->GetDlgItemText(IDC_ID,userId);
	USES_CONVERSION;
	string str_userId  = T2CA(userId);
	
	if (str_userId == "1")
	{
#ifdef _ENGLISH
		AfxMessageBox(_T("Administrator cannot be deleted"));
#else
		AfxMessageBox(_T("不能删除管理员"));
#endif
		return;
	}
	char sqlbuf[512];
	CString msg;
	sprintf_s(sqlbuf, "delete from user  where userid = %s ",str_userId.c_str());

#ifdef _ENGLISH
	CString strPrompt(_T("Delete this user?"));
	CString prompt(_T("Warning"));
#else
	CString strPrompt(_T("确定删除此用户吗?"));
	CString prompt(_T("提示"));
#endif
	
	if(AfxMessageBox(strPrompt,MB_OKCANCEL)==IDOK)
	{
		CDbsource::GetDB().Update(sqlbuf);

		int colnum = 1;
		char * query = "select userid from user";
		rst = CDbsource::GetDB().GetResult(query,colnum);
		int i = 1;
		for(list<CString>::iterator It=rst.begin();It!=rst.end();It++)
		{	
			wstring msg = (*It).GetBuffer();
			sprintf_s(sqlbuf, "update user set userid = %d where userid=%s",i++,ws2s(msg).c_str());
			CDbsource::GetDB().Update(sqlbuf);
		}
#ifdef _ENGLISH
		AfxMessageBox(_T("Deleted!"));
#else
		AfxMessageBox(_T("删除操作成功!"));
#endif
	    FillListCtrl();
        CleanupAllEditBoxes();
		GetDlgItem(IDC_DELETE)->EnableWindow(FALSE);
		GetDlgItem(IDC_MODIFICATION)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_CREATE)->EnableWindow(TRUE);
	}
}

void CUserManager::OnBnClickedButtonCreate()
{
	CString userName;
	this->GetDlgItemText(IDC_NAME,userName);
	if(userName.GetLength() <= 0)
 	{
#ifdef _ENGLISH
		 AfxMessageBox(_T("Please enter the username!"));
#else
 		 AfxMessageBox(_T("请输入用户名!"));
#endif
 		 return ;
 	}
	USES_CONVERSION;
	string str_userNm  = T2CA(userName);
	char sqlbuf[512];
	sprintf_s(sqlbuf, "select * from user  where username = \'%s\' ",str_userNm.c_str());
	list<CString> rst = CDbsource::GetDB().GetResult(sqlbuf,2);
	if(!rst.empty())
	{
#ifdef _ENGLISH
		AfxMessageBox(_T("The username is existed!"));
#else
		AfxMessageBox(_T("用户名已经存在！"));
#endif
		return;
	}

	// password
	CString psw;
	this->GetDlgItemText(IDC_PSW, psw);
	if(psw.GetLength() <= 0)
	{
#ifdef _ENGLISH
		AfxMessageBox(_T("Please enter the password!"));
#else
		AfxMessageBox(_T("请输入密码！"));
#endif
		return;
	}

	// Group
	CComboBox* pCb =(CComboBox *)GetDlgItem(IDC_COMBO_GROUP);
	int index = pCb->GetCurSel();
	if(3 == index)
	{
#ifdef _ENGLISH
		AfxMessageBox(_T("Pleae select a group to which the user belong to."));
#else
		AfxMessageBox(_T("请选择用户组。"));
#endif
		return;
	}

	string   str_psw = T2CA(psw);
	int id =  m_vUserInfo.size() + 1;
	std::ostringstream oss;
	oss << id;
	string str_userId = oss.str();

    sprintf_s(sqlbuf, "insert into user values(%s,'%s','%d','%s','%s') ",str_userId.c_str(),str_userNm.c_str(),m_ComboGroup.GetCurSel()+1,"Y",str_psw.c_str());
	if(CDbsource::GetDB().Update(sqlbuf))
	{
#ifdef _ENGLISH
		AfxMessageBox(_T("New user is added!"));
#else
		AfxMessageBox(_T("添加用户成功！"));
#endif
	}
	
	FillListCtrl();
    CleanupAllEditBoxes();
}
