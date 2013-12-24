
// MainTestView.h : CMainTestView 类的接口
//


#pragma once
#include "MainTestDoc.h"
//class CMainTestDoc;
class CModalSettingPropSheet;
class CSettingPropSheetFrame;
class CMainTestView : public CFormView
{
protected: // 仅从序列化创建
	CMainTestView();
	DECLARE_DYNCREATE(CMainTestView)

public:
	enum{ IDD = IDD_MAINTEST_FORM };

// 属性
public:
	CMainTestDoc* GetDocument() const;
	void OnClose();

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CMainTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
   CModalSettingPropSheet * m_pModalSettingPropSheet;

   CSettingPropSheetFrame * m_pSettingPropFrame;
// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()


public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	afx_msg void OnFullScreenMode();
	afx_msg void OnUpdateFullScreenMode(CCmdUI* pCmdUI);

protected:
	boolean isFull;
	CWnd *saveParent;
	CWnd *saveFullParent;
protected:
	//COLORREF background;
	//COLORREF text;
	CMenu *ContextMenu;
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSwitchModel();
	afx_msg void OnSetting();
	afx_msg void OnUpdateSetting(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // MainTestView.cpp 中的调试版本
inline CMainTestDoc* CMainTestView::GetDocument() const
   { return reinterpret_cast<CMainTestDoc*>(m_pDocument); }
#endif

