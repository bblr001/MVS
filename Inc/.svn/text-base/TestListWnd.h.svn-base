
#pragma once
#include "../Inc/ViewList.h"
#include "../Inc/tinxml/tinyxml.h"
#include "../Inc/TlsFileParser.h"
#include <vector>

using namespace std;

class CMConfigCenter;
class CMCtrlCenter;

class CTestListWindowToolBar : public CMFCToolBar
{
public:
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CTestListWnd : public CDockablePane
{
// 构造
public:
	CTestListWnd();
	void SetTestListWnd(CTlsData *pData);
	void ReflashTestListWnd(int order);
	void SetTestListCtrlConect(int Item,int Column);
	void SetTestListCtrlConect(int Item,int Column,CString connect);
	void SetTestListCtrlConect(int Item,int Column,int connect);
	void InitTestList(string fileName);
	int m_ItemCount;
// 属性
protected:
	CViewList m_wndTestItemList;	
	CTestListWindowToolBar m_wndToolBar;
	std::vector<CTlsData> m_vTestData;
	CTestItemList m_testItemData;
	void AdjustHorzScroll();
	void InsertListData();
	void AdjustLayout();
	void InitTestListWnd();
	void ReleaseMem();
// 实现
public:
	virtual ~CTestListWnd();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnDummyCompile();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
public:
	void OnTestListBtMoveUp();
	void OnTestListBtMoveDown();
	void OnTestListBtDelete();
	void OnTestListBtApply();

	void SaveTestList();

	BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

public:
	DECLARE_MESSAGE_MAP()
private:
	CMConfigCenter* m_pConfigCenter;
	CMCtrlCenter*   m_pCtrlCenter;
};

