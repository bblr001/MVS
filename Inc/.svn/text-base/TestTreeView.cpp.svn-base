
#include "stdafx.h"
#include "..\AOIEdit\MainFrm.h"
#include "TestTreeView.h"
#include "Resource.h"
#include "AOIEdit.h"
#include "Tools.h"
#include "MConfigCenter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileView

CTestTreeView::CTestTreeView()
{
	hCurrentTest=NULL;
}

CTestTreeView::~CTestTreeView()
{
}

BEGIN_MESSAGE_MAP(CTestTreeView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_BUTTON_TESTTREE_OPEN, OnOpenTLS)
	ON_WM_SETFOCUS()
	//ON_NOTIFY_REFLECT(NM_CLICK,OnNotify)   
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar 消息处理程序

int CTestTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 创建视图:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	if (!m_wndTestTreeView.Create(dwViewStyle, rectDummy, this, 4))
	{
		TRACE0("未能创建文件视图\n");
		return -1;      // 未能创建
	}

	// 加载视图图像:
 	m_TestTreeViewImages.Create(IDB_TESTTREE_VIEW, 16, 0, RGB(255, 0, 255));
 	m_wndTestTreeView.SetImageList(&m_TestTreeViewImages, TVSIL_NORMAL);
	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_TESTTREE_TOOLS);
	m_wndToolBar.LoadToolBar(IDR_TESTTREE_TOOLS, 0, 0, TRUE /* 已锁定*/);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// 所有命令将通过此控件路由，而不是通过主框架路由:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	// 填入一些静态树视图数据(此处只需填入虚拟代码，而不是复杂的数据)
	//FillTestTreeView();
	AdjustLayout();
	return 0;
}
void CTestTreeView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CTestTreeView::OnOpenTLS()
{

	CFileDialog   OpenTlsDlg(TRUE,NULL, NULL,OFN_HIDEREADONLY, _T("Test List File(*.mas)|*.mas"));//open   as 
	CString defPath;
	
	defPath.Format(_T("%smastertls\\"),CMConfigCenter::GetConfigCenter().GetLocalPath().c_str());
	OpenTlsDlg.m_ofn.lpstrInitialDir=defPath;

	if(OpenTlsDlg.DoModal()==IDOK) 
	{ 
		m_wndTestTreeView.DeleteAllItems();
		//FillTestTreeView(OpenTlsDlg.GetPathName());
	
	// 	CFileDialog   dlg(FALSE,NULL, "MyOrl.orl ",OFN_OVERWRITEPROMPT, "(*.orl)|*.orl| ");//save   as 
	// 	dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY, "AVI   files(*.avi)|*.avi| ")//open

		wstring tmp(OpenTlsDlg.GetPathName());
		string fileName= ws2s(tmp);
		m_TestTreeList.Init(fileName.c_str());

		HTREEITEM hRoot = m_wndTestTreeView.InsertItem(_T("Root"), 0, 0);
		HTREEITEM hCommon = m_wndTestTreeView.InsertItem(_T("Common"), 0, 0, hRoot);

		//HTREEITEM hTest = m_wndFileView.InsertItem(_T("Test"), 0, 0,hRoot);

		std::list<CTlsData*>* testData = m_TestTreeList.GetTestList();

		for (list<CTlsData*>::iterator testIt=testData->begin();testIt!=testData->end();testIt++)
		{
			switch ((*testIt)->GetType())
			{
			case COMMON:
				{
					STLSDATA_COMMON* pCommon = (*testIt)->GetDataCommon();
					CString commName (pCommon->commname.c_str());
					m_wndTestTreeView.SetItemText(hCommon,commName);
					m_wndTestTreeView.SetItemData(hCommon,(DWORD_PTR)(*testIt));
					break;
				}
			case SUBTEST:
				{
					if (!hCurrentTest)
					{
						break;
					}
					STLSDATA_SUBTEST* pSubTest = (*testIt)->GetDataSubtest();
					CString testName(pSubTest->subTestName.c_str());
					HTREEITEM hSubTest = m_wndTestTreeView.InsertItem(testName, 0, 0,hCurrentTest);
					m_wndTestTreeView.SetItemData(hSubTest,(DWORD_PTR)(*testIt));
					break;
				}
			case TEST:
				{
					STLSDATA_TEST* pTest = (*testIt)->GetDataTest();
					CString testName(pTest->testName.c_str());
					HTREEITEM hTest = m_wndTestTreeView.InsertItem(testName, 0, 0,hRoot);
					hCurrentTest = hTest;
					m_wndTestTreeView.SetItemData(hTest,(DWORD_PTR)(*testIt));
					break;
				}
			case ROOT:
				{
					STLSDATA_ROOT* pRoot = (*testIt)->GetDataRoot();
					CString rootName(pRoot->name.c_str());				
					m_wndTestTreeView.SetItemText(hRoot,rootName);
					m_wndTestTreeView.SetItemData(hRoot,(DWORD_PTR)(*testIt));
					break;
				}
			}

			m_wndTestTreeView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);

			m_wndTestTreeView.Expand(hRoot, TVE_EXPAND);
		}
		m_wndTestTreeView.Expand(hRoot, TVE_EXPAND);



	}
	OpenTlsDlg.DestroyWindow();


}

void CTestTreeView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndTestTreeView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// 选择已单击的项:
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
		}
	}

	pWndTree->SetFocus();
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_TESTTREE, point.x, point.y, this, TRUE);
}

void CTestTreeView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndTestTreeView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}



void CTestTreeView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndTestTreeView.SetFocus();
}

void CTestTreeView::OnChangeVisualStyle()
{
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_TESTTREE_TOOLS_24 : IDR_TESTTREE_TOOLS, 0, 0, TRUE /* 锁定 */);

	m_TestTreeViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_TESTTREE_VIEW_24 : IDB_TESTTREE_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("无法加载位图: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_TestTreeViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_TestTreeViewImages.Add(&bmp, RGB(255, 0, 255));

	m_wndTestTreeView.SetImageList(&m_TestTreeViewImages, TVSIL_NORMAL);
}



BOOL CTestTreeView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: Add your specialized code here and/or call the base class

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);
	switch (pNMHDR->code)
	{
 	case TVN_SELCHANGED:
 		{
 			//OnNotifySelChanged(wParam, lParam, pResult); 
 			//AfxMessageBox(_T("Slect..."));
			//showData->helpDescription;
			//showData->setting = false;
			//showData->property = &((*testIt).property);
			


 			break;
 		}
	case NM_DBLCLK:
		{
			//m_wndFileView.GetItem();
			//OnNotifyDBClick(wParam, lParam, pResult);
			CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndTestTreeView;

			HTREEITEM ht = pWndTree->GetSelectedItem();
			CTlsData *showData = (CTlsData*)pWndTree->GetItemData(ht);


			CMainFrame* pMainFrame= (CMainFrame*)AfxGetMainWnd();
			pMainFrame->SetPropertiesWnd(showData);
			//AfxMessageBox(_T("Double Clieck..."));
		
			break;
		}
	default:
		break;
	}

	return CDockablePane::OnNotify(wParam, lParam, pResult);
}