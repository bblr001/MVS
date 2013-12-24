#include "stdafx.h"
#include "GroupAddIn.h"
#include  "DBSQLite.h"

/////////////////////////////////////////////////////////////////////////////
// CGroupAddIn dialog
CGroupAddIn::CGroupAddIn() : CPropertyPage(CGroupAddIn::IDD)
{
	//{{AFX_DATA_INIT(CGroupAddIn)
	//}}AFX_DATA_INIT
}
CGroupAddIn::~CGroupAddIn()
{
	free(rst);
}
BOOL CGroupAddIn::PreCreateWindow(CREATESTRUCT& cs)
{
	// default is report view and full row selection
	return(CPropertyPage::PreCreateWindow(cs));
}
void CGroupAddIn::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGroupAddIn)

	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_GROUPINFO, m_lbGroup);
}
BOOL CGroupAddIn::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	UpdateData(TRUE);
	int colnum = 3;
	m_lbGroup.ResetContent();
	char * query = "select groupid,groupname,groupdes from usergroup ";
    rst = CDbsource::GetDB().GerResult(query,colnum);
    int i = 0;
	CString strGroupListInfo("");
	for(list<CString>::iterator It=rst->begin();It!=rst->end();It++)
	{
        strGroupListInfo=strGroupListInfo + "    " + *It;
		if(++i==3){m_lbGroup.AddString((LPCTSTR)strGroupListInfo);}
	}
	return TRUE;
}
BEGIN_MESSAGE_MAP(CGroupAddIn, CPropertyPage)
	//{{AFX_MSG_MAP(CGroupAddIn)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CGroupAddIn message handlers