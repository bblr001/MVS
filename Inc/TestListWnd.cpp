
#include "stdafx.h"

#include "TestListWnd.h"
//#include "../AOIEdit3/Resource.h"
#include "AOIEditVer3.h"
#include "Tools.h"
#include "MainFrm.h"
#include "MCtrlCenter.h"
#include "MConfigCenter.h"

#include <assert.h>
#include <memory>
#include <sstream>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputBar

CTestListWnd::CTestListWnd():
    m_pConfigCenter(CMConfigCenter::GetSingletonConfigCenter()),
		m_pCtrlCenter(CMCtrlCenter::GetSingletonCtrlCenter())
{
	assert(m_pConfigCenter != nullptr);
	assert(m_pCtrlCenter   != nullptr);
	m_ItemCount=0;
}

CTestListWnd::~CTestListWnd()
{
	ReleaseMem();
}

BEGIN_MESSAGE_MAP(CTestListWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CONTEXTMENU()
	ON_WM_SETFOCUS()

    ON_COMMAND(ID_TESTLIST_BT_MOVE_UP, OnTestListBtMoveUp)
	ON_COMMAND(ID_TESTLIST_BT_MOVE_DOWN, OnTestListBtMoveDown)
	ON_COMMAND(ID_TESTLIST_BT_DELETE, OnTestListBtDelete)
	ON_COMMAND(ID_TESTLIST_BT_APPLY, OnTestListBtApply)

END_MESSAGE_MAP()

int  CTestListWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;
	CRect rcRect(0, 0, 0, 0);
	if (!m_wndTestItemList.GetSafeHwnd())
	{
		LONG lStyle;
		lStyle = GetWindowLong(m_hWnd, GWL_STYLE);//获取当前窗口style
		lStyle &= ~LVS_TYPEMASK; //清除显示方式位
		lStyle |= LVS_REPORT; //设置style
		SetWindowLong(m_hWnd, GWL_STYLE, lStyle);//设置style

		m_wndTestItemList.Create(WS_CHILD | WS_VISIBLE | LVS_REPORT, rcRect, this, 999999);
		m_wndTestItemList.SetExtendedStyle(LVS_EX_FULLROWSELECT|m_wndTestItemList.GetExtendedStyle());
		m_wndTestItemList.ModifyStyle(0,LVS_SHOWSELALWAYS);
		m_wndTestItemList.m_bCustomDraw = true;
		m_wndTestItemList.m_pListWnd = this;
	}

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_TESTLIST_TOOLBAR);
	m_wndToolBar.LoadToolBar(IDR_TESTLIST_TOOLBAR, 0, 0, TRUE);
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_TESTLIST_TOOLBAR_HC : IDR_TESTLIST_TOOLBAR, 0, 0, TRUE);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);
	
	InitTestListWnd();
	AdjustLayout();
	SetControlBarStyle(AFX_CBRS_RESIZE|AFX_CBRS_AUTOHIDE|AFX_CBRS_FLOAT);
	return 0;
}


void CTestListWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CTestListWnd::InitTestListWnd()
{
	DWORD dwStyle2 = m_wndTestItemList.GetExtendedStyle();
	dwStyle2 |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle2 |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	dwStyle2 |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	dwStyle2 |= LVS_EX_INFOTIP;

	m_wndTestItemList.SetExtendedStyle(dwStyle2); //设置扩展风格
	//m_wndTestItemList.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	int i=0;
	int iItemWidth = 120;
#ifdef _ENGLISH
	m_wndTestItemList.InsertColumn(i++, _T("Index"), LVCFMT_LEFT, iItemWidth - 60);
	m_wndTestItemList.InsertColumn(i++, _T("Test Name"), LVCFMT_LEFT, iItemWidth);
	m_wndTestItemList.InsertColumn(i++, _T("Subtest Name"), LVCFMT_LEFT, iItemWidth);
	
	//m_wndTestItemList.InsertColumn(i++, _T("Total Count"), LVCFMT_LEFT, iItemWidth);
	m_wndTestItemList.InsertColumn(i++, _T("Rejection Count"), LVCFMT_LEFT, iItemWidth);
	m_wndTestItemList.InsertColumn(i++, _T("(Total Count)Rejection Count(DefectRate)"), LVCFMT_LEFT, iItemWidth + 30);
	m_wndTestItemList.InsertColumn(i++, _T("Program Name"), LVCFMT_LEFT, iItemWidth + 10);
	//m_wndTestItemList.InsertColumn(i++, _T("Version"), LVCFMT_LEFT, iItemWidth);
#else
	m_wndTestItemList.InsertColumn(i++, _T("序号"), LVCFMT_LEFT, iItemWidth - 60);
	m_wndTestItemList.InsertColumn(i++, _T("测试名"), LVCFMT_LEFT, iItemWidth);
	m_wndTestItemList.InsertColumn(i++, _T("子测试名"), LVCFMT_LEFT, iItemWidth + 10);
	//m_wndTestItemList.InsertColumn(i++, _T("检测数量"), LVCFMT_LEFT, iItemWidth);
	m_wndTestItemList.InsertColumn(i++, _T("检出数量"), LVCFMT_LEFT, iItemWidth);
	m_wndTestItemList.InsertColumn(i++, _T("(总数)不良品数(不良率)"), LVCFMT_LEFT, iItemWidth);
	m_wndTestItemList.InsertColumn(i++, _T("程式名"), LVCFMT_LEFT, iItemWidth);
	//m_wndTestItemList.InsertColumn(i++, _T("版本"), LVCFMT_LEFT, iItemWidth);
#endif

}

void CTestListWnd::ReflashTestListWnd(int order)
{
	int count = m_wndTestItemList.GetItemCount();
	if (order > count)
	{
		return;
	}
	DWORD_PTR ptr = (DWORD_PTR)m_wndTestItemList.GetItemData(order);
	CTlsData* pData =(CTlsData*)ptr; 
	if(pData == nullptr) return;
	int type = (int)pData->GetType();
	if(type >= NONE && type <= COMMON)
	{
		STLSDATA_SUBTEST* pSubTest = pData->GetDataSubtest();

		CString testName = s2ws(pSubTest->testName).c_str();
		CString strSubTestName = s2ws(pSubTest->m_strSubTestName).c_str();
		CString subtestExeName = s2ws(pSubTest->exeName).c_str();
		//CString subtestExeVersion = s2ws(pSubTest->exeVersion).c_str();

		m_wndTestItemList.SetItemText(order,1,testName);
		m_wndTestItemList.SetItemText(order,2,strSubTestName);
		m_wndTestItemList.SetItemText(order,5,subtestExeName);
		//m_wndTestItemList.SetItemText(order,7,subtestExeVersion);
	}
}

void CTestListWnd::SetTestListWnd(CTlsData * pData)
{
	CString item;
	item.Format(_T("%02d"),m_ItemCount+1);

	if(SUBTEST == pData->GetType())
	{
		STLSDATA_SUBTEST* pSubTest = pData->GetDataSubtest();
		pSubTest->order = m_ItemCount;
		CTlsData tlsData;
		STLSDATA_SUBTEST* pNewSubTest = tlsData.GetDataSubtest();
		*pNewSubTest = *pSubTest;
		pNewSubTest->order = m_ItemCount;
		int index = m_wndTestItemList.InsertItem(m_ItemCount, item);

		if(!_stricmp(pSubTest->RunTest.c_str(),"YES"))
			m_wndTestItemList.SetCheck(m_ItemCount,TRUE);
		else
			m_wndTestItemList.SetCheck(m_ItemCount,FALSE);

		m_vTestData.push_back(tlsData);
		size_t sz = m_vTestData.size();

		CString testName          = s2ws(pSubTest->testName).c_str();
        CString strSubTestName    = s2ws(pSubTest->m_strSubTestName).c_str();
		CString subtestExeName    = s2ws(pSubTest->exeName).c_str();
		//CString subtestExeVersion = s2ws(pSubTest->exeVersion).c_str();
		m_wndTestItemList.SetItemText(m_ItemCount,1,testName);
		m_wndTestItemList.SetItemText(m_ItemCount,2,strSubTestName);

		//m_wndTestItemList.SetItemText(m_ItemCount,3,_T("0"));
		m_wndTestItemList.SetItemText(m_ItemCount,3,_T("0"));
		m_wndTestItemList.SetItemText(m_ItemCount,4,_T("0"));

		m_wndTestItemList.SetItemText(m_ItemCount,5,subtestExeName);
		//m_wndTestItemList.SetItemText(m_ItemCount,7,subtestExeVersion);
		DWORD_PTR tmpPtr =(DWORD_PTR)(CTlsData*)&m_vTestData[sz-1];
		m_wndTestItemList.SetItemData(m_ItemCount,tmpPtr);
		m_ItemCount++;
	}
	return ;  // return TRUE  unless you set the focus to a control
}

void CTestListWnd::OnContextMenu(CWnd* pWnd, CPoint point)
{
	if(m_pConfigCenter->GetUserGroup()==OPERATOR)
		return;
 	if (point.x == -1 && point.y == -1)
 	{
 		CRect rect;
 		GetClientRect(rect);
 		ClientToScreen(rect);
 		point = rect.TopLeft();
 		point.Offset(5, 5);
 	}
 	CWnd* pWndPopupOwner = this;
 	while (pWndPopupOwner->GetStyle() & WS_CHILD)
 	{
 		pWndPopupOwner = pWndPopupOwner->GetParent();
 	}

}

void CTestListWnd::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}
	CRect rectClient;
	GetClientRect(rectClient);

	int cyCmb = 0;
	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;
	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top + cyCmb, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);

	m_wndTestItemList.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb , rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CTestListWnd::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文

	CRect rectTree;
	m_wndTestItemList.GetWindowRect(rectTree);
	ScreenToClient(rectTree);
	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CTestListWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndTestItemList.SetFocus();
}

void CTestListWnd::SetTestListCtrlConect(int Item,int Column)
{
	CString   str =  m_wndTestItemList.GetItemText(Item,Column); 

	int old = _tstoi(str);
	old++;
	str.Format(_T("%d"),old);
	SetTestListCtrlConect(Item,Column,str);
}

void CTestListWnd::SetTestListCtrlConect(int Item,int Column,CString connect)
{	
	m_wndTestItemList.SetItemText(Item,Column,connect);
}

void CTestListWnd::SetTestListCtrlConect(int Item,int Column,int connect)
{
	CString   str = m_wndTestItemList.GetItemText(Item,Column); 

	int old = _tstoi(str);
	old+=connect;
	str.Format(_T("%d"),old);
	SetTestListCtrlConect(Item,Column,str);
}

BOOL CTestListWnd::PreTranslateMessage(MSG* pMsg)
{
	return CDockablePane::PreTranslateMessage(pMsg);
}

BOOL CTestListWnd::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);
	if(pNMHDR->code == NM_DBLCLK)
	{
		CString str;
		for(int i=0; i<m_wndTestItemList.GetItemCount(); i++)
		{
			CTlsData * pData = nullptr;
			pData =(CTlsData*) m_wndTestItemList.GetItemData(i);
			pData->GetDataSubtest()->ShowObject = false;
		}
		for(int i=0; i<m_wndTestItemList.GetItemCount(); i++)
		{
			CTlsData * pData = nullptr;
			if( m_wndTestItemList.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
			{
				if(!m_wndTestItemList.GetCheck(i))
				{
				#ifdef _ENGLISH
					AfxMessageBox(_T("Please open this test items, and then adjust the test parameters"));
				#else
					AfxMessageBox(_T("请打开此测试项, 再进行测试参数的调整"));
				#endif
					
					break;
				}
				pData =(CTlsData*) m_wndTestItemList.GetItemData(i);	
				pData->GetDataSubtest()->ShowObject = true;
				CMainFrame* pMainFrame= (CMainFrame*)AfxGetMainWnd();
				pMainFrame->SetPropertiesWnd(pData);
				m_wndTestItemList.SetItemState(i,0,LVIS_SELECTED|LVIS_FOCUSED);
			}
			
		}
	}
	return CDockablePane::OnNotify(wParam, lParam, pResult);
}

void CTestListWnd::OnTestListBtMoveUp()
{
	m_wndTestItemList.OnItemMoveUP();
}

void CTestListWnd::OnTestListBtMoveDown()
{
	m_wndTestItemList.OnItemMoveDOWN();
}

void CTestListWnd::OnTestListBtDelete()
{
	m_wndTestItemList.OnItemDelete();
}

void CTestListWnd::OnTestListBtApply()
{
	if (m_pCtrlCenter->GetSysStatus() == RUNNING)
	{
#ifdef _ENGLISH
		AfxMessageBox(_T("Please suspend the system than application of the system parameters"));
#else
AfxMessageBox(_T("请先将系统暂停再应用程式参数"));
#endif
		
		
		return;
	}
	std::vector<CTlsData> tmpTlsData;
	for(int i=0; i<m_wndTestItemList.GetItemCount(); i++)
	{
		DWORD_PTR ptr = (DWORD_PTR)m_wndTestItemList.GetItemData(i);
		CTlsData* pData = (CTlsData*)(ptr);
		auto ptrSubtest = pData->GetDataSubtest();
		ptrSubtest->RunTest = m_wndTestItemList.GetCheck(i)?"YES":"NO";
		ptrSubtest->order = i;
		tmpTlsData.push_back(*pData);
	}
	m_wndTestItemList.DeleteAllItems();
	m_wndTestItemList.SetItemCount(32);
	m_vTestData.clear();
	m_vTestData.reserve(32);
	m_vTestData.assign(tmpTlsData.begin(), tmpTlsData.end());
	m_pConfigCenter->SetTestItemList(&m_vTestData);

	CString item;
	m_ItemCount = 0;
	std::for_each(m_vTestData.begin(), m_vTestData.end(), [&](CTlsData& data)
	{
		STLSDATA_SUBTEST* pSubTest = data.GetDataSubtest();
		item.Format(_T("%02d"),pSubTest->order + 1);
		m_wndTestItemList.InsertItem(m_ItemCount, item);

		CString testName = s2ws(pSubTest->testName).c_str();
		CString strSubTestName = s2ws(pSubTest->m_strSubTestName).c_str();
		CString subtestExeName = s2ws(pSubTest->exeName).c_str();
		//CString subtestExeVersion = s2ws(pSubTest->exeVersion).c_str();
		pSubTest->order = m_ItemCount;

		if(!_stricmp(pSubTest->RunTest.c_str(),"YES"))
			m_wndTestItemList.SetCheck(m_ItemCount,TRUE);
		else
			m_wndTestItemList.SetCheck(m_ItemCount,FALSE);
		
		m_wndTestItemList.SetItemText(m_ItemCount,1,testName);
		m_wndTestItemList.SetItemText(m_ItemCount,2,strSubTestName);


		//m_wndTestItemList.SetItemText(m_ItemCount,3,_T("0"));
		m_wndTestItemList.SetItemText(m_ItemCount,3,_T("0"));
		m_wndTestItemList.SetItemText(m_ItemCount,4,_T("0"));
		m_wndTestItemList.SetItemText(m_ItemCount,5,subtestExeName);
		//m_wndTestItemList.SetItemText(m_ItemCount,7,subtestExeVersion);

		DWORD_PTR tmpPtr =(DWORD_PTR)(CTlsData*)&m_vTestData[m_ItemCount];
		m_wndTestItemList.SetItemData(m_ItemCount,tmpPtr);
		m_ItemCount++;
	});
	m_wndTestItemList.SortColumn(0,true);
	m_pConfigCenter->SetTestItemList(&m_vTestData);
	CMCtrlCenter::GetSingletonCtrlCenter()->UpdateTestItem();
} 

void CTestListWnd::SaveTestList()
{
	if (m_vTestData.size()==0)
	{
		return;
	}
	wstring tmp;
	tmp=m_pConfigCenter->GetTestProgramPath()+_T("\\");

	string fileName= ws2s(tmp);
	fileName+=m_pConfigCenter->GetProgramName()+"\\";
	fileName+=m_pConfigCenter->GetTLSFileName();
	
	m_testItemData.SetTestList(&m_vTestData);
	m_testItemData.SaveTLS(fileName);
	
}

void CTestListWnd::ReleaseMem()
{
	m_vTestData.clear();
}

void CTestListWnd::InitTestList(string fileName)
{
    ReleaseMem();
	m_wndTestItemList.DeleteAllItems();
	m_wndTestItemList.SetItemCount(32);
	m_vTestData.reserve(32);
	m_vTestData.clear();
	m_testItemData.SetTestList(&m_vTestData);
	m_testItemData.OpenTLS(fileName);
	m_ItemCount = 0;
	CString item;
	std::for_each(m_vTestData.begin(), m_vTestData.end(), [&](CTlsData& data)
	{
		STLSDATA_SUBTEST* pSubTest = data.GetDataSubtest();
		item.Format(_T("%02d"),m_ItemCount + 1);
		int index = m_wndTestItemList.InsertItem(m_ItemCount, item);

		CString testName =s2ws(pSubTest->testName).c_str();
		CString strSubTestName = s2ws(pSubTest->m_strSubTestName).c_str();
		CString subtestExeName = s2ws(pSubTest->exeName).c_str();
		//CString subtestExeVersion = s2ws(pSubTest->exeVersion).c_str();
		pSubTest->order = m_ItemCount;

		if(!_stricmp(pSubTest->RunTest.c_str(),"YES"))
			m_wndTestItemList.SetCheck(m_ItemCount,TRUE);
		else
			m_wndTestItemList.SetCheck(m_ItemCount,FALSE);
		
		m_wndTestItemList.SetItemText(m_ItemCount,1,testName);
		m_wndTestItemList.SetItemText(m_ItemCount,2,strSubTestName);

		//m_wndTestItemList.SetItemText(m_ItemCount,3,_T("0"));
		m_wndTestItemList.SetItemText(m_ItemCount,3,_T("0"));
		m_wndTestItemList.SetItemText(m_ItemCount,4,_T("0"));

		m_wndTestItemList.SetItemText(m_ItemCount,5,subtestExeName);
		//m_wndTestItemList.SetItemText(m_ItemCount,7,subtestExeVersion);
		DWORD_PTR tmpPtr =(DWORD_PTR)(CTlsData*)&m_vTestData[m_ItemCount];
		m_wndTestItemList.SetItemData(m_ItemCount,tmpPtr);
		m_ItemCount++;
	});
	m_wndTestItemList.SortColumn(0,true);
	m_pConfigCenter->SetTestItemList(&m_vTestData);
}