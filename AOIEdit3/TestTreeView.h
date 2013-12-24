// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// ("Fluent UI")，该示例仅作为参考资料提供， 
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有 (C) Microsoft Corporation
// 保留所有权利。

#pragma once

#include "ViewTree.h"
#include "TlsFileParser.h"

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

// 属性
protected:

	CViewTree m_wndTestTreeView;
	CImageList m_TestTreeViewImages;
	CTestTreeViewToolBar m_wndToolBar;
	TlsFileParser m_TestTreeList;
	HTREEITEM hCurrentTest;

protected:
	void FillTestTreeView();

// 实现
public:
	virtual ~CTestTreeView();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnOpenTLS();
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	//afx_msg 
	BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

	DECLARE_MESSAGE_MAP()
};

