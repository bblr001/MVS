#pragma once
#include "resource.h"
#include "afxwin.h"

// CWarningDlg 对话框

class CWarningDlg : public CDialog
{
	DECLARE_DYNAMIC(CWarningDlg)

public:
	CWarningDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWarningDlg();

	virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG_WARNING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CComboBox m_SelectedWarning;
};
