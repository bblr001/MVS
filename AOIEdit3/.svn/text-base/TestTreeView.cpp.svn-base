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

#include "stdafx.h"
#include "mainfrm.h"
#include "TestTreeView.h"
#include "resource.h"
#include "AOIEditVer3.h"
#include "Tools.h"
#include "MConfigCenter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestTreeView

CTestTreeView::CTestTreeView()
{
}

CTestTreeView::~CTestTreeView()
{
}

BEGIN_MESSAGE_MAP(CTestTreeView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_BTN_TESTTREE_OPEN, OnOpenTLS)
	ON_WM_SETFOCUS()
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

	if (!m_wndTestTreeView.Create(dwViewStyle, rectDummy, this, IDD_TESTREE_VIEW))
	{
		TRACE0("未能创建文件视图\n");
		return -1;      // 未能创建
	}

	// 加载视图图像:
	m_TestTreeViewImages.Create(IDB_TESTTREE_VIEW, 16, 0, RGB(255, 0, 255));
	m_wndTestTreeView.SetImageList(&m_TestTreeViewImages, TVSIL_NORMAL);

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_TESTTREE_TL);
	m_wndToolBar.LoadToolBar(IDR_TESTTREE_TL, 0, 0, TRUE /* 已锁定*/);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// 所有命令将通过此控件路由，而不是通过主框架路由:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	// 填入一些静态树视图数据(此处只需填入虚拟代码，而不是复杂的数据)
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
	defPath.Format(_T("%smastertls\\"),CMConfigCenter::GetSingletonConfigCenter()->GetLocalPath().c_str());
	OpenTlsDlg.m_ofn.lpstrInitialDir=defPath;
	if(OpenTlsDlg.DoModal()==IDOK) 
	{ 
		m_wndTestTreeView.DeleteAllItems();
		wstring tmp(OpenTlsDlg.GetPathName());
		string fileName= ws2s(tmp);
		m_TestTreeList.Init(fileName.c_str());

		TVINSERTSTRUCT tvInsert;
		tvInsert.hParent = NULL;
		tvInsert.hInsertAfter = TVI_ROOT;
		tvInsert.item.mask = TVIF_TEXT;
		tvInsert.item.pszText = _T("Root");
		HTREEITEM hRoot = m_wndTestTreeView.InsertItem(&tvInsert);
		HTREEITEM hCommon = m_wndTestTreeView.InsertItem(_T("Common"), 0, 0, hRoot);
		auto testData = m_TestTreeList.GetTestList();

		std::for_each(testData->begin(), testData->end(), [&](CTlsData& data)
		{
			switch (data.GetType())
			{
			case COMMON:
				{
					STLSDATA_COMMON* pCommon = data.GetDataCommon();
					CString commName (s2ws(pCommon->commname).c_str());
					m_wndTestTreeView.SetItemText(hCommon,commName);
					m_wndTestTreeView.SetItemData(hCommon,(DWORD_PTR)&data);
					break;
				}
			case SUBTEST:
				{
					if (!hCurrentTest) break;
					STLSDATA_SUBTEST* pSubTest = data.GetDataSubtest();
					CString testName(s2ws(pSubTest->m_strSubTestName).c_str());
					HTREEITEM hSubTest = m_wndTestTreeView.InsertItem(testName, 0, 1,hCurrentTest);
					m_wndTestTreeView.SetItemData(hSubTest,(DWORD_PTR)&data);
					break;
				}
			case TEST:
				{
					STLSDATA_TEST* pTest = data.GetDataTest();
					CString testName(s2ws(pTest->testName).c_str());
					HTREEITEM hTest = m_wndTestTreeView.InsertItem(testName, 0, 0,hRoot);
					hCurrentTest = hTest;
					m_wndTestTreeView.SetItemData(hTest,(DWORD_PTR)&data);
					break;
				}
			default:
				break;
			}
			m_wndTestTreeView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);
			m_wndTestTreeView.Expand(hRoot, TVE_EXPAND);
		});
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
void CTestTreeView::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文

	CRect rectTree;
	m_wndTestTreeView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);
	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
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
	SetControlBarStyle(AFX_CBRS_RESIZE|AFX_CBRS_AUTOHIDE|AFX_CBRS_FLOAT);
}

BOOL CTestTreeView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);
	UINT ID = (UINT)wParam;
	if(ID == IDD_TESTREE_VIEW && pNMHDR->code == NM_DBLCLK)
	{
		HTREEITEM ht = m_wndTestTreeView.GetSelectedItem();
		CTlsData *showData = (CTlsData*)m_wndTestTreeView.GetItemData(ht);
		CMainFrame* pMainFrame= (CMainFrame*)AfxGetMainWnd();
		pMainFrame->SetPropertiesWnd(showData);
	}
	return CDockablePane::OnNotify(wParam, lParam, pResult);
}


