#pragma once
#include "afxwin.h"

class CMConfigCenter;
// CProSetBaseTab 对话框

class CProSetBaseTab : public CPropertyPage
{
	DECLARE_DYNAMIC(CProSetBaseTab)

public:
	CProSetBaseTab();
	virtual ~CProSetBaseTab();

// 对话框数据
	enum { IDD = IDD_DIALOG_PROSET_BASE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	BOOL OnInitDialog();

public:
	afx_msg BOOL OnBnClickedOk();
	CButton m_bSaveErrImag;
// 	int m_SourceFile;
// 	int m_SourceFiles;
// 	int m_SourceCamera;
	CButton m_SettingPathButton;
	CStatic m_ShowSetting;
	afx_msg void OnBnClickedRadioFile();
	afx_msg void OnBnClickedRadioFiles();
	afx_msg void OnBnClickedRadioCamera();
	afx_msg void OnBnClickedButtonSourcesel();
	CEdit m_TimeInterval;
	CEdit m_ErrorFileCount;
	CButton m_bSavePassImage;

private:
	CMConfigCenter* m_pConfigCenter;
};
