#pragma once
#include "afxwin.h"
#include  "DBSQLite.h"

// CChangeMode 对话框

class CChangeMode : public CDialog
{
	DECLARE_DYNAMIC(CChangeMode)

public:
	CChangeMode(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChangeMode();

// 对话框数据
	enum { IDD = IDD_DIALOG_USERMODE };
	BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedButton1();
public:
	CEdit m_userid;
	CEdit m_pswd;
	CString m_vMsg;

};
