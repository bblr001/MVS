#pragma once
#include "TlsFileParser.h"
#include "afxwin.h"

class CMConfigCenter;
// CProSetCameraTab 对话框

class CProSetCameraTab : public CPropertyPage
{
	DECLARE_DYNAMIC(CProSetCameraTab)

public:
	CProSetCameraTab();
	virtual ~CProSetCameraTab();

// 对话框数据
	enum { IDD = IDD_DIALOG_PROSET_CAMERA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:

	CButton m_BTScan;
	afx_msg void OnBnClickedButtonScan();
	CComboBox m_ComboSource;

	BOOL OnInitDialog();
	void UpdateCheckBox_LightCtrl();

	//int m_ComboSelect;
	CButton m_TriggerMode;
	afx_msg BOOL OnBnClickedOk();
	afx_msg void OnCbnSelchangeComboSoure();

	// //相机上升沿或下降沿触发
	CComboBox m_TraggerEdge;
	afx_msg void OnBnClickedCheckTrigger();
	CEdit m_triggerDelayAbs;
	CEdit m_CameraGain;
private:
	CMConfigCenter* m_pConfigCenter;
public:
	CButton m_bConnectLightCtrl;
#ifdef SHEET_INSPECTION
	CEdit m_linePerFrame;
	CEdit m_framePerSheet;
#endif
};
