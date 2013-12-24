// InspList.cpp : 实现文件
//

#include "stdafx.h"
#include "AOIEDITHelp.h"
#include "InspList.h"


// CInspList

IMPLEMENT_DYNAMIC(CInspList, CGridListCtrlEx)

CInspList::CInspList()
{

}

CInspList::~CInspList()
{
}
BOOL CInspList::OnHeaderClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	return TRUE;
}
BOOL CInspList::OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult)
{
	BOOL bRet = CGridListCtrlEx::OnEndLabelEdit(pNMHDR,pResult);
	LV_DISPINFO* pDispInfo = reinterpret_cast<LV_DISPINFO*>(pNMHDR);
	int nRow = pDispInfo->item.iItem;
	int nCol = pDispInfo->item.iSubItem;
	if((pDispInfo->item.mask & LVIF_TEXT)&&
		(pDispInfo->item.pszText != NULL)&&
		(nRow != -1) &&
		(nCol != -1))
	{
		GetParent()->SendMessage(ON_WM_ENDEDITTXT,(WPARAM)nCol,(LPARAM)nRow);
	}
	return bRet;
}
void CInspList::OnContextMenuCell(CWnd* pWnd, CPoint point, int nRow, int nCol)
{
	m_iRow  = nRow;
	m_iCol  = nCol;
	if (point.x == -1 && point.y == -1)
	{
		CRect rect;
		GetClientRect(rect);
		ClientToScreen(rect);
		point = rect.TopLeft();
		point.Offset(5, 5);
	}
	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_MENU_ITEM));
	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);
	CWnd* pWndPopupOwner = this;
	while (pWndPopupOwner->GetStyle() & WS_CHILD)
	{
		pWndPopupOwner = pWndPopupOwner->GetParent();
	}
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, 
		point.x, point.y, pWndPopupOwner);
}
void CInspList::OnContextMenuGrid(CWnd* pWnd, CPoint point)
{
}
int CInspList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CGridListCtrlEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}
BOOL CInspList::OnItemClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMITEMACTIVATE* pItem = reinterpret_cast<NMITEMACTIVATE*>(pNMHDR);

	// The iItem member of pItem is only valid if the icon or first-column label has been clicked
	int nRow = pItem->iItem;
	int nCol = pItem->iSubItem;
	CellHitTest(pItem->ptAction, nRow, nCol);
	return TRUE;	// Let parent-dialog get chance
}
void CInspList::OnCustomDrawCell(int nRow, int nCol, NMLVCUSTOMDRAW* pLVCD, LRESULT* pResult)
{
	CGridColumnTrait* pTrait = GetCellColumnTrait(nRow, nCol);
	if (pTrait==NULL)
		return;

	if (!pTrait->GetColumnState().m_Visible)
	{
		*pResult = CDRF_SKIPDEFAULT;
		return;
	}

	pTrait->OnCustomDraw(*this, pLVCD, pResult);
}
BOOL CInspList::OnItemChanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	if (pNMLV->uChanged & LVIF_STATE && pNMLV->iSubItem == 0)
	{
		if (GetStyle() & LVS_OWNERDATA && GetExtendedStyle() & LVS_EX_CHECKBOXES)
		{
			switch(pNMLV->uNewState & LVIS_STATEIMAGEMASK)
			{
			case INDEXTOSTATEIMAGEMASK(BST_CHECKED + 1):	// new state: checked
				OnOwnerDataToggleCheckBox(pNMLV->iItem, true);
				break;
			case INDEXTOSTATEIMAGEMASK(BST_UNCHECKED + 1):	// new state: unchecked
				OnOwnerDataToggleCheckBox(pNMLV->iItem, false);
				break;
			}
			*pResult = 0;
		}
	}

	return FALSE;	// Let parent-dialog get chance
}
bool CInspList::SortColumn(int nCol, bool bAscending)
{
	return CGridListCtrlEx::SortColumn(nCol,bAscending);
}
void CInspList::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	int startEdit = 0;

	// Find out what subitem was double-clicked
	int nRow, nCol;
	CellHitTest(point, nRow, nCol);
	//if(GetCellImage(nRow,1)==m_nStateImageIdx)
	//	  SetCellImage(nRow,1,m_nStateImageIdx+1);
	if (nRow!=-1)GetParent()->SendMessage(ON_WM_DBROWCLICK,(WPARAM)nRow,(LPARAM)nCol);
	if (nRow!=-1)
		startEdit = OnClickEditStart(nRow, nCol, point, true);

	if (startEdit!=2)
		CListCtrl::OnLButtonDblClk(nFlags, point);

	if (startEdit!=0)
		EditCell(nRow, nCol, point);
}
BEGIN_MESSAGE_MAP(CInspList, CGridListCtrlEx)
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CInspList 消息处理程序


