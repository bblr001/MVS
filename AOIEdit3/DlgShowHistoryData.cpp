// DlgShowHistoryData.cpp : implementation file
//

#include "stdafx.h"
#include "AOIEdit.h"
#include "DlgShowHistoryData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgShowHistoryData dialog


CDlgShowHistoryData::CDlgShowHistoryData(CWnd* pParent /*=NULL*/)
: CDialog(CDlgShowHistoryData::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgShowHistoryData)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgShowHistoryData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgShowHistoryData)
	// NOTE: the ClassWizard will add DDX and DDV calls here

	//}}AFX_DATA_MAP
}

int CDlgShowHistoryData::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CRect Rt;
	GetClientRect(&Rt);
	m_gridListVw.Create(NULL,Rt,this,IDD_SHOWGRID);
	m_gridListVw.ShowWindow(SW_SHOWNORMAL);
	return CDialog::OnCreate(lpCreateStruct);
}
BEGIN_MESSAGE_MAP(CDlgShowHistoryData, CDialog)
	//{{AFX_MSG_MAP(CDlgShowHistoryData)
	// NOTE: the ClassWizard will add message map macros here
		ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgShowHistoryData message handlers
