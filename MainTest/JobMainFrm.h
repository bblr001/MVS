
// MainFrm.h : CMainFrame 类的接口
//

#pragma once
#include "resource.h"  

#include "..\Inc\TestTreeView.h"

//#include "..\Inc\TestListWnd.h"
#include "..\Inc\TestItemPropertiesWnd.h"
#include "..\Inc\TestItemManage.h"

class CJobMainFrame : public CFrameWndEx
{
	
public: // 仅从序列化创建
	CJobMainFrame();
	DECLARE_DYNCREATE(CJobMainFrame)
	std::list<CTlsData*> m_TestList;

// 属性
public:

// 操作
public:
	

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// 实现
public:
	virtual ~CJobMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;



	//CTestListWnd        m_wndTestListView;


// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);

	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
};


