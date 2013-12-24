#pragma once


// CInspList
#include "../Inc/CGridListCtrlEx/CGridListCtrlEx.h"
#include "../Inc/CGridListCtrlEx/CGridColumnTraitDateTime.h"
#include "../Inc/CGridListCtrlEx/CGridColumnTraitEdit.h"
#include "../Inc/CGridListCtrlEx/CGridColumnTraitCombo.h"
#include "../Inc/CGridListCtrlEx/CGridColumnTraitHyperLink.h"
#include "../Inc/CGridListCtrlEx/CGridRowTraitXP.h"
#include "../Inc/CGridListCtrlEx/ViewConfigSection.h"
#define ON_WM_DBROWCLICK (WM_USER + 102)
#define ON_WM_ENDEDITTXT (WM_USER + 103)
class CInspList : public CGridListCtrlEx
{
	DECLARE_DYNAMIC(CInspList)

public:
	CInspList();
	virtual ~CInspList();
    int m_nStateImageIdx;
	int m_iRow;
	int m_iCol;
	virtual bool SortColumn(int nCol, bool bAscending);
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual afx_msg BOOL OnItemClick(NMHDR* pNMHDR, LRESULT* pResult);
	virtual afx_msg BOOL OnItemChanged(NMHDR* pNMHDR, LRESULT* pResult);
	virtual afx_msg void OnContextMenuGrid(CWnd* pWnd, CPoint pos);
	virtual afx_msg void OnContextMenuCell(CWnd* pWnd, CPoint point, int nRow, int nCol);
	virtual afx_msg BOOL OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult);
	virtual afx_msg BOOL OnHeaderClick(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnCustomDrawCell(int nRow, int nCol, NMLVCUSTOMDRAW* pLVCD, LRESULT* pResult);

};


