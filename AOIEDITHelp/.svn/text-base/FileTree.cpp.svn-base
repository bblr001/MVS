#include "stdafx.h"
#include "FileTree.h"
#include "AOIEDITHelp.h"
#include "AOIEDITHelpDoc.h"
#include "MainFrm.h"
#include "Resource.h"
#include <winnls.h>
#include "Tools.h"
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
IMPLEMENT_DYNCREATE(CFileTree, CTreeView)
CFileTree::CFileTree():m_numItem(0)
{

}
CFileTree::~CFileTree()
{

}


BEGIN_MESSAGE_MAP(CFileTree, CTreeView)
	//{{AFX_MSG_MAP(CFileTree)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_CONTEXTMENU()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
	ON_NOTIFY_REFLECT(TVN_SELCHANGED,OnTreeSelchanged)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnTreeItemExpanding)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED,OnTreeItemExpanded)
	ON_NOTIFY_REFLECT(TVN_DELETEITEM,OnTreeDeleteItem)
	ON_MESSAGE( WM_COMMANDHELP, OnCommandHelp)
	ON_NOTIFY_REFLECT(NM_RETURN, OnTreeReturn)
	ON_COMMAND(ID_FILETREE_OPENFILE, &CFileTree::OnFiletreeOpenfile)
END_MESSAGE_MAP()
void CFileTree::DeleteTreeContents()
{
	// Delete current contents
	//
	if ((int)GetTreeCtrl().GetCount() > 0)
	{
		DeleteTreeItems( m_hObjects) ;
	}
}
void CFileTree::OnContextMenu(CWnd* pWnd, CPoint point)
{
		if (point.x == -1 && point.y == -1)
			{
				CRect rect;
				GetClientRect(rect);
				ClientToScreen(rect);
				
				point = rect.TopLeft();
				point.Offset(5, 5);
			}
			
			CMenu menu;
			VERIFY(menu.LoadMenu(IDR_MENU_FILETREE));
			
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
void CFileTree::DeleteTreeItems( HTREEITEM htree )
{
	HTREEITEM       hItem, hItemNext ;

	hItem = GetTreeCtrl().GetChildItem( htree ) ;
	while( hItem )
	{
		hItemNext = GetTreeCtrl().GetNextSiblingItem( hItem ) ;
		DeleteTreeItems( hItem) ;
		hItem = hItemNext ;
	}
	GetTreeCtrl().DeleteItem(htree);
}
BOOL CFileTree::IsLeave(HTREEITEM htree)
{
 return (GetTreeCtrl().GetChildItem( htree ) == NULL);
}
BOOL CFileTree::IsValidSel()
{
	return (GetTreeCtrl().GetSelectedItem() != NULL) ;
}
LRESULT CFileTree::OnCommandHelp(WPARAM, LPARAM lParam)
{
  theApp.WinHelp(lParam,HELP_CONTEXT);
  return TRUE;
}
BOOL CFileTree::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CTreeView::PreCreateWindow(cs))
	{
		return FALSE;
	}
	cs.style = WS_CHILD|WS_VISIBLE|WS_BORDER|TVS_LINESATROOT|TVS_HASLINES
		|TVS_HASBUTTONS|TVS_DISABLEDRAGDROP;
	return TRUE;
}
int CFileTree::OnCreate(LPCREATESTRUCT lpcs)
{
	if (CTreeView::OnCreate(lpcs)==-1)
	{
		return -1;
	}
	return 0;
}
void CFileTree::OnInitialUpdate()
{
	GetTreeCtrl().SetImageList(&theApp.m_images,TVSIL_NORMAL);
    OnFileBind(CString(_T(".\\MasterTls\\Master_TestItem.mas")));
}
void CFileTree::OnDestroy()
{
	DeleteTreeContents();
	CTreeView::OnDestroy();
}
void CFileTree::OnDraw( CDC* /*pdc */ )
{
}
void CFileTree::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	UINT hitflags ;
	HTREEITEM hitem ;

	hitem = GetTreeCtrl().HitTest( point, &hitflags ) ;
	if (hitflags & (TVHT_ONITEM | TVHT_ONITEMBUTTON))
	{
		NM_TREEVIEW nm ;
		nm.itemNew.mask = TVIF_PARAM  ;
		nm.itemNew.hItem = hitem ;
		if (GetTreeCtrl().GetItem( &nm.itemNew ))
		{
			CAOIEDITHelpDoc*   pDoc = GetDocument() ;
			pDoc->SetSelectElem((TiXmlElement*)nm.itemNew.lParam);
			pDoc->UpdateAllViews( this, UPD_DBSELECTOBJECTVIEW ) ;
		}
	}
	CTreeView::OnLButtonDblClk(nFlags, point);
}
void CFileTree::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	pSender; pHint ;
	if (lHint & UPD_DBSELECTOBJECTVIEW)
		return ;

	BeginWaitCursor() ;
	GetTreeCtrl().SetRedraw( FALSE ) ;
	GetTreeCtrl().SelectItem( NULL ) ;

	GetTreeCtrl().SetRedraw( TRUE ) ;
	EndWaitCursor() ;
}
#ifdef _DEBUG
void CFileTree::AssertValid() const
{
	CTreeView::AssertValid();
}

void CFileTree::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

#endif //_DEBUG
void CFileTree::OnTreeSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	CAOIEDITHelpDoc*   pDoc = GetDocument() ;
	NM_TREEVIEW* pnmtv = (NM_TREEVIEW*)pNMHDR;
	BOOL bRet = IsValidSel();
	if(bRet)
	{
		/*pDoc->SetSelectElem((TiXmlElement*)pnmtv->itemNew.lParam);
		pDoc->UpdateAllViews( this, UPD_SELECTOBJECTVIEW ) ;*/
	}
	*pResult = 0;
}
void CFileTree::OnTreeItemExpanding(NMHDR* pNMHDR, LRESULT* pResult)
{
	*pResult = 0;
	NM_TREEVIEW* pnmtv = (NM_TREEVIEW*)pNMHDR;
	if (pnmtv->action == TVE_EXPAND && pnmtv->itemNew.hItem != m_hObjects)
	{
		if (pnmtv->itemNew.state & TVIS_EXPANDEDONCE)
			return ;

		BeginWaitCursor() ;
		GetTreeCtrl().SetRedraw( FALSE ) ;
		if (pnmtv->itemNew.lParam != NULL)
			ExpandObject( pnmtv ) ;
		GetTreeCtrl().SetRedraw( TRUE ) ;
		EndWaitCursor() ;
	}
}
WCHAR *CFileTree::Ansi2WChar(LPCSTR pszSrc, int nLen)

{
	int nSize = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pszSrc, nLen, 0, 0);
	if(nSize <= 0) return NULL;

	WCHAR *pwszDst = m_MemString.GetBufferSetLength(nSize+1);
	if( NULL == pwszDst) return NULL;

	MultiByteToWideChar(CP_ACP, 0,(LPCSTR)pszSrc, nLen, pwszDst, nSize);
	pwszDst[nSize] = 0;
	if( pwszDst[0] == 0xFEFF)                    
		for(int i = 0; i < nSize; i ++) 
			pwszDst[i] = pwszDst[i+1]; 
	return pwszDst;
}
void CFileTree::ExpandObject( NM_TREEVIEW* pnmtv )
{
	TV_INSERTSTRUCT tvis ;
	TiXmlElement*  element = (TiXmlElement*)(pnmtv->itemNew.lParam) ;
	tvis.hParent = pnmtv->itemNew.hItem ;
	//tvis.hInsertAfter = TVI_SORT ;
	tvis.item.mask = TVIF_PARAM | TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE ;
	tvis.item.iImage = tvis.item.iSelectedImage = BMINDEX(IDB_SUBOBJFOLDER) ;
	TiXmlAttribute *attribute;
    element=element->FirstChildElement();
	for (;element;element=element->NextSiblingElement())
	{
		attribute = element->FirstAttribute();
		if(attribute)
		{
			tvis.item.lParam = (LPARAM)(element);
			const char *pv = attribute->Value();
			tvis.item.pszText = Ansi2WChar(pv,strlen(pv));//
			m_hInsertable = GetTreeCtrl().InsertItem( &tvis ) ;
		}
	}
}
void CFileTree::OnFileBind(CString& path)
{
	GetTreeCtrl().DeleteAllItems();
	CAOIEDITHelpDoc*   pDoc = GetDocument() ;
	ASSERT(0!=pDoc);
	wstring wstrText = path.GetBuffer();
	bool bRet = pDoc->loadIni(ws2s(wstrText).c_str());
	if(bRet)
	{
	 TiXmlElement* rootElem = pDoc->GetRootElem();
	 if(rootElem)
	 {
		const char* value = rootElem->Value();
		string strText(value);
		wstrText = s2ws(strText);
		TV_INSERTSTRUCT tvis;
		tvis.hParent = TVI_ROOT;
		tvis.hInsertAfter = TVI_LAST;
		tvis.item.mask = TVIF_TEXT|TVIF_PARAM|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
		tvis.item.lParam = (LPARAM)(rootElem);
		tvis.item.cChildren = 1;
		tvis.item.pszText=(wchar_t*)wstrText.c_str();
		tvis.item.iImage = BMINDEX(IDB_OBJECTFOLDER);
		tvis.item.iSelectedImage = BMINDEX(IDB_OBJECTFOLDER);
		m_hObjects = GetTreeCtrl().InsertItem(&tvis);
		tvis.item.iImage = BMINDEX(IDB_SUBOBJFOLDER) ;
		tvis.item.iSelectedImage = BMINDEX(IDB_SUBOBJFOLDER) ;
		tvis.hParent = m_hObjects ;
		TiXmlAttribute *attribute;
		TiXmlElement *element=rootElem->FirstChildElement("common");
		if(element){
			attribute = element->FirstAttribute();
			if(attribute)
			{
			 tvis.item.lParam = (LPARAM)(element);
			 const char *pv = attribute->Value();
			 tvis.item.pszText = Ansi2WChar(pv,strlen(pv));//
			 m_hInsertable = GetTreeCtrl().InsertItem( &tvis ) ;
			}
		}
		tvis.item.mask |=TVIF_CHILDREN;
		element=element->NextSiblingElement();
		element = element->FirstChildElement();
		for (;element;element=element->NextSiblingElement())
		{
			attribute = element->FirstAttribute();
			if(attribute)
			{
				tvis.item.lParam = (LPARAM)(element);
				const char *pv = attribute->Value();
				tvis.item.pszText = Ansi2WChar(pv,strlen(pv));//
				m_hInsertable = GetTreeCtrl().InsertItem( &tvis ) ;
			}
		}
	  }
	}
	GetTreeCtrl().Expand( m_hObjects, TVE_EXPAND ) ;
}
void CFileTree::OnTreeItemExpanded(NMHDR* pNMHDR, LRESULT* pResult)
{
	*pResult = 0;
	NM_TREEVIEW* pnmtv = (NM_TREEVIEW*)pNMHDR;
	if ( pnmtv->itemNew.lParam != NULL &&
		pnmtv->action == TVE_COLLAPSE)
	{
		//        TV_INSERTSTRUCT tvis ;
		GetTreeCtrl().Expand( pnmtv->itemNew.hItem, TVE_COLLAPSERESET ) ;
	}
}
void CFileTree::OnTreeDeleteItem(NMHDR* pNMHDR, LRESULT*)
{
	NM_TREEVIEW* pnmtv = (NM_TREEVIEW*)pNMHDR;

	if (pnmtv->itemOld.lParam)
	{
		pnmtv->itemOld.lParam = NULL ;
	}
}
void CFileTree::OnTreeReturn(NMHDR* pNMHDR , LRESULT* pResult)
{
	*pResult = (LRESULT)TRUE ;
	HTREEITEM hTreeItemSel = GetTreeCtrl().GetSelectedItem() ;
    if(IsLeave(hTreeItemSel))
	{
		CAOIEDITHelpDoc*   pDoc = GetDocument() ;
		TiXmlElement* elem = (TiXmlElement*)GetTreeCtrl().GetItemData(hTreeItemSel);
		pDoc->SetSelectElem(elem);
		pDoc->UpdateAllViews( this, UPD_SELECTOBJECTVIEW ) ;
	}
	if (hTreeItemSel)
		GetTreeCtrl().Expand( hTreeItemSel, TVE_TOGGLE ) ;
}
#ifdef _DEBUG

CAOIEDITHelpDoc* CFileTree::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAOIEDITHelpDoc)));
	return (CAOIEDITHelpDoc*) m_pDocument;
}

#endif //_DEBUG
void CFileTree::OnFiletreeOpenfile()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog   OpenTlsDlg(TRUE,NULL, NULL,OFN_HIDEREADONLY, _T("Test List File(*.mas)|*.mas"));//open   as 
	if(OpenTlsDlg.DoModal()==IDOK) 
	{ 
		OnFileBind(OpenTlsDlg.GetPathName());
	}
}
