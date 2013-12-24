#pragma once

#include "TlsFileParser.h"
#include "afxwin.h"
// CProSetRejectTab 对话框

class CProSetRejectTab : public CPropertyPage
{
	DECLARE_DYNAMIC(CProSetRejectTab)

public:
	CProSetRejectTab();
	virtual ~CProSetRejectTab();

	enum { IDD = IDD_DIALOG_PROSET_REJECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:

	BOOL OnInitDialog();

	CButton m_RejectEnable;
	CButton m_RejectTest;
	afx_msg void OnBnClickedButtonTest();
	CEdit m_RejectPort;
	afx_msg void OnBnClickedCheckReject();
	//afx_msg BOOL OnBnClickedOk();
	BOOL OnBnClickedMyOk();
	CEdit m_DelayTime;
	CEdit m_SignelTime;
	// 连续不良下限数
	CEdit m_NGCount;
	//红色状态指示灯
	CEdit m_RedWinnerPort;
	// //正常状态指示灯(绿色)
	CEdit m_bStatePort;
};
