// WarningDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WarningDlg.h"
#include "TLog.h"

// CWarningDlg 对话框

IMPLEMENT_DYNAMIC(CWarningDlg, CDialog)

CWarningDlg::CWarningDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWarningDlg::IDD, pParent)
{


}
BOOL CWarningDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
#ifdef _ENGLISH
	m_SelectedWarning.InsertString(0,_T("Hardware/Device Problem"));
	m_SelectedWarning.InsertString(1,_T("Software Problem"));
	m_SelectedWarning.InsertString(2,_T("Light Source Problem"));
	m_SelectedWarning.InsertString(3,_T("Other"));
#else
	m_SelectedWarning.InsertString(0,_T("生产设备问题"));
	m_SelectedWarning.InsertString(1,_T("软件问题"));
	m_SelectedWarning.InsertString(2,_T("光源问题"));
	m_SelectedWarning.InsertString(3,_T("其它"));
#endif

	m_SelectedWarning.SetCurSel(0);
	return TRUE;

}

CWarningDlg::~CWarningDlg()
{
}

void CWarningDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_WARNING, m_SelectedWarning);
}


BEGIN_MESSAGE_MAP(CWarningDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CWarningDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CWarningDlg 消息处理程序

void CWarningDlg::OnBnClickedOk()
{
	CString msg;
	msg.Format(_T("Close Alarm. select is  %d"),m_SelectedWarning.GetCurSel());
	TLOG_WARNING(msg);
	OnOK();
}
