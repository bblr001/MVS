#pragma once


// COverViewPage 对话框

class COverViewPage : public CPropertyPage
{
	DECLARE_DYNAMIC(COverViewPage)

public:
	COverViewPage();
	virtual ~COverViewPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_OVERVIEWPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg BOOL OnEraseBkgnd(CDC* pDC); 

	DECLARE_MESSAGE_MAP()
};
