// TestChanelPage.cpp : 实现文件
//

#include "stdafx.h"
#include "SLACMVSN.h"
#include "TestChanelPage.h"
#include "TypeCent.h"
#include "MI_DataConfig.h"
#include "MI_PanelCenter.h"
#include "DlgShowData.h"
#include "MI_ControlCenter.h"
#include "TLog.h"
#include "WarningDlg.h"
// CTestChanelPage 对话框

IMPLEMENT_DYNAMIC(CTestChanelPage, CPropertyPage)

CTestChanelPage::CTestChanelPage(wstring szStationID)
	: CPropertyPage(CTestChanelPage::IDD)
{
	m_StationID = szStationID;
	m_ErrorDisplayWinID_Halcon=0;

}

CTestChanelPage::~CTestChanelPage()
{
}

void CTestChanelPage::SetMonitorImage(Hobject * image,bool st)
{
	disp_obj(*image,m_ErrorDisplayWinID_Halcon);

	if (st)
	{
		//pass
		m_lbStatus.SetColor(RGB(255,0,255),RGB(50,255,0));
	}
	else
	{
		//fail
		m_lbStatus.SetColor(RGB(0,0,255),RGB(255,255,0));
	}
		m_lbStatus.Invalidate();

}
void CTestChanelPage::SetDBName(char * pcdbname,int len)
{
	strcpy_s(m_strDbname,len,pcdbname);
}
void CTestChanelPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TOTALNUM, m_lbTotalNum);
	DDX_Control(pDX, IDC_FAUTYNUM, m_lbFautyNum);
	DDX_Control(pDX, IDC_OKNUM, m_lbOkNum);
	DDX_Control(pDX, IDC_STATIC_01, m_lbNUM_01);
	DDX_Control(pDX, IDC_STATIC_02, m_lbNUM_02);
	DDX_Control(pDX, IDC_STATIC_03, m_lbNUM_03);
	DDX_Control(pDX, IDC_COMBO2, m_cbxProName);
	DDX_Control(pDX,IDC_LIST1,m_ltcTestItem);
	DDX_Control(pDX, IDC_STATIC_LOGPIC, m_MonitorPhoto);
}
BOOL CTestChanelPage::Init()
{
	CRect* rt= new CRect();
	rt->left = 5;
	rt->top = 5;
	rt->bottom = rt->top + ZOOM_IMAGE_H-5;
	rt->right = rt->left + ZOOM_IMAGE_W-5;

	if (0!=m_ErrorDisplayWinID_Halcon)
	{
		close_window(m_ErrorDisplayWinID_Halcon);
	}

 	Hobject  initIimage;
 	unsigned char  image[ZOOM_IMAGE_W*ZOOM_IMAGE_H];
 	int            r,c;
 	for (r=0; r<ZOOM_IMAGE_H; r++)
 		for (c=0; c<ZOOM_IMAGE_W; c++)
 			image[r*ZOOM_IMAGE_W+c] = c % 255;

 	gen_image1(&initIimage,"byte",ZOOM_IMAGE_W,ZOOM_IMAGE_H,(long)image);

	if (0==m_ErrorDisplayWinID_Halcon)
	{
		set_check("~father");
		open_window(rt->left,rt->top,rt->Width(),rt->Height(),(Hlong)m_MonitorPhoto.m_hWnd,"visible","",&m_ErrorDisplayWinID_Halcon);	
		set_check("father");
	}
	set_draw(m_ErrorDisplayWinID_Halcon,"margin"); //margin or fill
	set_color(m_ErrorDisplayWinID_Halcon,"red");
	set_line_width(m_ErrorDisplayWinID_Halcon,HTuple(1));
	disp_obj(initIimage,m_ErrorDisplayWinID_Halcon);
	delete rt;
	return TRUE;
}
int CTestChanelPage::OnCreate(LPCREATESTRUCT lpCreateStruct )
{
	if(CPropertyPage::OnCreate(lpCreateStruct)==-1)
	{
		return -1;
	}
	CRect rt;
	this->GetClientRect(&rt);
	m_lbStatus.Create(_T("   在线"),WS_CHILD|WS_VISIBLE,CRect(rt.right - 160,25,rt.right-5,150),this);
	m_lbStatus.SetColor(RGB(255,255,255),RGB(0,255,0));
	m_lbStatus.SetTxtFont(42,FW_BOLD);
	

	m_lbPragramName.Create(_T(""),WS_CHILD|WS_VISIBLE,CRect(rt.right - 165,170,rt.right-5,190),this);
	m_lbPragramName.SetColor(RGB(255,255,255),RGB(bkgndR,bkgndG,bkgndB));
	m_lbPragramName.SetTxtFont(25,FW_BOLD);

	m_lbInfoMsg.Create(_T("程序正在运行中"),WS_CHILD|WS_VISIBLE,CRect(rt.right - 165,210,rt.right-5,230),this);
	m_lbInfoMsg.SetColor(RGB(255,255,255),RGB(bkgndR,bkgndG,bkgndB));
	m_lbInfoMsg.SetTxtFont(25,FW_BOLD);
	m_lbTotalNum.SetColor(RGB(255,255,255),RGB(0,230,0));
	m_lbTotalNum.SetTxtFont(15,FW_BOLD);
	m_lbFautyNum.SetColor(RGB(255,255,255),RGB(220,0,0));
	m_lbFautyNum.SetTxtFont(15,FW_BOLD);
	m_lbOkNum.SetColor(RGB(255,255,255),RGB(0,0,250));
	m_lbOkNum.SetTxtFont(15,FW_BOLD);
    
	m_lbNUM_01.SetColor(RGB(0,0,0),RGB(100,200,250));
	m_lbNUM_01.SetTxtFont(18,FW_BOLD);
	m_lbNUM_02.SetColor(RGB(0,0,0),RGB(100,200,250));
	m_lbNUM_02.SetTxtFont(18,FW_BOLD);
	m_lbNUM_03.SetColor(RGB(0,0,0),RGB(100,200,250));
	m_lbNUM_03.SetTxtFont(18,FW_BOLD);
	if (!m_btnLoad.LoadBitmaps(IDB_BITMAP_DISPLAYVWUP,IDB_BITMAP_DISPLAYVWDOWM))
	{
		TRACE0("Failed to load bitmaps for buttons\n");
		AfxThrowResourceException();

	}
    if(!m_btnOffLine.LoadBitmaps(IDB_BITMAP_OFF,IDB_BITMAP_OFFLINEDOWN,IDB_BITMAP_OFF,IDB_BITMAP_OFFLINEDIABLE))
	{
		TRACE0("Failed to load bitmaps for buttons\n");
		AfxThrowResourceException();
	}
	if(!m_btnOnLine.LoadBitmaps(IDB_BITMAP_ONLINEUP,IDB_BITMAP_ONLINEDOWN,IDB_BITMAP_ONLINEUP,IDB_BITMAP_ONLINEDISABLE))
	{
		TRACE0("Failed to load bitmaps for buttons\n");
		AfxThrowResourceException();
	}
	if(!m_btnOpen.LoadBitmaps(IDB_BITMAP_OPENUP,IDB_BITMAP_OPENDOWN))
	{
		TRACE0("Failed to load bitmaps for buttons\n");
		AfxThrowResourceException();
	}//
	if(!m_btnHistoryData.LoadBitmaps(IDB_BITMAP_LOADUP,IDB_BITMAP_LOADDOWN))
	{
		TRACE0("Failed to load bitmaps for buttons\n");
		AfxThrowResourceException();
	}//m_btnHistoryData
	if(!m_btnOkPic.LoadBitmaps(IDB_BITMAP_OKPICUP,IDB_BITMAP_OKPICDOWN,IDB_BITMAP_OKPICUP,IDB_BITMAP_OKPICUP1))
	{
		TRACE0("Failed to load bitmaps for buttons\n");
		AfxThrowResourceException();
	}
	if(!m_btnNoPic.LoadBitmaps(IDB_BITMAP_NOPICUP,IDB_BITMAP_NOPICDOWN,IDB_BITMAP_NOPICUP,IDB_BITMAP_NOPICUP1))
	{
		TRACE0("Failed to load bitmaps for buttons\n");
		AfxThrowResourceException();
	}

	if(!m_btnWarning.LoadBitmaps(IDB_BITMAP_WARNING_UP,IDB_BITMAP_WARNING_DOWN,NULL,IDB_BITMAP_WARNING_DOWN))
	//if(!m_btnWarning.LoadBitmaps(IDB_BITMAP_OKPICUP,IDB_BITMAP_OKPICDOWN,IDB_BITMAP_OKPICUP,IDB_BITMAP_OKPICUP1))
	{
		TRACE0("Failed to load bitmaps for buttons\n");
		AfxThrowResourceException();
	}

	//m_btnWarning.SizeToContent();  

	
	return 0;
}
BOOL CTestChanelPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	CFont font;
	font.CreateFont(
		25,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		18,	                // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("Arial"));
	this->SetFont(&font);
	VERIFY(m_btnLoad.SubclassDlgItem(IDC_BTN_LOAD, this));
	VERIFY(m_btnOnLine.SubclassDlgItem(IDC_BTN_ONLINE,this));
	VERIFY(m_btnOffLine.SubclassDlgItem(IDC_BTN_OFFLINE,this));

	VERIFY(m_btnOkPic.SubclassDlgItem(IDC_BTN_OKPIC, this));
	VERIFY(m_btnNoPic.SubclassDlgItem(IDC_BTN_NOPIC,this));
	VERIFY(m_btnOpen.SubclassDlgItem(IDC_BTN_OPEN,this));
	VERIFY(m_btnWarning.SubclassDlgItem(IDC_BT_WARNING,this));
	VERIFY(m_btnHistoryData.SubclassDlgItem(IDC_BTN_QUERY,this));
	HICON hIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICONLIST1), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_cbxProName.SetFont(&font);
	m_cbxProName.SetIcon(hIcon,TRUE);
	m_cbxProName.SetItemHeight(-1,22);
	m_cbxProName.SetItemHeight(0,18);
	m_cbxProName.SetMinVisibleItems(3);
	m_cbxProName.SetCueBanner(_T("可从下拉项中选择所要加载的程序"));

	DWORD dwstyle = m_ltcTestItem.GetExtendedStyle();
    //
 
	this->UpdateData(TRUE);
	LV_COLUMN lvc;
	lvc.mask = LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH;

	lvc.iSubItem = 0;
	lvc.pszText = _T("编号");
	lvc.cx = 100;
	m_ltcTestItem.InsertColumn(0,&lvc);

	lvc.iSubItem = 1;
	lvc.pszText = _T("检测项目");
	lvc.cx = 150;
	m_ltcTestItem.InsertColumn(1,&lvc);
	
	lvc.iSubItem = 2;
	lvc.pszText = _T("检测内容");
	lvc.cx = 150;
	m_ltcTestItem.InsertColumn(2,&lvc);
	
	lvc.iSubItem = 3;
	lvc.pszText = _T("不良盖数");
	lvc.cx = 175;
    m_ltcTestItem.InsertColumn(3,&lvc);

	m_btnOffLine.EnableWindow(FALSE);
	m_btnNoPic.EnableWindow(FALSE);
	m_ltcTestItem.SetExtendedStyle(dwstyle|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES);
	m_ltcTestItem.SetFont(&font);
    m_ltcTestItem.SetBkColor(RGB(255,255,225));

	m_ltcTestItem.EnableWindow(FALSE);
	SetWindowPos(&wndTopMost,0,0,1280,1024,SWP_SHOWWINDOW);
	return TRUE;
}
//void CTestChanelPage::InsertItems(list<CString>* arrItem)
//{
//	LV_ITEM lvi;
//	int i=0;
//	m_ltcTestItem.DeleteAllItems();
//	for(list<CString>::iterator It=arrItem->begin();It!=arrItem->end();++It)
//	{
//		lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
//		lvi.iItem = i;
//		lvi.iSubItem = 0;
//		lvi.pszText = (LPWSTR)(*It).GetBuffer();
//		lvi.iImage = i;
//		lvi.stateMask = LVIS_STATEIMAGEMASK;
//		lvi.state = INDEXTOSTATEIMAGEMASK(1);
//		m_ltcTestItem.InsertItem(&lvi);
//		++It;
//		m_ltcTestItem.SetItemText(i,1,(LPWSTR)(*It).GetBuffer());
//		++It;
//		m_ltcTestItem.SetItemText(i,2,(LPWSTR)(*It).GetBuffer());
//		i++;
//	}
//}
void CTestChanelPage::OnPaint()
{
	CPropertyPage::OnPaint();
//   CPaintDC dc(this);
//   dc.Rectangle(&this->m_rtPhotoArea);
//   dc.TextOutW(270,m_rtPhotoArea.top+100,_T("图像绘制区域"),6);
//   dc.SetBkColor((0,200,100));
}
BEGIN_MESSAGE_MAP(CTestChanelPage, CPropertyPage)
 //{{AFX_MSG_MAP(CTestChanelPage)
  ON_WM_CREATE()
  ON_WM_PAINT()
  ON_WM_ERASEBKGND()
  ON_WM_CTLCOLOR()
 //}}
 ON_BN_CLICKED(IDC_BTN_ONLINE, &CTestChanelPage::OnBnClickedBtnOnline)
 ON_BN_CLICKED(IDC_BTN_OFFLINE, &CTestChanelPage::OnBnClickedBtnOffline)
 ON_BN_CLICKED(IDC_BTN_NOPIC, &CTestChanelPage::OnBnClickedBtnNopic)
 ON_BN_CLICKED(IDC_BTN_OKPIC, &CTestChanelPage::OnBnClickedBtnOkpic)
 ON_CBN_SELCHANGE(IDC_COMBO2, &CTestChanelPage::OnCbnSelchangeCombo2)
 ON_BN_CLICKED(IDC_BTN_OPEN, &CTestChanelPage::OnBnClickedBtnOpen)
 ON_BN_CLICKED(IDC_BTN_QUERY,&CTestChanelPage::OnBnClickedBtnQuery)
 ON_BN_CLICKED(IDC_BT_WARNING,&CTestChanelPage::OnBnClickedBtnWarning)
END_MESSAGE_MAP()


// CTestChanelPage 消息处理程序
BOOL CTestChanelPage::OnEraseBkgnd(CDC* pDC)
{
	COLORREF   m_crBackground;   
	CBrush     m_wndbkBrush;    
	m_crBackground=RGB(bkgndR,bkgndG,bkgndB);//想要改成的颜色       
	m_wndbkBrush.CreateSolidBrush(m_crBackground);      
	CPropertyPage::OnEraseBkgnd(pDC);//这里要看基类是什么就用哪个类.   
	CRect rect;   
	GetClientRect(rect);   
	pDC->FillRect(&rect,&m_wndbkBrush);
	return TRUE;
}
HBRUSH CTestChanelPage::OnCtlColor(CDC* pDC,CWnd* pWnd,UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC,pWnd,nCtlColor);
	switch(nCtlColor)
	{
	case CTLCOLOR_BTN:
		pDC->SetBkColor(RGB(200,220,245));
		break;
	case CTLCOLOR_DLG:
		pDC->SetBkColor(RGB(200,220,245));
		break;
	default:
		break;
	}
	return hbr;
}
void CTestChanelPage::OnBnClickedBtnOnline()
{
	
	//MI_SETTING* data = CMI_DataConfig::GetDataConfig().GetSettingData(m_StationID);
	CMyPanel* panel = CMI_PanelCenter::GetPanelCenter().GetPanel(m_StationID);
	if (panel->ClickedRun())
	{
		SetState(MTI_GUI_RUN);
		m_btnOnLine.EnableWindow(FALSE);
		m_btnOffLine.EnableWindow(TRUE);
		OnBnClickedBtnNopic();
	}
}


void CTestChanelPage::OnBnClickedBtnWarning()
{
	CWarningDlg dlg;
	if (dlg.DoModal()==IDOK)
	{
		CMI_ControlCenter::GetInstance().SetPortST(CMI_DataConfig::GetDataConfig().GetRPort(),0);
		m_btnWarning.EnableWindow(FALSE);
		CMyPanel* panel = CMI_PanelCenter::GetPanelCenter().GetPanel(m_StationID);
		panel->ClickedWarning();
	}
	dlg.DestroyWindow();

}



void CTestChanelPage::OnBnClickedBtnOffline()
{
	CMyPanel* panel = CMI_PanelCenter::GetPanelCenter().GetPanel(m_StationID);
	if (panel->ClickedPause())
	{
		SetState(MTI_GUI_PAUSE);
		m_btnOnLine.EnableWindow(TRUE);
		m_btnOffLine.EnableWindow(FALSE);
	}
}
void CTestChanelPage::OnBnClickedBtnNopic()
{
	CMyPanel* panel = CMI_PanelCenter::GetPanelCenter().GetPanel(m_StationID);
	if (panel->ClickedShowNGPic())
	{
		m_btnOkPic.EnableWindow(TRUE);
		m_btnNoPic.EnableWindow(FALSE);
	}
}

void CTestChanelPage::OnBnClickedBtnOkpic()
{
	CMyPanel* panel = CMI_PanelCenter::GetPanelCenter().GetPanel(m_StationID);
	if (panel->ClickedShowAllPic())
	{
		m_btnOkPic.EnableWindow(FALSE);
		m_btnNoPic.EnableWindow(TRUE);
	}
}
void CTestChanelPage::OnBnClickedBtnQuery()
{
	CDlgShowHistoryData dlg;
	dlg.SetDbName(m_strDbname,256);
	dlg.InitConnect();
	dlg.DoModal();
}
void CTestChanelPage::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CTestChanelPage::OnBnClickedBtnOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	MI_SETTING* wMI = CMI_DataConfig::GetDataConfig().GetSettingData(m_StationID);
	//MI_SETTING* wMI =  (MI_SETTING*)wPanel;
	PROCESS_INFORMATION *pi = &(wMI->m_pi);
	HANDLE  hProcess = OpenProcess(PROCESS_QUERY_INFORMATION , FALSE, pi->dwProcessId);
	if(hProcess == NULL)
	{
		//创建新的进程
		//AfxMessageBox(_T("This Chanel is Close."));
		int ret = MessageBox(_T("This Chanel is Close.ReCreate it."),_T("Chanel Error"),MB_YESNO);
		if (ret ==IDYES)
		{
			wchar_t m_sCurrentPath[MAX_PATH];
			GetCurrentDirectory(MAX_PATH,m_sCurrentPath);
			CString ApplicationName;
			ApplicationName=m_sCurrentPath;
			ApplicationName+=_T("\\AOIEDIT.EXE");
			STARTUPINFO si;
			ZeroMemory(&si,sizeof(si)); 
			si.cb   =   sizeof   STARTUPINFO; 
			si.lpReserved=NULL;    
			si.lpDesktop=NULL;    
			si.lpTitle=NULL;    
			si.dwX=0;
			si.dwY=0;
			si.dwXSize=0;
			si.dwYSize=0;
			si.dwXCountChars=500;
			si.dwYCountChars=500;
			si.dwFlags=STARTF_USESHOWWINDOW|STARTF_USESTDHANDLES;    
			si.wShowWindow=SW_HIDE;    
			//说明进程将以隐藏的方式在后台执行    
			si.cbReserved2=0;    
			si.lpReserved2=NULL;    
			si.hStdInput=stdin;    
			si.hStdOutput=stdout;    
			si.hStdError=stderr;  

			//C:\\WINDOWS\\SYSTEM32\\NOTEPAD.EXE")

			CString cmd;
			cmd.Format(_T("%s$%s$%d$"),wMI->szStationID,wMI->szProgramName,wMI->ch);
			BOOL fRet=CreateProcess(ApplicationName,cmd.GetBuffer(),NULL,NULL,TRUE,NULL ,NULL,NULL,&si,&(wMI->m_pi));
			if(fRet==false)   
			{   
				AfxMessageBox(_T("CreateProcess    failed"));   
				//exit(1);
			}   
			else   
			{   
				WaitForInputIdle(wMI->m_pi.hProcess,0);   
				CloseHandle(wMI->m_pi.hThread);   
				CloseHandle(wMI->m_pi.hProcess);   
			}
			Sleep(100);
			CMyPanel* panel = CMI_PanelCenter::GetPanelCenter().GetPanel(m_StationID);
			panel->ClickedOpenChanel(wMI->m_pi.dwProcessId);
			EnumThreadWindows(pi->dwThreadId,EnumThreadWndProc,MI_SHOW);
		}
		return ;
	}
	EnumThreadWindows(pi->dwThreadId,EnumThreadWndProc,MI_SHOW);
	::CloseHandle(hProcess);

	return ;
}


VOID CTestChanelPage::SetState(eMTI_GUI_STATE state)
{
	switch(state) 
	{
	case MTI_GUI_IDLE:
		m_lbStatus.SetWindowText(_T(" 等侍"));		
		m_lbStatus.SetColor(RGB(0,102,0),RGB(180,180,180));
		m_lbStatus.SetTxtFont(48,FW_BOLD);
		m_btnOnLine.EnableWindow(TRUE);
		m_btnOffLine.EnableWindow(FALSE);
		m_btnOkPic.EnableWindow(TRUE);
		m_btnNoPic.EnableWindow(FALSE);
		break;
	case MTI_GUI_RUN:
		m_lbStatus.SetWindowText(_T(" 在线中"));
		m_lbStatus.SetColor(RGB(0,0,255),RGB(0,255,0));
		m_lbStatus.SetTxtFont(48,FW_BOLD);
		SetTimer(UM_CONTER, 1000, NULL);
		m_btnOnLine.EnableWindow(FALSE);
		m_btnOffLine.EnableWindow(TRUE);
		break;
	case MTI_GUI_STOP:
		m_lbStatus.SetWindowText(_T(" 停止"));
		m_lbStatus.SetColor(RGB(0,102,0),RGB(180,180,180));
		m_lbStatus.SetTxtFont(48,FW_BOLD);
		m_btnOnLine.EnableWindow(FALSE);
		m_btnOffLine.EnableWindow(FALSE);
		m_btnOkPic.EnableWindow(FALSE);
		m_btnNoPic.EnableWindow(FALSE);
		break;
	case MTI_GUI_PAUSE:
		m_lbStatus.SetWindowText(_T(" 离线"));
		m_lbStatus.SetColor(RGB(0,102,0),RGB(180,180,180));
		m_lbStatus.SetTxtFont(48,FW_BOLD);
		m_btnOnLine.EnableWindow(TRUE);
		m_btnOffLine.EnableWindow(FALSE);
		break;
	case MTI_GUI_INIT:
		m_btnOnLine.EnableWindow(TRUE);
		m_btnOffLine.EnableWindow(FALSE);
		break;

	case MTI_GUI_EXIT:
		m_lbStatus.SetWindowText(_T(" 退出"));
		m_lbStatus.SetColor(RGB(0,102,0),RGB(180,180,180));
		m_lbStatus.SetTxtFont(48,FW_BOLD);
		m_btnOnLine.EnableWindow(FALSE);
		m_btnOffLine.EnableWindow(FALSE);
		m_btnOnLine.EnableWindow(FALSE);
		m_btnOffLine.EnableWindow(FALSE);
		m_btnOkPic.EnableWindow(FALSE);
		m_btnNoPic.EnableWindow(FALSE);

		break;
	default:
		break;
	}
	m_lbStatus.Invalidate();
}

VOID CTestChanelPage::SetProgramName(const wchar_t * strName,COLORREF GRDColor,COLORREF TxtColor)
{
	m_lbPragramName.SetColor(TxtColor,RGB(bkgndR,bkgndG,bkgndB));
	m_lbPragramName.SetWindowText(strName);
	m_lbPragramName.Invalidate();
}
VOID CTestChanelPage::SetMsg(const wchar_t * strMsg,COLORREF TxtColor)
{
	m_lbInfoMsg.SetColor(TxtColor,RGB(bkgndR,bkgndG,bkgndB));
	m_lbInfoMsg.SetWindowText(strMsg);
	m_lbInfoMsg.Invalidate();
}
void CTestChanelPage::InsertRecord(CString test,CString subTest,CString IsTest)
{
	CString item;
	item.Format(_T("%d"),m_ltcTestItem.GetItemCount());
	m_ltcTestItem.InsertItem(m_ltcTestItem.GetItemCount(),item,NULL);	
	m_ltcTestItem.SetItemText(m_ltcTestItem.GetItemCount()-1,1,test);
	m_ltcTestItem.SetItemText(m_ltcTestItem.GetItemCount()-1,2,subTest);
	if (!IsTest.CompareNoCase(_T("yes")))
	{
		m_ltcTestItem.SetCheck(m_ltcTestItem.GetItemCount()-1);
	}
	else
		m_ltcTestItem.SetCheck(m_ltcTestItem.GetItemCount()-1,FALSE);
}
void CTestChanelPage::UpdateRecord(int Item,CString connect)
{
	m_ltcTestItem.SetItemText(Item,3,connect);
}
void CTestChanelPage::InitRecordLog()
{
	m_ltcTestItem.DeleteAllItems();
	m_ltcTestItem.RemoveAllGroups();

}

void CTestChanelPage::UpdateTotalRecord(CString ReciveCount,CString TotalFailCount)
{
	m_lbTotalNum.SetWindowText(ReciveCount);
	m_lbTotalNum.Invalidate();
	m_lbFautyNum.SetWindowText(TotalFailCount);
	m_lbFautyNum.Invalidate();

	int failCount = _ttoi(TotalFailCount);
	int reciveCount= _ttoi(ReciveCount);
	float okNub =1-failCount/((float)reciveCount); 

	CString strOkNum;
	strOkNum.Format(_T("%0.3f%%"),okNub*100);
	m_lbOkNum.SetWindowText(strOkNum);
	m_lbOkNum.Invalidate();
}