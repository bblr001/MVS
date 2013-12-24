// NextFormView.cpp : implementation file
//

#include "stdafx.h"
#include "AOIEditVer3.h"
#include "NextFormView.h"
#include "resource.h"
#include "MainFrm.h"
#include "MConfigCenter.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNextFormView

IMPLEMENT_DYNCREATE(CNextFormView, CFormView)

CNextFormView::CNextFormView()
	: CFormView(CNextFormView::IDD),
	m_cmdProxy(IPC_CMD_BUS_DEPRECATED(_T("FTS2007MIDataCFG")))
{
}
CNextFormView::~CNextFormView()
{
}

void CNextFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

void CNextFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	CRect   clientRect;  
	::GetWindowRect(::GetDesktopWindow(),&clientRect);
	auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();

	CRect pagerCtrlRect;
	CRect currentPicRect;

	pagerCtrlRect.left  = clientRect.left;
	pagerCtrlRect.top   = clientRect.bottom - 375;
	pagerCtrlRect.right = clientRect.right;
	pagerCtrlRect.bottom= clientRect.bottom;

	currentPicRect.left  = clientRect.left;
	currentPicRect.top   = clientRect.top;
    currentPicRect.bottom= pagerCtrlRect.top - 5;
	currentPicRect.right = clientRect.right;

	BOOL nRet;
	nRet = m_grabPicture.Create(NULL,WS_VISIBLE | WS_CHILD|WS_THICKFRAME,currentPicRect,this,0xffffff);
	if(!nRet)
		return;
	nRet = m_pagerctrl.Create(WS_VISIBLE | WS_CHILD | PGS_VERT ,pagerCtrlRect, this,IDC_PAGER_CTRL);
	if (!nRet)
		return;

	m_pagerctrl.GetClientRect(&pagerCtrlRect);
	if(!m_errorImgPanel.Create(IDD_DISPS,&m_pagerctrl))
		AfxMessageBox(_T("Error creating Dialog"));

	m_errorImgPanel.ShowWindow(SW_SHOW);
    m_errorImgPanel.MoveWindow(pagerCtrlRect);
	m_pageHeight = pagerCtrlRect.Height();
	int cx = pagerCtrlRect.Width() / 15 ,cy;
	m_errorImgPanel.AdjustDispViews(2,&cx,&cy);
	m_pagerctrl.SetChild(m_errorImgPanel.m_hWnd);
	m_pagerctrl.SetButtonSize(15);
	m_pagerctrl.SetBkColor(RGB(123,123,123));
	m_pagerctrl.SetBorder(3);
	m_pagerctrl.RecalcSize();
	pConfigCenter->SetLogUIWindowID((Hlong)m_grabPicture.m_hWnd);
}

BEGIN_MESSAGE_MAP(CNextFormView, CFormView)
	ON_WM_KEYDOWN()
	ON_NOTIFY(PGN_CALCSIZE, IDC_PAGER_CTRL, OnCalcSize)
	ON_NOTIFY(PGN_SCROLL,IDC_PAGER_CTRL,OnPGScroll)
	ON_NOTIFY(PGN_HOTITEMCHANGE,IDC_PAGER_CTRL,OnHotItemChg)
END_MESSAGE_MAP()

#ifdef _DEBUG
void CNextFormView::AssertValid() const
{
	CFormView::AssertValid();
}

void CNextFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

void CNextFormView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(VK_ESCAPE == nChar)
	{
		CMainFrame *pFrame = (CMainFrame *)::AfxGetApp()->m_pMainWnd;
	}
	CFormView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CNextFormView::OnCalcSize(NMHDR * pNotifyStruct, LRESULT * result)
{
	LPNMPGCALCSIZE pNMPGCALCSIZE = (LPNMPGCALCSIZE)pNotifyStruct;

	if (pNMPGCALCSIZE->dwFlag == PGF_CALCHEIGHT)
	{
		pNMPGCALCSIZE->iHeight =(m_pageHeight)*2;
	}
}

void CNextFormView::OnHotItemChg(NMHDR * pNotifyStruct, LRESULT * result)
{
	LPNMPGHOTITEM  pnmPGHotItem = (LPNMPGHOTITEM) pNotifyStruct;
	int oldItem = pnmPGHotItem->idOld;
	int newItem = pnmPGHotItem->idNew;

	if(HICF_ENTERING==pnmPGHotItem->dwFlags)
	{
		newItem = pnmPGHotItem->idNew;
	}
	else if (HICF_LEAVING == pnmPGHotItem->dwFlags)
	{
	    oldItem = pnmPGHotItem->idOld;
	}
}

void CNextFormView::OnPGScroll(NMHDR * pNotifyStruct, LRESULT * result)
{
}

void CNextFormView::ShowErrorLogPic(CMData* pData)
{
	m_errorImgPanel.ShowErrorLogPic(pData);
}

void CNextFormView::OpenHelpTool()
{
	//write image to file
	m_programname = CMConfigCenter::GetSingletonConfigCenter()->GetProgramName();

	m_imagefilename = "D:\\SLACTST\\" + m_programname;
	m_imagefilename += "\\tmp.tiff";

	m_tlsfilename = "D:\\SLACTST\\" + m_programname + "\\";
	m_tlsfilename+=CMConfigCenter::GetSingletonConfigCenter()->GetTLSFileName();

	write_image(CMConfigCenter::GetSingletonConfigCenter()->GetLogWindowImage(),"tiff",0,m_imagefilename.c_str());

	Sleep(30);

	char tmpData[256];
	memset(tmpData,0,256);
	DWORD m_dwProcessID = GetCurrentProcessId();
	sprintf_s(tmpData,"{$processID=%d;$image=%s;$tls=%s;};",m_dwProcessID,m_imagefilename.c_str(),m_tlsfilename.c_str());
	string tmp = tmpData;
	m_cmdProxy.Write(tmpData, strlen(tmpData));
}