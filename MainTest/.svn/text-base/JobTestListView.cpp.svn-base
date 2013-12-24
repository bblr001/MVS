// JobTestListView.cpp : 实现文件
//

#include "stdafx.h"
#include "MainTest.h"
#include "JobTestListView.h"
#include "MCtrlCenter.h"


// CJobTestListView

IMPLEMENT_DYNCREATE(CJobTestListView, CFormView)

CJobTestListView::CJobTestListView()
	: CFormView(CJobTestListView::IDD)
{
	m_ItemCount=0;

}

CJobTestListView::~CJobTestListView()
{
}

void CJobTestListView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TESTITEM, m_TestListItem);
}

BEGIN_MESSAGE_MAP(CJobTestListView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CJobTestListView::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CJobTestListView::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CJobTestListView::OnBnClickedButtonLoad)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_TESTITEM, &CJobTestListView::OnNMDblclkListTestitem)
END_MESSAGE_MAP()


// CJobTestListView 诊断

#ifdef _DEBUG
void CJobTestListView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CJobTestListView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CJobTestListView 消息处理程序
void CJobTestListView::Init(MI_SETTING *pSetting)
{

	m_pCurrentPanel = pSetting;

	DWORD dwStyle2 = m_TestListItem.GetExtendedStyle();
	dwStyle2 |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle2 |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	dwStyle2 |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_TestListItem.SetExtendedStyle(dwStyle2); //设置扩展风格


	m_TestListItem.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	int i=0;
	m_TestListItem.InsertColumn(i++, _T("Item"), LVCFMT_LEFT, 100);
	m_TestListItem.InsertColumn(i++, _T("Test"), LVCFMT_LEFT, 100);
	m_TestListItem.InsertColumn(i++, _T("Subtest"), LVCFMT_LEFT, 100);
	m_TestListItem.InsertColumn(i++, _T("ProName"), LVCFMT_LEFT, 100);
	m_TestListItem.InsertColumn(i++, _T("ProVersion"), LVCFMT_LEFT, 100);
	m_TestListItem.InsertColumn(i++, _T("TestCount"), LVCFMT_LEFT, 100);
	m_TestListItem.InsertColumn(i++, _T("FailCount"), LVCFMT_LEFT, 100);
	m_TestListItem.InsertColumn(i++, _T("Log"), LVCFMT_LEFT, 100);
	
}
void CJobTestListView::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog   OpenTlsDlg(TRUE,NULL, NULL,OFN_HIDEREADONLY, _T("Test List File(*.tls)|*.tls| "));//open   as 


	if(OpenTlsDlg.DoModal()==IDOK) 
	{ 

		pSubTestItemList.clear();
		m_TestListItem.DeleteAllItems();

		wstring tmp(OpenTlsDlg.GetPathName());
		string fileName= ws2s(tmp);

		testItemData.SetTestList(&pSubTestItemList);
		testItemData.OpenTLS(fileName);
		m_ItemCount=0;

		for (list<CTlsData*>::iterator it = pSubTestItemList.begin();it!=pSubTestItemList.end();it++)
		{
			CString item;
			item.Format(_T("%d"),m_ItemCount);

			STLSDATA_SUBTEST* pSubTest = (*it)->GetDataSubtest();

			m_TestListItem.InsertItem(m_ItemCount, item);
			CString testName(pSubTest->testName.c_str());
			CString subtestName(pSubTest->subTestName.c_str());
			CString subtestExeName(pSubTest->exe.exeName.c_str());
			CString subtestExeVersion(pSubTest->exe.exeVersion.c_str());

			m_TestListItem.SetItemText(m_ItemCount,1,testName);
			m_TestListItem.SetItemText(m_ItemCount,2,subtestName);
			m_TestListItem.SetItemText(m_ItemCount,3,subtestExeName);
			m_TestListItem.SetItemText(m_ItemCount,4,subtestExeVersion);
			m_TestListItem.SetItemText(m_ItemCount,5,_T("0"));
			m_TestListItem.SetItemText(m_ItemCount,6,_T("0"));
			m_TestListItem.SetItemText(m_ItemCount,7,_T("0"));

			m_TestListItem.SetItemData(m_ItemCount,(DWORD_PTR)(*it));
			m_ItemCount++;
		}
	}
	OpenTlsDlg.DestroyWindow();
}

void CJobTestListView::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	if (pSubTestItemList.size()==0)
	{
		return;
	}

	//AfxMessageBox(_T("On PropertiesSave"));
	//CFileDialog   dlg(FALSE,NULL, "MyOrl.orl ",OFN_OVERWRITEPROMPT, "(*.orl)|*.orl| ");//save   as 
	CFileDialog   SaveTlsDlg(FALSE,NULL, _T("MyTLS.tls"),OFN_OVERWRITEPROMPT, _T("Test List File(*.tls)|*.tls| "));//save   as 


	if(SaveTlsDlg.DoModal()==IDOK) 
	{ 
		wstring tmp(SaveTlsDlg.GetPathName());
		string fileName= ws2s(tmp);


		testItemData.SetTestList(&pSubTestItemList);
		testItemData.SaveTLS(fileName);
		//m_TestTreeList.SaveTLS(fileName);

	}
	SaveTlsDlg.DestroyWindow();
}

void CJobTestListView::OnBnClickedButtonLoad()
{
	// TODO: 在此添加控件通知处理程序代码

	pSubTestItemList.clear();
	for(int i=0; i<m_TestListItem.GetItemCount(); i++)
	{	
		CTlsData * pData = (CTlsData*)m_TestListItem.GetItemData(i);
		pSubTestItemList.push_back(pData);
	}
	m_pCurrentPanel->pCtrlCent->m_filterCenter.SetTestItemList(&pSubTestItemList);
}


void CJobTestListView::SetTestListCtrlConect(int Item,int Column)
{
	CString   str   =   m_TestListItem.GetItemText(Item,Column); 

	int old = _tstoi(str);
	old++;
	str.Format(_T("%d"),old);
	m_TestListItem.SetItemText(Item,Column,str);
}


void CJobTestListView::SetTestListCtrlConect(int Item,int Column,CString connect)
{
	m_TestListItem.SetItemText(Item,Column,connect);
}

void CJobTestListView::OnNMDblclkListTestitem(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	switch (pNMHDR->code)
	{
		// 	case TVN_SELCHANGED:
		// 		{
		// 			//OnNotifySelChanged(wParam, lParam, pResult); 
		// 			AfxMessageBox(_T("Slect..."));
		// 			break;
		// 		}
	case NM_DBLCLK:
		{
			CString str;
			for(int i=0; i<m_TestListItem.GetItemCount(); i++)
			{
				if( m_TestListItem.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
				{
					// 					str.Format(_T("选中了第%d行"), i);
					// 					AfxMessageBox(str);
					CTlsData * pData =(CTlsData*) m_TestListItem.GetItemData(i);		

// 					CMainFrame* pMainFrame= (CMainFrame*)AfxGetMainWnd();
// 					pMainFrame->SetPropertiesWnd(pData);				
					AfxMessageBox(_T("Double Click...."));
				}
			}
			break;
		}
	default:
		break;
	}

	*pResult = 0;
}
