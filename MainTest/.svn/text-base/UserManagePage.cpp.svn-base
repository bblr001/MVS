
#include "stdafx.h"
#include "UserManagePage.h"
#include  "DBSQLite.h"
#include  "string"
//#include  "CppSQLite3.h"
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserManagePage property page
list<CString> * rst;
CUserManagePage::CUserManagePage()
	: CPropertyPage(CUserManagePage::IDD)
{
	rst = new list<CString>();
	//{{AFX_DATA_INIT(CUserManagePage)
	
	//}}AFX_DATA_INIT
}
CUserManagePage::~CUserManagePage()
{
	free(rst);
}
void CUserManagePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserManagePage)
	DDX_Control(pDX, IDC_LISTVIEW1, m_listctrl);
	DDX_Control(pDX, IDC_ROLE, m_box_role);
	DDX_Control(pDX, IDC_USER, m_box_user);
	DDX_Control(pDX, IDC_MSG, m_msg);
	//}}AFX_DATA_MAP
}
BEGIN_MESSAGE_MAP(CUserManagePage, CPropertyPage)
	//{{AFX_MSG_MAP(CUserManagePage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CONFIRM, &CUserManagePage::OnBnClickedConfirm)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserManagePage message handlers
BOOL CUserManagePage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	UpdateData(TRUE);
	ModifyHeaderItems();
	FillListCtrl();
	DWORD style=m_listctrl.GetExtendedStyle();
	m_listctrl.SetExtendedStyle(style|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	return TRUE;
}
void CUserManagePage::FillListCtrl()
{
	LV_ITEM lvi;
	int colnum = 2;
	m_listctrl.DeleteAllItems();
	char * query = "select USERNAME, USERGROUP.GROUPNAME from user join USERGROUP on USERGROUP.GROUPID=USER.USERGROUPID ";
    rst = CDbsource::GetDB().GerResult(query,colnum);
    int i = 0;
	m_box_user.ResetContent();
	for(list<CString>::iterator It=rst->begin();It!=rst->end();It++)
	{
		lvi.mask = LVIF_TEXT | LVIF_STATE;
		lvi.iItem = i;
		lvi.iSubItem = 0;
		lvi.pszText = (*It).GetBuffer((*It).GetLength());
		lvi.stateMask = LVIS_STATEIMAGEMASK;
		lvi.state = INDEXTOSTATEIMAGEMASK(1);
		m_listctrl.InsertItem(&lvi);
		m_box_user.AddString((LPCTSTR)*It);
		for(int j = 1; j<colnum; j++)
		{
			m_listctrl.SetItemText(i,j,(LPCTSTR)*(++It));
		}
		i++;
	}
	colnum = 1;
	query  = "select USERGROUP.GROUPNAME from  USERGROUP";
    rst = CDbsource::GetDB().GerResult(query,colnum);
	m_box_role.ResetContent();
	for(list<CString>::iterator It=rst->begin();It!=rst->end();It++)
	{
		m_box_role.AddString((LPCTSTR)*It);
	}
}

void CUserManagePage::ModifyHeaderItems()
{
	CRect           rect;
	CString         strItem1= _T("User");
	CString         strItem2= _T("Group");
	m_listctrl.GetWindowRect(&rect);
	m_listctrl.InsertColumn(0, strItem1, LVCFMT_LEFT,
		rect.Width() * 1/2, 0);
	m_listctrl.InsertColumn(1, strItem2, LVCFMT_LEFT,
		rect.Width() * 1/2 - 3, 1);
	HD_ITEM curItem;
	CHeaderCtrl* pHdrCtrl= NULL;
	pHdrCtrl= m_listctrl.GetHeaderCtrl();

	memset(&curItem, 0, sizeof(curItem));
	pHdrCtrl->GetItem(0, &curItem);
	curItem.mask= HDI_FORMAT;
	curItem.fmt= HDF_LEFT | HDF_STRING;
	pHdrCtrl->SetItem(0, &curItem);

	pHdrCtrl->GetItem(1, &curItem);
	curItem.mask=  HDI_FORMAT;
	curItem.fmt= HDF_LEFT | HDF_STRING;
	pHdrCtrl->SetItem(1, &curItem);
}

void CUserManagePage::OnBnClickedConfirm()
{
	// TODO: 在此添加控件通知处理程序代码
	char sqlbuf[512];
	CString groupname;
	m_box_role.GetWindowTextW(groupname);
	CString user;
	m_box_user.GetWindowTextW(user);
	string str_group = WChar2Ansi((LPCWSTR)groupname);
	string str_user  = WChar2Ansi((LPCWSTR)user);
	sprintf_s(sqlbuf, "update user set usergroupid = (select groupid from usergroup where groupname = '%s') where username = '%s'",str_group.c_str(),str_user.c_str());
	if(CDbsource::GetDB().Update(sqlbuf))
	{
	   ::SetDlgItemTextW(this->m_hWnd,IDC_MSG,_T("执行成功."));
	   FillListCtrl();
	}
}
