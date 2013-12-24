#pragma once
#include <pylon/PylonIncludes.h>

#include "resource.h"
#include "afxwin.h"
#include "TlsFileParser.h"
#include "ProSetCameraTab.h"
#include "ProSetRejectTab.h"
#include "ProSetBaseTab.h"
#include "CheckBox.h"

// CProgramSettingDlg 对话框

class CProgramSettingDlg : public CDialog
{
	DECLARE_DYNAMIC(CProgramSettingDlg)

public:
	CProgramSettingDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CProgramSettingDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_PROSETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BOOL OnInitDialog();
	CProSetCameraTab m_CameraTab;
	CProSetRejectTab m_RejectTab;
	CProSetBaseTab m_BaseTab;
	CButton m_InitCurrentPro;

	CTabCtrl m_TabCtrl_ProSetting;
	afx_msg void OnTcnSelchangeTabProsetting(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnPaint();
private:
	//CRect m_acceptRect;
	//CRect m_denyRect;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedCancel();
};
