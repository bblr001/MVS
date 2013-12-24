// ProSetCameraTab.cpp : 实现文件
//

#include "stdafx.h"
#include "AOIEditVer3.h"
#include "ProSetCameraTab.h"
#include "ProgramSettingDlg.h"
#include "MConfigCenter.h"
#include "MCtrlCenter.h"
#include <atlconv.h>


// CProSetCameraTab 对话框

IMPLEMENT_DYNAMIC(CProSetCameraTab, CPropertyPage)

CProSetCameraTab::CProSetCameraTab()
	: CPropertyPage(CProSetCameraTab::IDD),
	  m_pConfigCenter(CMConfigCenter::GetSingletonConfigCenter())
{
}

CProSetCameraTab::~CProSetCameraTab()
{
}

void CProSetCameraTab::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO_SOURE, m_ComboSource);
	DDX_Control(pDX, IDC_BUTTON_SCAN, m_BTScan);
	DDX_Control(pDX, IDC_CHECK_TRIGGER, m_TriggerMode);
	DDX_Control(pDX, IDC_COMBO_TraggerEdge, m_TraggerEdge);
	//DDX_Control(pDX, IDC_EDIT_TIME, m_ExposureTimeRaw);
	DDX_Control(pDX,IDC_EDIT_CAMERAGAIN,m_CameraGain);
	DDX_Control(pDX, IDC_CHECK_CONNECT_LIGHT_CTRL, m_bConnectLightCtrl);
	DDX_Control(pDX, IDC_EDIT_CAMERATRIGERDELAY, m_triggerDelayAbs);
#ifdef SHEET_INSPECTION
	DDX_Control(pDX, IDC_EDIT_LINE_PER_FRAME, m_linePerFrame);
	DDX_Control(pDX, IDC_EDIT_FRAME_PER_SHEET, m_framePerSheet);
#endif
}

BEGIN_MESSAGE_MAP(CProSetCameraTab, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_SCAN, &CProSetCameraTab::OnBnClickedButtonScan)
	ON_CBN_SELCHANGE(IDC_COMBO_SOURE,&CProSetCameraTab::OnCbnSelchangeComboSoure)
	ON_BN_CLICKED(IDOK, &CProgramSettingDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK_TRIGGER, &CProSetCameraTab::OnBnClickedCheckTrigger)

	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()
// CProSetCameraTab 消息处理程序

BOOL CProSetCameraTab::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_TraggerEdge.EnableWindow(FALSE);

	if(m_pConfigCenter->GetTriggerMode())
	{
		m_TriggerMode.SetCheck(BST_CHECKED);
		m_TraggerEdge.EnableWindow(TRUE);
	}
	else
	{
		m_TriggerMode.SetCheck(BST_UNCHECKED);
	}
	// Delete every item from the combo box.
	for (int i = m_ComboSource.GetCount ()-1; i >= 0; i--)
	{
		m_ComboSource.DeleteString (i);
	}
	m_ComboSource.Clear();
	CTlFactory *m_pTlFactory = &CTlFactory::GetInstance();

	DeviceInfoList_t m_devices;
	m_devices.clear ();
	m_pTlFactory->EnumerateDevices (m_devices);
	for (DeviceInfoList_t::iterator it = m_devices.begin (); it != m_devices.end(); it++)
	{
		string name=(*it).GetFriendlyName().c_str();
		if (m_pConfigCenter->GetCameraName() == name)
		{
			wstring wname = s2ws(name);
			m_ComboSource.AddString (wname.c_str());
		}
	}
	if (m_ComboSource.GetCount()==0)
	{
		if (m_pConfigCenter->GetImgSource()==CAMERA_SOURCE)
		{
			CString msg;
			msg.Format(_T("No Find Camera %s. please rescan"),(s2ws(m_pConfigCenter->GetCameraName())).c_str());
			AfxMessageBox(msg);
		}
	}
	m_ComboSource.SetCurSel (0);

	if (m_pConfigCenter->GetTriggerEdge()==RISING_EDGE)
		m_TraggerEdge.SetCurSel(0);
	else
		m_TraggerEdge.SetCurSel(1);

	// Restore the Camera Gain to UI
	unsigned int value = m_pConfigCenter->GetCameraGain();
	CString strValue;
	strValue.Format(_T("%d"), value);
	m_CameraGain.SetWindowText(strValue);

	value = m_pConfigCenter->GetTriggerDelayAbs();	
	strValue.Format(_T("%d"), value);
	m_triggerDelayAbs.SetWindowText(strValue);

#ifdef SHEET_INSPECTION
	value  = m_pConfigCenter->GetLineCountPerFrame();
	strValue.Format(_T("%d"), value);
	m_linePerFrame.SetWindowText(strValue);

	value = m_pConfigCenter->GetFrameCountPerSheet();
	strValue.Format(_T("%d"),value);
	m_framePerSheet.SetWindowText(strValue);
#endif

    UpdateCheckBox_LightCtrl();

	return TRUE;
}

void CProSetCameraTab::OnBnClickedButtonScan()
{
	CTlFactory *m_pTlFactory;
	// Get the transport layer factory
	m_pTlFactory = &CTlFactory::GetInstance();
	DeviceInfoList_t m_devices;
	m_devices.clear ();
	m_pTlFactory->EnumerateDevices (m_devices);
	// Delete every item from the combo box.
	for (int i = m_ComboSource.GetCount ()-1; i >= 0; i--)
	{
		m_ComboSource.DeleteString (i);
	}
	m_ComboSource.Clear();
	for (DeviceInfoList_t::iterator it = m_devices.begin (); it != m_devices.end(); it++)
	{
		CString name((*it).GetFriendlyName().c_str());
		m_ComboSource.AddString (name);
	}
	m_ComboSource.SetCurSel (0);
}

BOOL CProSetCameraTab::OnBnClickedOk()
{
	if (m_pConfigCenter->GetImgSource()!=CAMERA_SOURCE)
		return TRUE;

	if (m_ComboSource.GetCount()==0)
	{
		CString msg;
		msg.Format(_T("Cannot find Camera %s. please rescan"),(s2ws(m_pConfigCenter->GetCameraName())).c_str());
		AfxMessageBox(msg);
		return FALSE;
	}

	CString name;
	m_ComboSource.GetLBText(m_ComboSource.GetCurSel(),name);
	wstring wname = name;
	m_pConfigCenter->SetCameraName(ws2s(wname));
	m_pConfigCenter->SetImgSource(CAMERA_SOURCE);

	bool bChecked = (m_TriggerMode.GetCheck()==BST_CHECKED);
	m_pConfigCenter->SetTriggerMode(bChecked);

	if(bChecked) 
	{
		if (m_TraggerEdge.GetCurSel() == 0)
		{
			m_pConfigCenter->SetTriggerEdge(RISING_EDGE);
		}
		else
		{
			m_pConfigCenter->SetTriggerEdge(FALLING_EDGE);
		}
	}
	USES_CONVERSION;
	CString strValue;

	m_CameraGain.GetWindowText(strValue);
	m_pConfigCenter->SetCameraGain(_ttoi(T2CW(strValue)));

	m_triggerDelayAbs.GetWindowText(strValue);
	m_pConfigCenter->SetTriggerDelayAbs(_ttoi(T2CW(strValue)));

#ifdef SHEET_INSPECTION
	m_linePerFrame.GetWindowText(strValue);
	m_pConfigCenter->SetLineCountPerFrame(_ttoi(T2CW(strValue)));

	m_framePerSheet.GetWindowText(strValue);
	m_pConfigCenter->SetFrameCountPerSheet(_ttoi(T2CW(strValue)));
#endif

	// Connect to Light Controller and update the intensity value
	bChecked = (m_bConnectLightCtrl.GetCheck() == BST_CHECKED);
	m_pConfigCenter->SetConnect2LightCtrlFlag(bChecked);
	if(bChecked)
	{
		if(CMCtrlCenter::GetSingletonCtrlCenter()->m_VLproxy.TryConnectToUSB())
		{
			CMCtrlCenter::GetSingletonCtrlCenter()->m_VLproxy.WriteLightParam2Controller();
		}
	}
	OnOK();
	return TRUE;
}

void CProSetCameraTab::UpdateCheckBox_LightCtrl()
{
	if(m_pConfigCenter->GetImgSource() == CAMERA_SOURCE)
	{
		m_bConnectLightCtrl.EnableWindow(TRUE);
		if(m_pConfigCenter->GetConnect2LightCtrlFlag() == true)
		{
			m_bConnectLightCtrl.SetCheck(BST_CHECKED);
		}
	}
	else
	{
		m_bConnectLightCtrl.SetCheck(BST_UNCHECKED);
		m_bConnectLightCtrl.EnableWindow(FALSE);
	}
}

void CProSetCameraTab::OnCbnSelchangeComboSoure()
{
	CString name;
	m_ComboSource.GetLBText(m_ComboSource.GetCurSel(),name);
	wstring wname = name;
	m_pConfigCenter->SetCameraName(ws2s(wname));
}

void CProSetCameraTab::OnBnClickedCheckTrigger()
{
	bool bEnableWnd = (m_TriggerMode.GetCheck() == BST_CHECKED);
	m_TraggerEdge.EnableWindow(bEnableWnd);
}


