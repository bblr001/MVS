// ProSetRejectTab.cpp : 实现文件
//

#include "stdafx.h"
#include "AOIEditVer3.h"
#include "ProSetRejectTab.h"
#include "MConfigCenter.h"

// CProSetRejectTab 对话框

IMPLEMENT_DYNAMIC(CProSetRejectTab, CPropertyPage)

CProSetRejectTab::CProSetRejectTab()
	: CPropertyPage(CProSetRejectTab::IDD)
{

}

CProSetRejectTab::~CProSetRejectTab()
{
}

void CProSetRejectTab::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_REJECT, m_RejectEnable);
	DDX_Control(pDX, IDC_EDIT_REJECTPORT, m_RejectPort);

	DDX_Control(pDX, IDC_EDIT_DELAYTIME, m_DelayTime);
	DDX_Control(pDX, IDC_EDIT_SIGNELTIME, m_SignelTime);
	DDX_Control(pDX, IDC_EDIT_NGCOUNT, m_NGCount);
	DDX_Control(pDX, IDC_EDIT_WINNERPORT, m_RedWinnerPort);
	DDX_Control(pDX, IDC_EDIT_STATEPORT, m_bStatePort);
}

BEGIN_MESSAGE_MAP(CProSetRejectTab, CPropertyPage)
	ON_BN_CLICKED(IDC_CHECK_REJECT, &CProSetRejectTab::OnBnClickedCheckReject)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

BOOL CProSetRejectTab::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	CString value;

	auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();

	if(pConfigCenter->GetRejectMode())
	{
		m_RejectEnable.SetCheck(BST_CHECKED);
		m_RejectPort.EnableWindow(TRUE);
		value.Format(_T("%d"),pConfigCenter->GetRejectPort());
		m_RejectPort.SetWindowText(value);
	}
	else
	{
		m_RejectEnable.SetCheck(BST_UNCHECKED);
		m_RejectPort.EnableWindow(FALSE);
	}

	value.Format(_T("%d"),pConfigCenter->GetRPort());
	m_RedWinnerPort.SetWindowText(value);


	value.Format(_T("%d"),pConfigCenter->GetGPort());
	m_bStatePort.SetWindowText(value);

	value.Format(_T("%d"),pConfigCenter->GetAlarmThreshold());
	m_NGCount.SetWindowText(value);

	m_DelayTime.EnableWindow(TRUE);
	int nTimeInterval = pConfigCenter->GetTimeInterval();
	value.Format(_T("%d"), nTimeInterval);
	m_DelayTime.SetWindowText(value);

	return TRUE;
}

void CProSetRejectTab::OnBnClickedButtonTest()
{
}

void CProSetRejectTab::OnBnClickedCheckReject()
{
	if(m_RejectEnable.GetCheck()   ==   BST_CHECKED) 
	{
		m_RejectPort.EnableWindow(TRUE);
	}
	else
	{
		m_RejectPort.EnableWindow(FALSE);
	}
}

BOOL CProSetRejectTab::OnBnClickedMyOk()
{
	auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();
	CString value;
 	if(m_RejectEnable.GetCheck()   ==   BST_CHECKED) 
 	{
 		pConfigCenter->SetRejectMode(TRUE);
 		m_RejectPort.GetWindowText(value);
 		pConfigCenter->SetRejectPort(_wtoi(value));
 	}
 	else
 	{
 		pConfigCenter->SetRejectMode(FALSE);
 	}

	m_RedWinnerPort.GetWindowText(value);	
	pConfigCenter->SetRPort(_wtoi(value));

	m_bStatePort.GetWindowText(value);	
	pConfigCenter->SetGPort(_wtoi(value));

	m_NGCount.GetWindowText(value);	
	pConfigCenter->SetAlarmThreshold(_wtoi(value));

	m_DelayTime.GetWindowText(value);
	pConfigCenter->SetTimeInterval(_wtoi(value));

	//m_DelaySingleCounts.GetWindowText(value);
	//pConfigCenter->SetEncoderDelaySingleCounts(_wtoi(value));

	return TRUE;
	 
}
