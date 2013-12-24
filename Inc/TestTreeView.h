
#pragma once

#include "ViewTree.h"
#include "AnalyzeTLS.h"


class CTestTreeViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CTestTreeView : public CDockablePane
{
// 构造
public:
	CTestTreeView();

	void AdjustLayout();
	void OnChangeVisualStyle();
	AnalyzeTLS* GetTestTreeList(){return &m_TestTreeList;};
	void EnableTools(bool disableTools){m_wndToolBar.EnableWindow(disableTools);};

// 属性
protected:

	CViewTree m_wndTestTreeView;
	CImageList m_TestTreeViewImages;
	CTestTreeViewToolBar m_wndToolBar;
	AnalyzeTLS m_TestTreeList;
	HTREEITEM hCurrentTest;

protected:
	void FillTestTreeView();


// 实现
public:
	virtual ~CTestTreeView();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnOpenTLS();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//afx_msg 
	BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

	DECLARE_MESSAGE_MAP()
};

