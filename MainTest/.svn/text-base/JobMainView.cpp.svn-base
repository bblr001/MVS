// JobMainWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "MainTest.h"
#include "JobMainView.h"

#include <pylon/PylonIncludes.h>
#include "pylon_utilities.h"
#include "MCtrlCenter.h"


// CJobMainWnd

IMPLEMENT_DYNCREATE(CJobMainView, CFormView)

CJobMainView::CJobMainView()
	: CFormView(CJobMainView::IDD)
{

		m_bHaveTestItem= FALSE;
}

CJobMainView::~CJobMainView()
{
}

void CJobMainView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SOURCE, m_ComboSource);
	DDX_Control(pDX, IDC_BUTTON_SCAN, m_BTScan);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_BTStop);
	DDX_Control(pDX, IDC_STATIC_SHOW_WINDOW, m_Static_ShowWindow);
	DDX_Control(pDX, IDC_BUTTON_CONFIG, m_BTConfig);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_BTClose);
	DDX_Control(pDX, IDC_BUTTON_LOADDLL, m_BTLoadDll);
	DDX_Control(pDX, IDC_BUTTON_RUN, m_BTRun);
}

BEGIN_MESSAGE_MAP(CJobMainView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_SCAN, &CJobMainView::OnBnClickedButtonScan)
	ON_BN_CLICKED(IDC_BUTTON_LOADDLL, &CJobMainView::OnBnClickedButtonLoaddll)
	ON_BN_CLICKED(IDC_BUTTON_RUN, &CJobMainView::OnBnClickedButtonRun)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CJobMainView::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_CONFIG, &CJobMainView::OnBnClickedButtonConfig)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CJobMainView::OnBnClickedButtonClose)
END_MESSAGE_MAP()


// CJobMainWnd 诊断

#ifdef _DEBUG
void CJobMainView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CJobMainView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


void CJobMainView::Init(MI_SETTING *pSetting)
{

	m_pCurrentPanel = pSetting;
}
// CJobMainWnd 消息处理程序

void CJobMainView::OnBnClickedButtonScan()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码

	CTlFactory *m_pTlFactory;
	// Get the transport layer factory
	m_pTlFactory = &CTlFactory::GetInstance ();
	DeviceInfoList_t m_devices;

	m_devices.clear ();
	m_pTlFactory->EnumerateDevices (m_devices);

	// Delete every item from the combo box.
	for (int i = m_ComboSource.GetCount ()-1; i >= 0; i--)
	{
		m_ComboSource.DeleteString (i);
	}

	m_ComboSource.Clear();
	m_ComboSource.AddString(_T("File"));
	m_ComboSource.AddString(_T("Folders"));
	for (DeviceInfoList_t::iterator it = m_devices.begin (); it != m_devices.end (); it++)
	{
		CString name((*it).GetFriendlyName().c_str());
		m_ComboSource.AddString (name);		
	}

	m_ComboSource.SetCurSel (1);

	//Check Test Item Count is >0...

	m_BTLoadDll.EnableWindow (TRUE);
}

void CJobMainView::OnBnClickedButtonLoaddll()
{
// 	if(!m_bHaveTestItem)
// 	{
// 		AfxMessageBox(_T("Please Input you test item..."));
// 		return;
// 	}

	m_ComboSelect = m_ComboSource.GetCurSel ();

	if (m_ComboSelect ==0)
	{
		//from 文件
		// 		CRect m_Input_Source_Rect;
		// 		m_Static_ShowWindow.GetClientRect(&m_Input_Source_Rect);		
		// 		m_WorkUnit.InitUI((Hlong)m_Static_ShowWindow.m_hWnd,m_Input_Source_Rect.Width(),m_Input_Source_Rect.Height());
		// 		m_WorkUnit.Init(false);
		// 		m_WorkUnit.Start();
	}
	if (m_ComboSelect==1)
	{
		//from 文件夹

		TCHAR strDirName[MAX_PATH];

		BROWSEINFO bi;
		CString szString = TEXT("选择一个源文件子文件夹");
		bi.hwndOwner = ::GetFocus();
		bi.pidlRoot = NULL;
		bi.pszDisplayName = strDirName;
		bi.lpszTitle = szString;
		bi.ulFlags = BIF_BROWSEFORCOMPUTER | BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS;
		bi.lpfn = NULL;
		bi.lParam = 0;
		bi.iImage = 0;

		LPITEMIDLIST pItemIDList = ::SHBrowseForFolder(&bi);
		if(pItemIDList == NULL)
		{
			return ;
		}

		::SHGetPathFromIDList(pItemIDList, strDirName);

		CString str = strDirName;
		if(str != "" && str.Right(1) != '\\')
			str += '\\';

		CStringW strTmp =(CStringW)str;
		CStringA strTmpa(strTmp.GetBuffer(0)); 
		strTmp.ReleaseBuffer();
		m_pCurrentPanel->pCtrlCent->m_cfgCenter.SetRecvFileSearchPath(strTmpa.GetBuffer(0));
		strTmpa.ReleaseBuffer(-1);

		CRect m_Input_Source_Rect;
		m_Input_Source_Rect.SetRectEmpty();

		m_Static_ShowWindow.GetClientRect(&m_Input_Source_Rect);	

		m_pCurrentPanel->pCtrlCent->m_cfgCenter.m_bRecvFileIsOn = true;
		m_pCurrentPanel->pCtrlCent->m_cfgCenter.m_bRecvCameraOn = false;
		m_pCurrentPanel->pCtrlCent->m_cfgCenter.SetUISize((Hlong)m_Static_ShowWindow.m_hWnd,m_Input_Source_Rect.Width(),m_Input_Source_Rect.Height());

		m_pCurrentPanel->pCtrlCent->Begin();




	}

	if (m_ComboSelect>=2)
	{
		m_ComboSelect-=2;
		CRect m_Input_Source_Rect;
		m_Input_Source_Rect.SetRectEmpty();

		m_Static_ShowWindow.GetClientRect(&m_Input_Source_Rect);	
		m_pCurrentPanel->pCtrlCent->m_cfgCenter.m_bRecvFileIsOn = false;
		m_pCurrentPanel->pCtrlCent->m_cfgCenter.m_bRecvCameraOn = true;
		m_pCurrentPanel->pCtrlCent->m_cfgCenter.m_iIndexCamera = m_ComboSelect;
		m_pCurrentPanel->pCtrlCent->m_cfgCenter.SetUISize((Hlong)m_Static_ShowWindow.m_hWnd,m_Input_Source_Rect.Width(),m_Input_Source_Rect.Height());
		m_pCurrentPanel->pCtrlCent->Begin();

	}
	m_BTLoadDll.EnableWindow(FALSE);
	m_BTRun.EnableWindow(TRUE);
}

void CJobMainView::OnBnClickedButtonRun()
{
	// TODO: 在此添加控件通知处理程序代码

	m_BTRun.EnableWindow(FALSE);
	m_pCurrentPanel->pCtrlCent->Start();
	m_BTStop.EnableWindow(TRUE);
}

void CJobMainView::OnBnClickedButtonStop()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pCurrentPanel->pCtrlCent->Stop();
	m_BTScan.EnableWindow(TRUE);
	m_BTLoadDll.EnableWindow(FALSE);
	m_BTRun.EnableWindow(TRUE);

}

void CJobMainView::OnBnClickedButtonConfig()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CJobMainView::OnBnClickedButtonClose()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pCurrentPanel->pCtrlCent->Close();
}




void CJobMainView::LoadTestItem(list<CTlsData*> *itemList)
{
	m_bHaveTestItem= TRUE;
	//m_ControlCent.m_cfgCenter.SetTestItemList(itemList);
	m_pCurrentPanel->pCtrlCent->m_filterCenter.SetTestItemList(itemList);

}
