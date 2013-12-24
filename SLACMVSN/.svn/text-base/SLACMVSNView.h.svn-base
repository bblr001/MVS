
// SLACMVSNView.h : CSLACMVSNView 类的接口
//


#pragma once
#include "OverViewPage.h"
//#include "TestChanelPage.h"
#include "BtnST.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "MyLabel.h"
#include "TabCtrlDoc.h"
#include "MyPopButton.h"
class CSettingPropSheetFrame;

class CSLACMVSNDoc;
class CSLACMVSNView : public CFormView
{
protected: // 仅从序列化创建
	CSLACMVSNView();
	DECLARE_DYNCREATE(CSLACMVSNView)

public:
	enum{ IDD = IDD_SLACMVSN_FORM };

// 属性
public:
	CSLACMVSNDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void UpdateUserInfo(CString username, eUSER_GROUP userGroup);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

public:
	virtual ~CSLACMVSNView();
	//void OnTcnSelchangeTabCtrol(NMHDR *pNMHDR, LRESULT *pResult);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:
    CSettingPropSheetFrame * m_pSettingPropFrame;
	COverViewPage m_overView;
	CFont   cfont; 
	CFont   timefont;
	CFont * m_oldFont;
	CDC*    m_pDC;
	__time64_t ltime;
	void OnDraw(CDC* pDC);

public:


// 生成的消息映射函数
protected:
	//{{AFX_MSG(CSLACMVSNView)
	afx_msg int OnCreate(LPCREATESTRUCT lpcs);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC,CWnd* pWnd,UINT nCtlColor);
	//afx_msg void OnTimer(UINT nIdEvent);
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CTabCtrlDoc m_MainTable;
	CButtonST m_btnExit;
	CButtonST m_btnUser;
	CButtonST m_btnLogin;
	CMyLabel  m_sCustomerTile;
	CMyLabel  m_lbUSER;
	CMyPopButton m_btnMenu;
	CRect m_rtArea;
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedUser();
	afx_msg void OnBnClickedLogin();
	CMyLabel m_stTitleEng;
	CButtonST m_btnLogout;
	afx_msg void OnBnClickedButLogout();
};

#ifndef _DEBUG  // SLACMVSNView.cpp 中的调试版本
inline CSLACMVSNDoc* CSLACMVSNView::GetDocument() const
   { return reinterpret_cast<CSLACMVSNDoc*>(m_pDocument); }
#endif

