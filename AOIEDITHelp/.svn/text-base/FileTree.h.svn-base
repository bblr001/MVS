#ifndef _FILE_VW_H_
#define _FILE_VW_H_
#include <afxcview.h>

#include "tinyxml.h"
class CAOIEDITHelpDoc;

class CFileTree : public CTreeView
{
public:
	DECLARE_DYNCREATE(CFileTree)
protected:
	CFileTree();
public:
	CAOIEDITHelpDoc* GetDocument();
	HTREEITEM m_hElement;
	HTREEITEM     m_hObjects;
	HTREEITEM     m_hTypeLibs ;
	HTREEITEM     m_hInterfaces;

	HTREEITEM     m_hInsertable ;
	HTREEITEM     m_hControls ;
	HTREEITEM     m_hInternal ;
#ifdef SHOW_CONTAINERS
	HTREEITEM     m_hContainers ;
#endif
	HTREEITEM     m_hOLE1 ;
	HTREEITEM     m_hUnclassified ;
	int m_numItem;
	void DeleteTreeContents() ;
	void DeleteTreeItems( HTREEITEM htree ) ;
	BOOL IsValidSel() ;
	BOOL IsLeave(HTREEITEM htree );
	void ExpandObject( NM_TREEVIEW* pnmtv );
	WCHAR *Ansi2WChar(LPCSTR pszSrc, int nLen);
	CString m_MemString;

public:
	virtual ~CFileTree();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnDraw(CDC* pDC);
	virtual void OnInitialUpdate();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:
	//{{AFX_MSG(CFileTree)
	afx_msg int  OnCreate(LPCREATESTRUCT lpcs);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnFileBind(CString& path);
	//}}AFX_MSG
	afx_msg void OnTreeSelchanged(NMHDR* pNMHDR, LRESULT* pResult) ;
	afx_msg void OnTreeItemExpanding(NMHDR* pNMHDR, LRESULT* pResult) ;
	afx_msg void OnTreeItemExpanded(NMHDR* pNMHDR, LRESULT* pResult) ;
	afx_msg void OnTreeDeleteItem(NMHDR* pNMHDR, LRESULT* pResult) ;
	afx_msg void OnTreeReturn(NMHDR* pNMHDR, LRESULT* pResult) ;
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg LRESULT OnCommandHelp(WPARAM, LPARAM lParam) ;
	DECLARE_MESSAGE_MAP()

	friend class CMainFrame;

public:
	afx_msg void OnFiletreeOpenfile();
};
#ifndef _DEBUG  // debug version in vw.cpp
inline CAOIEDITHelpDoc* CFileTree::GetDocument()
{ return (CAOIEDITHelpDoc*) m_pDocument; }
#endif
#endif