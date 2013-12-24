#pragma once
#include "afxwin.h"
#include "AnalyzeTLS.h"
#include "TypeCent.h"


// CJobMainWnd 窗体视图

class CJobMainView : public CFormView
{
	DECLARE_DYNCREATE(CJobMainView)

protected:
	CJobMainView();           // 动态创建所使用的受保护的构造函数
	virtual ~CJobMainView();

public:
	enum { IDD = IDD_FORMVIEW_JOBMAINVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ComboSource;
	CButton m_BTScan;


	CButton m_BTRun;

	void Init(MI_SETTING *pSetting);

	int m_ComboSelect;
	CButton m_BTStop;
	CStatic m_Static_ShowWindow;
	afx_msg void OnBnClickedButtonScan();
	afx_msg void OnBnClickedButtonLoaddll();
	afx_msg void OnBnClickedButtonRun();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonConfig();
	CButton m_BTConfig;
	CButton m_BTClose;
	afx_msg void OnBnClickedButtonClose();
	CButton m_BTLoadDll;

	void LoadTestItem(list<CTlsData*> *itemList);

	MI_SETTING* m_pCurrentPanel;
	BOOL m_bHaveTestItem;
};


