
#include "stdafx.h"
#include "ViewList.h"
#include "CGridListCtrlEx\CGridColumnTraitDateTime.h"
#include "CGridListCtrlEx\CGridColumnTraitEdit.h"
#include "CGridListCtrlEx\CGridColumnTraitCombo.h"
#include "CGridListCtrlEx\CGridColumnTraitHyperLink.h"
#include "CGridListCtrlEx\CGridRowTraitXP.h"
#include "CGridListCtrlEx\ViewConfigSection.h"
#include "MCtrlCenter.h"
#include "AOIEditVer3.h"
#include "../AOIEdit3/Resource.h"
#include "TestListWnd.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTree

CViewList::CViewList():m_pListWnd(0)
{
}
CViewList::~CViewList()
{
}
BEGIN_MESSAGE_MAP(CViewList, CGridListCtrlEx)
 //{{AFX_MSG(CViewList,CGridListCtrlEx)
    ON_NOTIFY_REFLECT(NM_CLICK,OnClick)
 //}}AFX_MSG
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CViewTree 消息处理程序
void CViewList::OnClick(NMHDR* pNMHDR, LRESULT* pResult)
{
    NMITEMACTIVATE* nmitm = (NMITEMACTIVATE*)pNMHDR;
	m_nRow = nmitm->iItem;
	m_nCol = nmitm->iSubItem;
}
void CViewList:: OnItemMoveUP()
{
	if(m_nRow == 0) 
		return;
	SetRedraw(FALSE);
	m_nRow--;
	this->MoveSelectedRows(m_nRow);
	SetRedraw(TRUE);
}
void CViewList:: OnItemMoveDOWN()
{
	int count = GetItemCount();
	if(m_nRow == count - 1)
		return;
	SetRedraw(FALSE);
	m_nRow++;
	this->MoveSelectedRows(m_nRow);
	SetRedraw(TRUE);
}
void CViewList:: OnItemDelete()
{
	SetRedraw(FALSE);
	DeleteItem(m_nRow);	
	if(m_pListWnd)
		m_pListWnd->m_ItemCount--;
	SetRedraw(TRUE);
}
BOOL CViewList::OnHeaderClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	return TRUE;
}
void CViewList::OnContextMenuCell(CWnd* pWnd, CPoint point, int nRow, int nCol)
{
	if(CMConfigCenter::GetSingletonConfigCenter()->GetUserGroup()==OPERATOR)
		return;
	m_nRow  = nRow;
	m_nCol  = nCol;
	if (point.x == -1 && point.y == -1)
	{
		CRect rect;
		GetClientRect(rect);
		ClientToScreen(rect);
		point = rect.TopLeft();
		point.Offset(5, 5);
	}
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_MENU_TESTITEM, point.x, point.y, this, TRUE);
}

bool CViewList::SortColumn(int nCol, bool bAscending)
{
	return CGridListCtrlEx::SortColumn(nCol,bAscending);	
}


