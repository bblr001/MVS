#pragma once
#include "TypeCent.h"
#include "resource.h"
// CJobDialog 对话框

class CJobDialog : public CDialog
{
	DECLARE_DYNAMIC(CJobDialog)

public:
	//
	//CJobDialog(CWnd* pParent = NULL);   // 标准构造函数
	CJobDialog(MI_SETTING* pParent);
	virtual ~CJobDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG_JOB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog();

	CFrameWnd * m_pJobFrameWnd;

	CSplitterWnd m_cSplitter;

	MI_SETTING* m_pCurrentPanel;
};