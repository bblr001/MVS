// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// ("Fluent UI")，该示例仅作为参考资料提供， 
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有 (C) Microsoft Corporation
// 保留所有权利。

// MainFrm.h : CMainFrame 类的接口
//

#pragma once
#include "ChildView.h"
#include "TestTreeView.h"
#include "testlistwnd.h"
#include "PropertiesWnd.h"
#include "TypeCent.h"
#include "..\Inc\TestItemManage.h"
#include "ProgramSettingDlg.h"
#include "LoginDlg.h"
#include <WindowsX.h>
#include "NextFormView.h"
#define  SHOWMessageBox(S) MessageBox(_T(S),_T("系统提示："),MB_OK|MB_ICONWARNING)
#define  BTN_MAX 12
#define  ON_WM_RIBBON_HEADER (WM_USER + 102)
const int GroupNum = sizeof(eUSER_GROUP);
class CNextFormView;
class CHomeFormView;
class CMRibbonPage;
class CMConfigCenter;
class CMCtrlCenter;

class CMainFrame : public CFrameWndEx
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)
private:
	volatile eUSER_GROUP m_user;
	bool m_btnEnable[GroupNum][BTN_MAX+1];
public:
	void SetPropertiesWnd(CTlsData *pData)
	{
		__try
		{
			m_wndAlgorithmParameter.SetPropertyList(pData);
		}
		__except(ExpFltr(GetExceptionInformation()))
		{
		}
	};

	void SetTestListWnd(CTlsData *pData){m_wndTestListView.SetTestListWnd(pData);}
	CTestListWnd* GetTestListWndID(){return &m_wndTestListView;};

	void ReflashTestListWnd(int order){m_wndTestListView.ReflashTestListWnd(order);};
	
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

	void RunInAutoMode();
	void SetUserMode(eUSER_GROUP group);
	void OnMainCtrlInit();

	void ShowErrorLogPic(CMData * pData){m_pNextView->ShowErrorLogPic(pData);};

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	CMFCRibbonLabel * m_RibbonLbUser;
protected:  // 控件条嵌入成员
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCRibbonCategory* m_pHomeCategory;
	CMFCRibbonCategory* m_pFilterCategory;
	CMFCRibbonCategory* m_pActiveCategory;
	CMFCToolBarImages   m_PanelImages;
	CMFCToolBarImages   m_PanelImages2;
	CMFCRibbonStatusBar m_wndStatusBar;
	CStatic             m_dispHist;

	CTestTreeView     m_wndFileView;
    CTestListWnd      m_wndTestListView;
	CPropertiesWnd    m_wndAlgorithmParameter;
	CPropertiesWnd    m_wndLightParameter;

	CMFCCaptionBar    m_wndCaptionBar;
	CChildView        m_wndHomeView;

    CMFCRibbonPanel * m_pPanelHistData;

	CMFCRibbonButton* pBtnSaveSYS;
	CMFCRibbonButton* pBtnOpenCfg;
	CMFCRibbonButton* pBtnContinueGrab;

	CMFCRibbonButton* pBtnOPEN;
	CMFCRibbonButton* pBtnCFG;
	CMFCRibbonButton* pBtnRUN;
	CMFCRibbonButton* pBtnSTOP;
	CMFCRibbonButton* pBtnPAUSE;
	CMFCRibbonButton* pBtnSHOT;
	CMRibbonPage   * m_pRibbonPage;
	CMFCRibbonButton* pBtnCONTIN;
	CMFCRibbonButton* pBtnSAVE;
	CMFCRibbonButton* pBtnZERO;
    CHomeFormView   * m_pHomeView;
	CNextFormView   * m_pNextView;
// 生成的消息映射函数
protected:
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnViewCaptionBar();
	afx_msg LPARAM OnRibbonCategoryChanged(WPARAM wp, LPARAM lp);
	afx_msg void OnUpdateViewCaptionBar(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBtnCk(CCmdUI* pCmdUI);

	afx_msg LPARAM  OnReciveTLSUpdateMessage(WPARAM wParam, LPARAM lParam);//参数有无根据实际情况而定

	afx_msg LRESULT OnRibbonHeaderDraw(WPARAM wp,LPARAM lp);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
#ifdef _ENGLISH
	void InitializeRibbon_English();
#else
	void InitializeRibbon();
#endif
	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
	BOOL CreateCaptionBar();
	void GetCmdParameter(CString& strCmd);
public:

	bool CfgDlg();
	bool SelectProgramDlg();
	bool UserDlg();
	bool SysRun();
	bool SysStop();
	bool SysPause();
	bool ShotGrab();
	bool ContinueGrab();
	bool Save();
	bool Zero();
	bool SaveSys();
	bool OpenHelpTool();
	bool HoverOverErrorImages();

	afx_msg void OnBtnClicked(UINT nCmdID);

	bool OneShotGrabErrPic();
    void InitForm();
	//
	LONG ExpFltr(LPEXCEPTION_POINTERS pep);
	void SwitchToForm(UINT nForm);

	BOOL m_bInitPane;
};


