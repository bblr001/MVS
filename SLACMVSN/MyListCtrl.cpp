// MyListCtrl.cpp
#include "stdafx.h"
#include "MyListCtrl.h"
#include "Resource.h"
#include "UserManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
CMyListCtrl::CMyListCtrl():m_bDragging(FALSE),\
m_pImageListDrag(NULL),m_oldDNDStyle(NULL)
{
	m_bStateIcons = TRUE;
	m_nCheckedItem = -1;
}
CMyListCtrl::~CMyListCtrl()
{}
BEGIN_MESSAGE_MAP(CMyListCtrl,CListCtrl)
	//{{AFX_MSG_MAP(CMyListCtrl)
	ON_NOTIFY_REFLECT(LVN_BEGINDRAG,OnBeginDrag)
	ON_NOTIFY_REFLECT(LVN_BEGINRDRAG,OnBeginDrag)
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT,OnEndLabelEdit)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
void CMyListCtrl::OnBeginDrag(LPNMHDR pnmhdr,LRESULT*)
{
	CPoint ptItem,ptAction,ptImage;
	NM_LISTVIEW *pnmListView = (NM_LISTVIEW *)pnmhdr;
	m_oldDNDStyle = GetExtendedStyle();

	if(m_oldDNDStyle != 0)SetExtendedStyle(0);
	ASSERT(!m_bDragging);
	m_bDragging = TRUE;
	m_iItemDrag = pnmListView->iItem;
	ptAction = pnmListView->ptAction;
	GetItemPosition(m_iItemDrag,&ptItem);
	GetOrigin(&m_ptOrigin);
	ASSERT(m_pImageListDrag == NULL);
	m_pImageListDrag = CreateDragImage(m_iItemDrag,&ptImage);
	m_sizeDelta = ptAction - ptImage;
	m_ptHotSpot = ptAction - ptItem + m_ptOrigin;
	m_pImageListDrag->DragShowNolock(TRUE);
	m_pImageListDrag->SetDragCursorImage(0,CPoint(0,0));
	m_pImageListDrag->BeginDrag(0,CPoint(0,0));

	ptAction -=m_sizeDelta;
	m_pImageListDrag->DragEnter(this,ptAction);
	m_pImageListDrag->DragMove(ptAction);
	m_iItemDrop = -1;
	SetCapture();
}
void CMyListCtrl::OnMouseMove(UINT nFlags,CPoint point)
{
	long        lStyle;
	int         iItem;
	//The LVITEM structure specifies or receives the attributes of a list view item.
	LV_ITEM     lvitem;

	lStyle = GetWindowLong(m_hWnd, GWL_STYLE);
	lStyle &= LVS_TYPEMASK;  // drag will do different things in list and report mode

	if (m_bDragging)
	{
		ASSERT(m_pImageListDrag != NULL);
		m_pImageListDrag->DragMove(point - m_sizeDelta);  // move the image 
		if ((iItem = HitTest(point)) != -1)
		{
			lvitem.mask = LVIF_STATE;
			lvitem.stateMask = LVIS_DROPHILITED;  // highlight the drop target
			if (m_iItemDrop != -1)  // remove the drophighlighted from previous item
			{
				m_pImageListDrag->DragLeave(this);
				lvitem.iItem = m_iItemDrop;
				lvitem.iSubItem = 0;
				lvitem.state = 0;	// sets drophighlighted to FALSE  
				SetItem(&lvitem);
			}
			m_iItemDrop = iItem;
			m_pImageListDrag->DragLeave(this); // unlock the window and hide drag image

			if (lStyle == LVS_REPORT || lStyle == LVS_LIST)
			{
				lvitem.iItem = iItem;
				lvitem.iSubItem = 0;
				lvitem.state = LVIS_DROPHILITED;	// sets the drophighlighted

				SetItem(&lvitem);
				UpdateWindow();
			}
			point -= m_sizeDelta;
			m_pImageListDrag->DragEnter(this, point);  // lock updates and show drag image
		}
	}
	CListCtrl::OnMouseMove(nFlags, point);
}
void CMyListCtrl::OnButtonUp(CPoint point)
{
	if (m_bDragging)  // end of the drag operation
	{
		long        lStyle;
		CString     cstr;

		lStyle = GetWindowLong(m_hWnd, GWL_STYLE) & LVS_TYPEMASK;
		if (m_oldDNDStyle != 0) SetExtendedStyle(m_oldDNDStyle);

		m_bDragging = FALSE;
		ASSERT(m_pImageListDrag != NULL);
		m_pImageListDrag->DragLeave(this);

		SetItemState(m_iItemDrop, 0, LVIS_DROPHILITED);	// remove the drophighlighted from last highlighted target

		m_pImageListDrag->EndDrag();
		delete m_pImageListDrag;
		m_pImageListDrag = NULL;

		// The drop target's sub-item text is replaced by the dragged item's
		// main text
		if (lStyle == LVS_REPORT && m_iItemDrop != m_iItemDrag)
		{
			cstr = GetItemText(m_iItemDrag, 0);
			SetItemText(m_iItemDrop, 1, cstr);
		}

		//the character string "**" is added to the end of the drop target's main text
		if (lStyle == LVS_LIST && m_iItemDrop != m_iItemDrag)
		{
			cstr = GetItemText(m_iItemDrop, 0);
			cstr += _T("**");
			SetItemText(m_iItemDrop, 0, cstr);
		}

		// move the icon
		if (lStyle == LVS_ICON || lStyle == LVS_SMALLICON)
		{
			point -= m_ptHotSpot;  // the icon should be drawn exactly where the image is
			point += m_ptOrigin;
			SetItemPosition(m_iItemDrag, point);  // just move the dragged item
		}
		::ReleaseCapture();
	}
}

void CMyListCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	OnButtonUp(point);
	CListCtrl::OnLButtonUp(nFlags, point);
}

void CMyListCtrl::OnRButtonUp(UINT nFlags, CPoint point)
{
	OnButtonUp(point);
	CListCtrl::OnRButtonUp(nFlags, point);
}

void CMyListCtrl::OnEndLabelEdit(LPNMHDR pnmhdr, LRESULT* /*pLResult*/)
{
	LV_DISPINFO  *plvDispInfo = (LV_DISPINFO *)pnmhdr;
	LV_ITEM      *plvItem = &plvDispInfo->item;
	if (plvItem->pszText != NULL)
		SetItemText(plvItem->iItem, plvItem->iSubItem, plvItem->pszText);
}
void CMyListCtrl::CheckItem(int nNewCheckedItem)
{
	if (m_nCheckedItem != -1)
	{
		if (m_bStateIcons)
		{
			this->SetItemState(m_nCheckedItem, INDEXTOSTATEIMAGEMASK(1), LVIS_STATEIMAGEMASK);
		}
		else
		{
			this->SetItemState(m_nCheckedItem,INDEXTOSTATEIMAGEMASK(1), LVIS_STATEIMAGEMASK | LVIS_OVERLAYMASK);
		}

		// Disable Modify and Delete buttons if no user is selected yet.
		// And cleanup all edit boxes.
		CWnd* pParent = this->GetParent();
		pParent->SetDlgItemText(IDC_ID, _T(""));
		pParent->SetDlgItemText(IDC_NAME, _T(""));
		pParent->SetDlgItemText(IDC_PSW,_T(""));

		pParent->GetDlgItem(IDC_MODIFICATION)->EnableWindow(FALSE);
		pParent->GetDlgItem(IDC_DELETE)->EnableWindow(FALSE);
		pParent->GetDlgItem(IDC_BUTTON_CREATE)->EnableWindow(TRUE);
		CComboBox *com =(CComboBox *)this->GetParent()->GetDlgItem(IDC_COMBO_GROUP);
		com->SetCurSel(3);
	}

	if (m_nCheckedItem == nNewCheckedItem)
	{
		m_nCheckedItem = -1;
	}
	else if ((m_nCheckedItem = nNewCheckedItem) != -1)
	{
		if (m_bStateIcons)
		{
			CWnd* pParent = this->GetParent();
			this->SetItemState(m_nCheckedItem,INDEXTOSTATEIMAGEMASK(2), LVIS_STATEIMAGEMASK);
			pParent->SetDlgItemText(IDC_ID,this->GetItemText(nNewCheckedItem,0));
			pParent->SetDlgItemText(IDC_NAME,this->GetItemText(nNewCheckedItem,1));
			pParent->SetDlgItemText(IDC_GROUPNAME,this->GetItemText(nNewCheckedItem,2));
			pParent->SetDlgItemText(IDC_PSW,_T("TESTTEST1!"));

			pParent->GetDlgItem(IDC_MODIFICATION)->EnableWindow(TRUE);
			pParent->GetDlgItem(IDC_DELETE)->EnableWindow(TRUE);
			pParent->GetDlgItem(IDC_BUTTON_CREATE)->EnableWindow(FALSE);
			
			CComboBox *com =(CComboBox *)this->GetParent()->GetDlgItem(IDC_COMBO_GROUP);
			CUserManager* pWnd = (CUserManager*)pParent;
			auto userInfo = pWnd->m_vUserInfo[m_nCheckedItem];
			int index = com->SelectString(0, userInfo.m_strGroupName);
			if(index == CB_ERR)
				index =  3;
			com->SetCurSel(index);
			
		}
		else
		{
			this->SetItemState(m_nCheckedItem,INDEXTOSTATEIMAGEMASK(2) | INDEXTOOVERLAYMASK(1),LVIS_STATEIMAGEMASK | LVIS_OVERLAYMASK);
		}
	}
}
void CMyListCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	UINT uFlags = 0;
	int nHitItem = this->HitTest(point, &uFlags);

	// we need additional checking in owner-draw mode
	// because we only get LVHT_ONITEM
	BOOL bHit = FALSE;
	if (uFlags == LVHT_ONITEM && (GetStyle() & LVS_OWNERDRAWFIXED))
	{
		CRect rect;
		this->GetItemRect(nHitItem, rect, LVIR_ICON);

		// check if hit was on a state icon
		if (m_bStateIcons && point.x < rect.left)
			bHit = TRUE;
	}
	else if (uFlags & LVHT_ONITEMSTATEICON)
		bHit = TRUE;

	if (bHit)
		CheckItem(nHitItem);
	else
		CListCtrl::OnLButtonDown(nFlags, point);
}