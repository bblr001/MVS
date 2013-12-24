
// AOIEDITHelpView.h : CAOIEDITHelpView 类的接口
//


#pragma once
#include "afxwin.h"
#ifndef _HelpView_H_
#define _HelpView_H_

class CAOIEDITHelpDoc;
class CAOIEDITHelpView : public CFormView
{
protected: // 仅从序列化创建
	CAOIEDITHelpView();
	DECLARE_DYNCREATE(CAOIEDITHelpView)

public:
	enum{ IDD = IDD_AOIEDITHELP_FORM };

// 属性
public:
	CAOIEDITHelpDoc* GetDocument() const;

// 操作
public:
   	HWND GetWndHID(){ASSERT(this->m_hWnd);return m_hWnd;};
// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnDraw(CDC* pDC);

// 实现
public:
	virtual ~CAOIEDITHelpView();



#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	void SysInit();
protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnMoving(UINT nSide, LPRECT lpRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	bool m_bRBtnDB;
public:
	//CStatic m_halconDispWnd;
};

#ifndef _DEBUG  // AOIEDITHelpView.cpp 中的调试版本
inline CAOIEDITHelpDoc* CAOIEDITHelpView::GetDocument() const
   { return reinterpret_cast<CAOIEDITHelpDoc*>(m_pDocument); }
#endif

#endif

