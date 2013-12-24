
#pragma once
#include "../Inc/CGridListCtrlEx/CGridListCtrlGroups.h"
/////////////////////////////////////////////////////////////////////////////
// CViewTree 窗口
class CTestListWnd;
class CViewList : public CGridListCtrlEx
{
// 构造
public:
	CViewList();
// 重写
protected:
// 实现
public:
	virtual ~CViewList();
	CTestListWnd * m_pListWnd;
    int m_nRow;
	int m_nCol;
	bool m_bCustomDraw;
	virtual bool SortColumn(int nCol, bool bAscending);
    afx_msg void OnClick(NMHDR *,LRESULT*);
	virtual afx_msg void OnContextMenuCell(CWnd* pWnd, CPoint point, int nRow, int nCol);
	virtual afx_msg BOOL OnHeaderClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemMoveUP();
	afx_msg void OnItemMoveDOWN();
	afx_msg void OnItemDelete();
	DECLARE_MESSAGE_MAP()
public:

};
