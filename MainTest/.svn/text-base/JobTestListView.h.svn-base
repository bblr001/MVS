#pragma once

#include "TypeCent.h"
#include "AnalyzeTLS.h"
#include "afxcmn.h"
#include "Tools.h"

// CJobTestListView 窗体视图

class CJobTestListView : public CFormView
{
	DECLARE_DYNCREATE(CJobTestListView)

protected:
	CJobTestListView();           // 动态创建所使用的受保护的构造函数
	virtual ~CJobTestListView();

public:
	enum { IDD = IDD_FORMVIEW_JOBLISTVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
	void Init(MI_SETTING* pSetting);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


	list<CTlsData*> pSubTestItemList;

	CTestItemList testItemData;
	MI_SETTING* m_pCurrentPanel;
	int m_ItemCount;
public:
	CListCtrl m_TestListItem;
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonLoad();


	void SetTestListCtrlConect(int Item,int Column);
	void SetTestListCtrlConect(int Item,int Column,CString connect);
	afx_msg void OnNMDblclkListTestitem(NMHDR *pNMHDR, LRESULT *pResult);
};


