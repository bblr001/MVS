// MyListCtrl.h
// CMyListCtrl.h

#ifndef INC_MYLISTCTRL_H
#define INC_MYLISTCTRL_H

class CMyListCtrl : public CListCtrl
{
	//Construction
public:
	CMyListCtrl();
	//Attributes
	BOOL      m_bDragging;
	int       m_iItemDrag;
	int       m_iItemDrop;
	CPoint    m_ptHotSpot;
	CPoint    m_ptOrigin;
	CSize     m_sizeDelta;
	DWORD     m_oldDNDStyle;
	CImageList * m_pImageListDrag;
	int       m_checkItemIndex;
	// Operations
public:
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyListCtrl)
public:
	//}}AFX_VIRTUAL
	//Implementation
public:
	virtual ~CMyListCtrl();
	void OnButtonUp(CPoint point);
	void CheckItem(int nNewCheckedItem);
	// Generated message map functions
protected:
	//{{AFX_MSG(CMyListCtrl)
	afx_msg void OnBeginDrag(LPNMHDR pnmhdr,LRESULT *pResult);
	afx_msg void OnEndLabelEdit(LPNMHDR pnmhdr,LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags,CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags,CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags,CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BOOL m_bStateIcons;
	int  m_nCheckedItem;
};
/////////
#endif