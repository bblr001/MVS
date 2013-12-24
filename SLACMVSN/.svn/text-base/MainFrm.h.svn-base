
// MainFrm.h : CMainFrame 类的接口
//

#pragma once
#include "TypeCent.h"

class CMainFrame : public CFrameWndEx
{
	
protected: // 仅从序列化创建
	DECLARE_DYNCREATE(CMainFrame)

// 属性
public:
CMainFrame();
// 操作
public:
	void UpdateUserInfo(CString username, eUSER_GROUP userGroup);

	LRESULT EnterStation(WPARAM wPanel,LPARAM Mylparamp);

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
	void OnClose();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	//CMFCMenuBar       m_wndMenuBar;
	//CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	HBRUSH OnCtlColor(CDC* pDC,CWnd* pWnd,UINT nCtlColor);
	DECLARE_MESSAGE_MAP()

public:
	CWnd* SOverViewWnd;

};


