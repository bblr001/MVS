#include "stdafx.h"
#include "UserAddIn.h"
#include  "DBSQLite.h"
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserAddIn dialog
#define NUM_COLUMNS 4
static _TCHAR *_gszColumnLabel[NUM_COLUMNS] =
{
	_T("UserId"), _T("UserName"), _T("Group"), _T("Status")
};
static int _gnColumnFmt[NUM_COLUMNS] =
{
	LVCFMT_CENTER, LVCFMT_CENTER, LVCFMT_CENTER, LVCFMT_CENTER
};

static int _gnColumnWidth[NUM_COLUMNS] =
{
	80, 100, 100, 100
};
CUserAddIn::CUserAddIn() : CPropertyPage(CUserAddIn::IDD)
{
	//{{AFX_DATA_INIT(CUserAddIn)
	//}}AFX_DATA_INIT
}
CUserAddIn::~CUserAddIn()
{
	free(rst);
}
BOOL CUserAddIn::PreCreateWindow(CREATESTRUCT& cs)
{
	// default is report view and full row selection
	return(CPropertyPage::PreCreateWindow(cs));
}
void CUserAddIn::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserAddIn)

	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_USERINFO, m_userinfo);
}
BOOL CUserAddIn::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	UpdateData(TRUE);
	m_StateImageList.Create(IDB_STATEICONS, 16, 1, RGB(255, 0, 0));
	m_userinfo.SetImageList(&m_StateImageList, LVSIL_STATE);
	ModifyHeaderItems();
	FillListCtrl();
    DWORD style=m_userinfo.GetExtendedStyle();
	m_userinfo.SetExtendedStyle(style|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_OWNERDRAWFIXED);
	return TRUE;
}
void CUserAddIn::FillListCtrl()
{
	LV_ITEM lvi;
	int colnum = 4;
	m_userinfo.DeleteAllItems();
	char * query = "select USERID,USERNAME,(select groupname from usergroup where groupid = USERGROUPID) gName,STATUS from user ";
    rst = CDbsource::GetDB().GerResult(query,colnum);
    int i = 0;
	for(list<CString>::iterator It=rst->begin();It!=rst->end();It++)
	{
		lvi.mask = LVIF_TEXT | LVIF_STATE;
		lvi.iItem = i;
		lvi.iSubItem = 0;
		lvi.pszText = (*It).GetBuffer((*It).GetLength());
		lvi.stateMask = LVIS_STATEIMAGEMASK;
		lvi.state = INDEXTOSTATEIMAGEMASK(1);
		m_userinfo.InsertItem(&lvi);
		for(int j = 1; j<colnum; j++)
		{
			m_userinfo.SetItemText(i,j,(LPCTSTR)*(++It));
		}
		i++;
	}
}

void CUserAddIn::ModifyHeaderItems()
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

BEGIN_MESSAGE_MAP(CUserAddIn, CPropertyPage)
	//{{AFX_MSG_MAP(CUserAddIn)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CONFIRM, &CUserAddIn::OnBnClickedConfirm)
	ON_BN_CLICKED(IDC_CANCEL, &CUserAddIn::OnBnClickedCancel)
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CUserAddIn message handlers
void CUserAddIn::OnBnClickedConfirm()
{
	// TODO: 在此添加控件通知处理程序代码
	char sqlbuf[512];
	CString msg;
	CString userId;
	this->GetDlgItemTextW(IDC_ID,userId);
	CString status;
	this->GetDlgItemTextW(IDC_STATUS,status);
	CString userName;
	this->GetDlgItemTextW(IDC_NAME,userName);
	CString psw;
	this->GetDlgItemTextW(IDC_PSW,psw);
	string str_userId  = WChar2Ansi((LPCWSTR)userId);
	string str_userNm  = WChar2Ansi((LPCWSTR)userName);
	string str_status  = WChar2Ansi((LPCWSTR)status);
	string str_psw     = WChar2Ansi((LPCWSTR)psw);
	if(str_psw=="")
	{
	 this->MessageBox(_T("请设置密码!"));
	 return ;
	}
	str_status = str_status=="Y"?"Y":"N";
	sprintf_s(sqlbuf, "select * from user  where userid = %s ",str_userId.c_str());
	list<CString>* rst = CDbsource::GetDB().GerResult(sqlbuf,1);
	if(rst->empty())
	{//insert
      	sprintf_s(sqlbuf, "insert into user values(%s,'%s',1,'%s','%s') ",str_userId.c_str(),str_userNm.c_str(),str_status.c_str(),str_psw.c_str());
	    msg = "新增用户";
	}
	else
	{//update
      	sprintf_s(sqlbuf, "update user set username = '%s' , status = '%s' , password = '%s' where userid = %s  ",str_userNm.c_str(),str_status.c_str(),str_psw.c_str(),str_userId.c_str());
	    msg = "更新用户";
	}
	if(CDbsource::GetDB().Update(sqlbuf))
	{
		this->MessageBox(msg+_T("成功!"));
	    FillListCtrl();
		SetDlgItemTextW(IDC_ID,_T(""));
		SetDlgItemTextW(IDC_PSW,_T(""));
		SetDlgItemTextW(IDC_NAME,_T(""));
		usrmanage->FillListCtrl();
	}
}

void CUserAddIn::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	char sqlbuf[512];
	CString msg;
	CString userId;
	this->GetDlgItemTextW(IDC_ID,userId);
	string str_userId  = WChar2Ansi((LPCWSTR)userId);
	CString psw;
	this->GetDlgItemTextW(IDC_PSW,psw);
    string str_psw     = WChar2Ansi((LPCWSTR)psw);
	if(str_psw=="")
	{
		this->MessageBox(_T("请设置密码!"));
		return ;
	}

	if(str_psw=="")
	{
		this->MessageBox(_T("请设置密码!"));
		return ;
	}
	if (str_userId=="1")
	{
		AfxMessageBox(_T("不能删除管理员"));
		return;
	}
	sprintf_s(sqlbuf, "delete from user  where userid = %s and password = '%s' ",str_userId.c_str(),str_psw.c_str());
	if(this->MessageBox(_T("确定删除此用户吗?"),_T("提示"),MB_OKCANCEL)==IDOK&&CDbsource::GetDB().Update(sqlbuf))
	{
		this->MessageBox(_T("操作成功!"));
	    FillListCtrl();
		usrmanage->FillListCtrl();
		this->usrmanage->Invalidate();
	}
}
