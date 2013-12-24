
// MainFrm.h : CMainFrame 类的接口
//

#ifndef _MAINFRM_H_
#define _MAINFRM_H_
#pragma once

#include "CTLSplitter.h"
#include "DoProcess/CMData.h"
#include "../inc/ShareMem.h"
#include "../inc/TLog.h"
#include "DoProcess/ProcessComunicate.h"
#include "DlgBar.h"
#define UPD_ALL                0x00000000
#define UPD_SELECTOBJECTVIEW   0x00000001
#define UPD_DBSELECTOBJECTVIEW 0x00000002
#define UPD_DBADDNEWOBJECTVIEW 0x00000004
#define UPD_ITEMRELOAD         0x00000008
#define CH_ORDER               0
static const char* arrNameType[] = {"common","test","subtest"};
class CAOIEDITHelpView;
class CFileTree;
class CItemView;
class CPropertyFormView;

class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 属性
protected:
	BOOL m_bSplitterCreated;
	CExSplitWnd m_wndSplitter;
	CExSplitWnd m_wndSplitter2;
	CAOIEDITHelpView *m_pHomePaintView;
	CItemView * m_pItemViewGrid;
	CFileTree *m_fileTree;
	CPropertyFormView * m_pPropertyView;
	int m_currentCx;
	int m_currentCy;

	string m_processID;
	string m_TLSFileName;
	string m_ImageFileName;
	bool m_bDispFileTree;

public:
    BOOL m_bSysRun;
	BOOL m_bSysPause;
	BOOL m_bInitOper;
	CMCmd* m_pCMD;
	IPC_CMD_BUS* m_pUiCmdProxy;	

	void ManualUpdate(string name,string mvalue);
private:
	list<HMODULE> m_hinstList;
	void LoadOperDll();
	void FreeOperDll();
// 操作
public:
	void ReStart();
    void SysInit();
	void ReciveImage(string pid,string tls,string image);
// 重写
public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CToolBar          m_wndToolBar;
	CReBar            m_wndReBar;
	CDlgBar           m_wndDlgBar;

	void AdjustRec(int cx,int cy);

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMove(int x, int y);
	DECLARE_MESSAGE_MAP()
private:
	void SaveParameter();
public:
	afx_msg void OnClose();
	afx_msg void OnBtnRun();
	afx_msg void OnBtnStop();
	afx_msg void OnBtnPause();
	afx_msg void OnBtnSave();

	afx_msg void OnUpdateBtnRun(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBtnSave(CCmdUI *pCmdUI);

	afx_msg void OnUpdateBtnStop(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBtnPause(CCmdUI *pCmdUI);
	afx_msg void OnFineTuning();
	afx_msg LRESULT GetReportMsg(WPARAM, LPARAM);
	afx_msg void OnUpdateFineTuning(CCmdUI *pCmdUI);
};

#endif


