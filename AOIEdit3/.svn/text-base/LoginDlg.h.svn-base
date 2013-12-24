#pragma once
#include "afxwin.h"
#include "DBControl.h"
#include "function.h"

#include "SqliteDB.h"
#include "DBControl.h"
#include "CppSQLite3.h"
#include "TypeCent.h"

// CLoginDlg 对话框

class CLoginDlg : public CDialog
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoginDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_CHMODE };

	BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
		CDBControl<CppSQLite3Query>* m_db;
public:
	afx_msg void OnBnClickedOk();
	CEdit m_editUsername;
	CEdit m_UserGroup;
	CEdit m_editPassword;
	CBrush m_brushBk;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
