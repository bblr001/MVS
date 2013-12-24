
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "AOIEDITHelp.h"
#include "afxcview.h"
#include "MainFrm.h"
#include "DoProcess/CMCtrolCenter.h"
#include "AOIEDITHelpView.h"
#include "DoProcess/CMCfgCenter.h"
#include "DoProcess/util.h"
#include "FileTree.h"
#include "PropertyFormView.h"
#include "DoProcess/ActionHalcon.h"
#include "ItemView.h"
#include "AOIEDITHelpDoc.h"
#include "Tools.h"
#include <list>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_WM_MOVE()
	// 全局帮助命令
	ON_MESSAGE(MSG_REPORT, GetReportMsg)
	ON_COMMAND(ID_BTN_SAVE, &CMainFrame::OnBtnSave)
	ON_UPDATE_COMMAND_UI(ID_BTN_SAVE, &CMainFrame::OnUpdateBtnSave)
	ON_COMMAND(ID_FINE_TUNING, &CMainFrame::OnFineTuning)
	ON_UPDATE_COMMAND_UI(ID_FINE_TUNING, &CMainFrame::OnUpdateFineTuning)
END_MESSAGE_MAP()

CMainFrame::CMainFrame():
	    m_bSplitterCreated(FALSE),
		m_bSysRun(FALSE),
		m_bSysPause(TRUE),
		m_bInitOper(FALSE),
		m_pItemViewGrid(0),
		m_pCMD(0),
		m_pPropertyView(0),
		m_bDispFileTree(false)
{
	m_ImageFileName="D:\\SLACTST\\Example.102\\sample.tiff";
	m_TLSFileName = "";
	m_pCMD = new CMCmd();
}

CMainFrame::~CMainFrame()
{
	if(0!=m_pCMD)
	{
		m_pCMD->Close();
	    delete m_pCMD;
	}
}

void CMainFrame::OnMove(int x, int y)
{
	CFrameWnd::OnMove(x,y);
}

void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType,cx,cy);
	AdjustRec(cx,cy);
}

void CMainFrame::AdjustRec(int /*cx*/,int/* cy*/)
{
	if( m_bSplitterCreated )  // m_bSplitterCreated set in OnCreateClient
	{
		CRect rect;
		GetWindowRect( &rect );
		int MarginPane = rect.Width()/7;
		int CenterPaneWidth = rect.Width()- 2*MarginPane;
		m_wndSplitter.SetColumnInfo(m_bDispFileTree?0:1, MarginPane, 100);
		m_wndSplitter.SetColumnInfo(m_bDispFileTree?1:0, CenterPaneWidth, 400);
		m_wndSplitter.RecalcLayout();
	    //MarginPane = rect.Height()/7;
		CenterPaneWidth = rect.Height()*7/10;
		//m_wndSplitter2.SetRowInfo(1, MarginPane, 50);
		m_wndSplitter2.SetRowInfo(0, CenterPaneWidth, 300);
		m_wndSplitter2.RecalcLayout();
	}
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT | TBSTYLE_TRANSPARENT) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}
	if (!m_wndDlgBar.Create(this, IDR_MAINFRAME, CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("未能创建对话栏\n");
		return -1;		// 未能创建
	}

	if (!m_wndReBar.Create(this) || !m_wndReBar.AddBar(&m_wndToolBar) || !m_wndReBar.AddBar(&m_wndDlgBar))
	{
		TRACE0("未能创建 Rebar\n");
		return -1;      // 未能创建
	}
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	return 0;
}
void CMainFrame::ManualUpdate(string name,string mvalue)
{
	m_pPropertyView->ManualUpdate(name,mvalue);
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs,CCreateContext* pContext)
{
	m_bSplitterCreated = FALSE;
	m_bDispFileTree =(L"sadmin"==theApp.m_user);
	if(!m_wndSplitter.CreateStatic(this,1,m_bDispFileTree?3:2))
	{
		TRACE(_T("Failed to CreateStaticSplitter\n"));
		return FALSE;
	}
	int ColId2 = 0;
	int ColId3 = 1;
	if(m_bDispFileTree)
	{
		if (!m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(CFileTree),CSize(240,0),pContext))
		{
			TRACE(_T("Failed to CreateStaticSplitter\n"));
			return FALSE;
		}
		ColId2 = 1;
		ColId3 = 2;
	}
	if (!m_wndSplitter2.CreateStatic(
		&m_wndSplitter,     // our parent window is the first splitter
		2, 1,               // the new splitter is 3 rows, 1 column
		WS_CHILD | WS_VISIBLE | WS_BORDER,  // style, WS_BORDER is needed
		m_wndSplitter.IdFromRowCol(0, ColId2)
		// new splitter is in the first row, 2nd column of first splitter
		))
	{
		TRACE0("Failed to create nested splitter\n");
		return FALSE;
	}
	if (!m_wndSplitter2.CreateView(0,0,pContext->m_pNewViewClass,CSize(240,0),pContext))
	{
		TRACE(_T("Failed to CreateStaticSplitter\n"));
		return FALSE;
	}
	if (!m_wndSplitter2.CreateView(1,0,RUNTIME_CLASS(CItemView),CSize(240,0),pContext))
	{
		TRACE(_T("Failed to CreateStaticSplitter\n"));
		return FALSE;
	}

	if (!m_wndSplitter.CreateView(0,ColId3,RUNTIME_CLASS(CPropertyFormView),CSize(100,0),pContext))
	{
		TRACE(_T("Failed to CreateStaticSplitter\n"));
		return FALSE;
	}
	m_pHomePaintView = (CAOIEDITHelpView*)m_wndSplitter2.GetPane(0,0);
	m_pItemViewGrid  = (CItemView*)m_wndSplitter2.GetPane(1,0);
	ASSERT(0!=m_pItemViewGrid);
	if(m_bDispFileTree){m_fileTree = (CFileTree*)m_wndSplitter.GetPane(0,0);}
	m_pPropertyView = (CPropertyFormView*)m_wndSplitter.GetPane(0,ColId3);
	m_bSplitterCreated=TRUE;
	return m_bSplitterCreated;
}


BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	cs.style = WS_THICKFRAME| WS_SYSMENU|WS_MINIMIZE|WS_MAXIMIZE|WS_MAXIMIZEBOX|WS_MINIMIZEBOX;
	return TRUE;
}

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG

void CMainFrame::SaveParameter()
{
	CString szSection ;
	CString szKey ;
#pragma warning(suppress: 6031)
	szSection.LoadString( IDS_INI_CONFIG) ;
	ASSERT(szSection != "");
#pragma warning(suppress: 6031)
	szKey.LoadString( IDS_INI_IMAGE) ;
	ASSERT(szKey != "");
}

void CMainFrame::OnClose()
{
	OnBtnStop();
	if(m_bSysRun)
	{
		MessageBox(_T("请先停止程序，然后退出系统！"),_T("系统提示:"),MB_OK|MB_ICONWARNING);
		return;
	}
	SaveParameter();
	FreeOperDll();
	CFrameWnd::OnClose();
}

void CMainFrame::ReStart()
{
   if (!m_bInitOper)
   {
	   MessageBox(_T("算子未初始化！"),_T("系统提示:"),MB_OK|MB_ICONWARNING);
	   return;
   }
}

void CMainFrame::SysInit()
{
   CString szSection ;
   CString szKey ;
#pragma warning(suppress: 6031)
   szSection.LoadString( IDS_INI_CONFIG ) ;
   ASSERT(szSection != "");
#pragma warning(suppress: 6031)
   szKey.LoadString( IDS_INI_IMAGE ) ;
   ASSERT(szKey != "");

   CRect rect;
   m_pHomePaintView->GetClientRect(&rect);
   int height = rect.Height();
   int width = rect.Width();

   m_pHomePaintView->SetScrollSizes(MM_TEXT,CSize(width,height));
   HWND WndID = m_pHomePaintView->GetWndHID();
   CMCfgCenter::GetCfgCenter().SetWndID(WndID);
   CMCfgCenter::GetCfgCenter().InitWnd(width,height);
   CMCfgCenter::GetCfgCenter().SetFilePath(ws2s(theApp.m_ImageFileName));
   CMCtrlCenter::GetCtrlCenter().m_SendMsgHWND = this->m_hWnd;
   CMCtrlCenter::GetCtrlCenter().m_HalconWindowHD = CMCfgCenter::GetCfgCenter().GetHCWnd();
   if(m_pItemViewGrid)
   {
	  m_pItemViewGrid->OnFileBind(ws2s(theApp.m_TLSFileName).c_str());
   }
   CAOIEDITHelpDoc* pDoc =(CAOIEDITHelpDoc*)theApp.m_currentDocument;
   pDoc->SetBarTileHWND(&m_wndDlgBar);
   pDoc->UPDataTitle(theApp.m_TLSFileName);
   OnFineTuning();
}

LRESULT CMainFrame::GetReportMsg(WPARAM wp, LPARAM lp)
{
	std::vector<SubTestResult>* msgData = (std::vector<SubTestResult>*)wp;
	typedef std::vector<SubTestResult>::iterator CNT_IT;
	int nItem = 0;
	for (CNT_IT it = msgData->begin();it!= msgData->end();++it)
	{
		m_pItemViewGrid->DisplayResult(nItem++,it->m_bFailSubTest);
	}

	return 0;
}

void CMainFrame::OnBtnRun()
{
	if (!m_bInitOper)
	{
		AfxMessageBox(_T("算子未初始化！"),MB_OK|MB_ICONERROR);
		return;
	}
	if(!m_bSysRun||m_bSysPause)
	{
		CMCtrlCenter::GetCtrlCenter().StartThreads();
		m_bSysRun = TRUE;
		m_bSysPause = FALSE;
	}
}
void CMainFrame::OnBtnStop()
{
	if(m_bSysRun)
	{
		CMCtrlCenter::GetCtrlCenter().StopThreads();
		if(!m_bSysPause)Sleep(100);
		m_bSysRun = FALSE;
	}
}
void CMainFrame::OnBtnPause()
{
	if(m_bSysRun/*&&!m_bSysPause*/)
	{
       CMCtrlCenter::GetCtrlCenter().ShotGrab();
	  /* m_bSysPause = TRUE;*/
	}
}
void CMainFrame::OnBtnSave()
{
	CAOIEDITHelpDoc* pDoc =(CAOIEDITHelpDoc*)theApp.m_currentDocument;
	if (m_pPropertyView)
	{
      m_pPropertyView->SaveFile();
	}
	if (m_pItemViewGrid)
	{
		m_pItemViewGrid->SaveFile();
	}
	if (pDoc)
	{
		pDoc->SaveFile(eItemList);
	}
	wchar_t tmpBuff[128];
	swprintf_s(tmpBuff,_T("%s-%s:cmd"),_T("FTS2007MICMD"),theApp.m_processID.c_str());
	m_pUiCmdProxy = new IPC_CMD_BUS(tmpBuff);

	char cmd[2]; cmd[0] = (char)UPDATE_TLS_FILE; cmd[1] = 0;
	m_pUiCmdProxy->Write(sizeof(char),cmd, 2);
	Sleep(150);
	delete m_pUiCmdProxy;
	CMCtrlCenter::GetCtrlCenter().m_bSaveBtnClicked = true;
}
void CMainFrame::OnUpdateBtnSave(CCmdUI *pCmdUI)
{
	bool bChanged = CMCtrlCenter::GetCtrlCenter().m_bParamChanged;
	bool bBtnClicked =  CMCtrlCenter::GetCtrlCenter().m_bSaveBtnClicked;
	pCmdUI->Enable(bChanged && !bBtnClicked);
}
void CMainFrame::OnUpdateBtnRun(CCmdUI *pCmdUI)
{
     pCmdUI->Enable(!m_bSysRun||m_bSysPause);
}

void CMainFrame::OnUpdateBtnStop(CCmdUI *pCmdUI)
{
	  pCmdUI->Enable(m_bSysRun);
}

void CMainFrame::OnUpdateBtnPause(CCmdUI *pCmdUI)
{
	  pCmdUI->Enable(m_bSysRun&&!m_bSysPause);
}

void CMainFrame::OnFineTuning()
{
	if(m_bSysRun)
		return;
    bool bNewOperItm =  m_pItemViewGrid->AppOperItem();
	if (bNewOperItm)
	{
		LoadOperDll();
	}
}
void CMainFrame::FreeOperDll()
{
	list<HMODULE>::iterator hinstIt = m_hinstList.begin();
	for (;hinstIt!=m_hinstList.end();hinstIt++)
	{
		 FreeLibrary(*hinstIt); 
	}
	m_hinstList.clear();
}
void CMainFrame::LoadOperDll()
{
	Hobject image;
	gen_image_const(&image,"byte",512,512); //这

   TCHAR szFilePath[MAX_PATH + 1];
   GetModuleFileName(NULL, szFilePath, MAX_PATH);
   (_tcsrchr(szFilePath, _T('\\')))[1] = 0; 
   CAOIEDITHelpDoc* pDoc =(CAOIEDITHelpDoc*)theApp.m_currentDocument;
   ListOperItem& mListItem = pDoc->GetItemList();
   ListOperItem::iterator It = mListItem.begin();
   FreeOperDll();
   list<STDoProcess>& m_pDoProcessList = pDoc->GetDoProcess();
   list<STSetParameter>& m_pSetParameterList = pDoc->GetParameterFun();
   m_pDoProcessList.clear();
   m_pSetParameterList.clear();
   CString dllName;
   int order = 0;
   for (;It!=mListItem.end();++It)
   {
	   dllName.Format(_T("%s\\%s.dll"),szFilePath,(*It)->AppName.c_str());
	   HMODULE hinst=::LoadLibrary(dllName);
	   if (NULL == hinst)
	   {
		   dllName.AppendFormat(_T("%s"),_T(" dll loaded Error!"));
		   AfxMessageBox(dllName,MB_OK|MB_ICONERROR);
		   return ;
	   }
	   DLLSetParameter pfDllFuncSetParameter=NULL;
	   pfDllFuncSetParameter = (DLLSetParameter)GetProcAddress(hinst, "SetParameter");

	   order= (*It)->order;
	   if (NULL != pfDllFuncSetParameter)
	   {
		   MapFineValue propValue = (*It)->propertyV;
		   MapFineValue::const_iterator _it = propValue.begin();
		   for (;_it!=propValue.end();++_it)
		   {
			   string parameterName(pDoc->WChar2Ansi(_it->first.c_str()));
			   string value(pDoc->WChar2Ansi(_it->second.c_str()));
			   (*pfDllFuncSetParameter)(order,parameterName,value);
		   }
	   }
	   STSetParameter stSTSetParameter;
	   stSTSetParameter.order=order;
	   stSTSetParameter.parameter = pfDllFuncSetParameter;
	   m_pSetParameterList.push_back(stSTSetParameter);
	   (*It)->stSTSetParameter = stSTSetParameter;
	   STDoProcess stSTDoPorceess;
	   stSTDoPorceess.process = (DllDoProcess)GetProcAddress(hinst, "SLACDllDoProcess");
	   stSTDoPorceess.order = order;
	   if (NULL == stSTDoPorceess.process)
	   {
		   dllName.AppendFormat(_T("%s"),_T(" dll loaded Error!"));
		   AfxMessageBox(dllName,MB_OK|MB_ICONERROR);
		   return ;
	   }
	   m_pDoProcessList.push_back(stSTDoPorceess);
	   (*It)->stSTDoPorceess =stSTDoPorceess;
	   m_hinstList.push_back(hinst);
   }
   if (m_pDoProcessList.size()!=0)
   {
	   MandrillRegionOp::m_pDoProcessList = &m_pDoProcessList;
	   m_bInitOper = TRUE;

	   Sleep(100);
	this->OnBtnRun();
   }
}
void CMainFrame::OnUpdateFineTuning(CCmdUI *pCmdUI)
{
	 pCmdUI->Enable(!m_bSysRun);
}

void CMainFrame::ReciveImage(string pid,string tls,string image)
{
	theApp.m_processID = s2ws(pid);
	theApp.m_ImageFileName = s2ws(image);
	AAction::Acquirsition::SetPath(image);

	CMCtrlCenter::GetCtrlCenter().ShotGrab();
	wstring tls_path = s2ws(tls);
	if(theApp.m_TLSFileName!=tls_path)
	{	
		theApp.m_TLSFileName = tls_path;
		CAOIEDITHelpDoc* pDoc =(CAOIEDITHelpDoc*)theApp.m_currentDocument;
		pDoc->UPDataTitle(theApp.m_TLSFileName);
		POSITION pos = pDoc->GetFirstViewPosition();
		CItemView * pItemView = 0;
		while (pos != NULL)
		{
			CView* pView = pDoc->GetNextView(pos);
			if(pView->IsKindOf(RUNTIME_CLASS(CItemView)))
			{
              pItemView = (CItemView *)pView;
			}
		} 
		if (pItemView)
		{
			pItemView->OnFileBind(ws2s(theApp.m_TLSFileName));
		}
        MessageBox(_T("算子文件有改变，请重新加载算子！"),theApp.m_TLSFileName.c_str(),MB_OK|MB_ICONINFORMATION);
	}
}