#include "stdafx.h"
#include "MyPanel.h"
#include "TypeCent.h"
#include <string>
#include "PanelManager.h"
#include "../Inc/ConfigurationManager.h"
#include "TLog.h"
#include "..\slacmvsn\WarningDlg.h"
#include "..\slacmvsn\MainFrm.h"
#include "..\SLACMVSN\DlgShowData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
using namespace std;
using namespace Halcon;
/////////////////////////////////////////////////////////////////////////////
// CMTIPanel

#pragma warning(disable:4244)
#pragma warning(disable:4996)

extern MvsConfigurationManager  gConfigManager;

void MyHalconExceptionHandler(const Halcon::HException& except)
{
	throw except;
}

CMyPanel::CMyPanel(CPanelManager* pPanelManager)
	:m_shHour(0), 
	m_shMinute(0),
	m_shSecond(0),
	m_bClearCounter(TRUE),
	m_pPanelManager(pPanelManager)
{	
	m_iWidth = 1250;
	m_iHeight = 185;
	m_DisplayWinID_Halcon = 0;
	m_isExit = false;
	m_bReflash = false;
	m_font.CreateFont(
		16,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,	                // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("Arial"));	
	m_pGraphObject = nullptr;

#ifdef SHEET_INSPECTION
	m_vResultData     = std::vector<unsigned char>(DEFAULT_SIZE, 0);
	m_vErrorRgnInfo   = std::vector<ERROR_RGN_INFO>(DEFAULT_ERROR_RGN_COUNTER,ERROR_RGN_INFO());
	m_bGenImgOk       = false;
	m_bReadErrorRgnOk = false;
	m_hTriggerEvent   = CreateEvent(NULL, TRUE, FALSE, _T("Trigger"));
	m_hMutex          = CreateMutex(NULL, FALSE, _T("PanelGenImgOkFlagMutex"));
#endif

	m_iGport = -1; //Green Port
	m_iRport = -1 ; //Red Light 
}

CMyPanel::~CMyPanel()
{
	if (m_pGraphObject!=NULL)
	{
		m_pGraphObject->DestroyWindow();
		delete m_pGraphObject;
	}
	m_db->Close();
	delete m_db;
}

BEGIN_MESSAGE_MAP(CMyPanel, CButton)
	ON_WM_TIMER()
END_MESSAGE_MAP()

void CMyPanel::InitButtons(CHANNEL_SETTING& panelSetting)
{
	CString tmp;
#ifdef _ENGLISH
	tmp = _T("Run");
#else
	tmp = _T("运行");
#endif
	m_butRun.Create(tmp,WS_CHILD|WS_VISIBLE,CRect(m_iWidth*0.10+5,15,m_iWidth*0.15,m_iHeight*0.34+5),this,NULL);
	m_butRun.SetFont(&m_font);
	m_butRun.SetPanelID(panelSetting);
	m_butRun.SetButtonType(BT_RUN);

#ifdef _ENGLISH
	tmp = _T("Pause");
#else
	tmp = _T("暂停");
#endif
	m_butPause.Create(tmp,WS_CHILD|WS_VISIBLE,CRect(m_iWidth*0.10+5,m_iHeight*0.34+10,m_iWidth*0.15,m_iHeight*0.66),this,NULL);
	m_butPause.SetFont(&m_font);
	m_butPause.SetPanelID(panelSetting);
	m_butPause.SetButtonType(BT_PAUSE);




	m_programNamePanel.Create(_T("PROGRAM:"),WS_CHILD|WS_VISIBLE,CRect(10,m_iHeight*0.7+2,m_iWidth*0.1,m_iHeight*0.82), this);
	wstring name(_T(""));
	name += panelSetting.szProgramName;
	SetProgramNamePanel(name.c_str(),RGB(0,0,0),RGB(200,220,250));

	m_statePromptPanel.Create(_T("等侍"),WS_CHILD|WS_VISIBLE|SS_NOTIFY,CRect(10,m_iHeight*0.82+2,m_iWidth*0.1,m_iHeight*0.95), this);
	SetStatePromptPanel(name.c_str(),RGB(0,0,0),RGB(200,220,250));

#ifdef _ENGLISH
	tmp = _T("Channel");
#else
	tmp = _T("通道");
#endif
 	m_butStation.Create(tmp,WS_CHILD|WS_VISIBLE,CRect(m_iWidth*0.79,15,m_iWidth*0.84,m_iHeight*0.34+5),this,NULL);
	m_butStation.SetFont(&m_font);
	m_butStation.SetPanelID(panelSetting);
	m_butStation.SetButtonType(BT_ENTER);

#ifdef _ENGLISH
	tmp = _T("Alarm");
#else
	tmp = _T("警告");
#endif
 	m_butAlarm.Create(tmp,WS_CHILD|WS_VISIBLE,CRect(m_iWidth*0.79,m_iHeight*0.34+10,m_iWidth*0.84,m_iHeight*0.66),this,NULL);
 	m_butAlarm.SetFont(&m_font);
 	m_butAlarm.SetPanelID(panelSetting);
 	m_butAlarm.SetButtonType(BT_ALARM);


#ifdef _ENGLISH
	tmp = _T("Query");
#else
	tmp = _T("查询");
#endif
	m_butQuery.Create(tmp,WS_CHILD|WS_VISIBLE,CRect(m_iWidth*0.79,m_iHeight*0.66+5,m_iWidth*0.84,m_iHeight*0.98-5),this,NULL);
	m_butQuery.SetFont(&m_font);
	m_butQuery.SetPanelID(panelSetting);
	m_butQuery.SetButtonType(BT_QUERY);

#ifdef _ENGLISH
	tmp = _T("Recount");
#else
	tmp = _T("清零");
#endif
	m_butRecount.Create(tmp,WS_CHILD|WS_VISIBLE,CRect(m_iWidth*0.10+5,m_iHeight*0.66+5,m_iWidth*0.15,m_iHeight*0.98-5),this,NULL);
	m_butRecount.SetFont(&m_font);
	m_butRecount.SetPanelID(panelSetting);
	m_butRecount.SetButtonType(BT_RECOUNT);



	m_butStation.SetPanelPoint(this);
	m_butPause.SetPanelPoint(this);
	m_butRun.SetPanelPoint(this);
	m_butAlarm.SetPanelPoint(this);
	m_butQuery.SetPanelPoint(this);
	m_butRecount.SetPanelPoint(this);

	m_butStation.SetPanelType(PT_NORMAL);
	m_butPause.SetPanelType(PT_NORMAL);
	m_butRun.SetPanelType(PT_NORMAL);
	m_butAlarm.SetPanelType(PT_NORMAL);
	m_butQuery.SetPanelType(PT_NORMAL);
	m_butRecount.SetPanelType(PT_NORMAL);
}
	
int CMyPanel::Init(CHANNEL_SETTING& panelSetting)
{
	time_t curtime = time(NULL);
	struct tm stm;
	localtime_s(&stm, &curtime);
	memset(m_cStartTime, 0, TIME_LEN);	
	strftime(m_cStartTime, TIME_LEN,"%Y-%m-%d %H:%M:%S", &stm);

	RECT rect;
	rect.left = 5+(1-1)*(5 + m_iWidth);
	rect.top = 5+(panelSetting.m_channelIndex)*(5 + m_iHeight);
	rect.right = rect.left + m_iWidth;
	rect.bottom = rect.top + m_iHeight;

	CWnd* pMainView  = ((CMainFrame*)AfxGetMainWnd())->SOverViewWnd;
	dwProcessId = panelSetting.m_pi.dwProcessId;
	//将逻辑坐标转换为物理坐标
	CClientDC   dc(pMainView);   
	dc.LPtoDP(&rect);    

	CString strPanel;
	strPanel.Format(_T("%s"),panelSetting.szStationID.c_str());
	Create(strPanel,WS_CHILD|WS_VISIBLE|BS_GROUPBOX,rect,pMainView,331);
	SetOwner(pMainView);
	SetFont(&m_font);
	
	m_sStateIndicator.Create(_T(""), WS_CHILD|WS_VISIBLE,CRect(10,15,128,128), this);
	m_sStateIndicator.SetColor(RGB(10,10,115),RGB(200,220,250));
	m_sStateIndicator.Invalidate();
	m_sStateIndicator.SetPtr2UiDecorator(&m_ui_decorator);

	InitButtons(panelSetting);

	CRect logrect(m_iWidth*0.84+5,15,m_iWidth*0.99,m_iHeight*0.98);
	m_Static_MonitorPhoto.Create( _T("  LOG  "), WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_CLIPSIBLINGS | SS_BITMAP , logrect,this);

	wchar_t tmpBuff[128];
	::memset((void*)tmpBuff, 0x00, sizeof(wchar_t) * 128);
	swprintf_s(tmpBuff,_T("%s-%d:cmd"),_T("FTS2007MICMD"),dwProcessId);
	m_uiCmdProxy.Init(tmpBuff);

	::memset((void*)tmpBuff, 0x00, sizeof(wchar_t) * 128);
	swprintf_s(tmpBuff,_T("%s-%d:img"),_T("FTS2007MICMD"),dwProcessId);
	m_channelImgProxy.Init(tmpBuff);

	::memset((void*)tmpBuff, 0x00, sizeof(wchar_t) * 128);
	swprintf_s(tmpBuff,_T("%s-%d:report"),_T("FTS2007MICMD"),dwProcessId);
	m_channelReportProxy.Init(tmpBuff);

	m_rejectSignalSentry.Init(dwProcessId);

#ifdef SHEET_INSPECTION
	::memset((void*)tmpBuff, 0x00, sizeof(wchar_t) * 128);
	swprintf_s(tmpBuff, _T("ChannelInspectionResult#%d"), dwProcessId);
	m_resultDataBuff.Init(tmpBuff);

	::memset((void*)tmpBuff, 0x00, sizeof(wchar_t) * 128);
	swprintf_s(tmpBuff, _T("ChannelErrorRgnInfo#%d"), dwProcessId);
	m_errorRgnInfoBuff.Init(tmpBuff);

	::memset((void*)tmpBuff, 0x00, sizeof(wchar_t) * 128);
	swprintf_s(tmpBuff, _T("UploadImageCommand#%d"), dwProcessId);
	m_uiPullImgCmdBuff.Init(tmpBuff);

	::memset((void*)tmpBuff, 0x00, sizeof(wchar_t) * 128);
	swprintf_s(tmpBuff, _T("ChannelSendImgFlagBuff#%d"), dwProcessId);
	m_channelSentImagFlagBuff.Init(tmpBuff);
#endif

	try
	{
		Hobject  initIimage;
		unsigned char  image[ZOOM_IMAGE_W*ZOOM_IMAGE_H];

		for (int r=0; r<ZOOM_IMAGE_H; r++)
			for (int c=0; c<ZOOM_IMAGE_W; c++)
				image[r*ZOOM_IMAGE_W+c] = c % 255;

		gen_image1(&initIimage,"byte",ZOOM_IMAGE_W,ZOOM_IMAGE_H,(long)image);
		set_check("~father");
		open_window(0,0,logrect.Width(),logrect.Height(),(Hlong)m_Static_MonitorPhoto.m_hWnd,"visible","",&m_DisplayWinID_Halcon);	
		set_check("father");
		set_draw(m_DisplayWinID_Halcon,"margin"); //margin or fill
		disp_obj(initIimage, m_DisplayWinID_Halcon);
		set_line_width(m_DisplayWinID_Halcon,HTuple(1));
	}
	catch (HException &except) 
	{
		string msg;
		msg = except.line;
		msg+=except.message;
		AfxMessageBox(s2ws(msg).c_str());
	}
	//create test time counter control
	GetClientRect(&rect);
	rect.bottom = rect.top + 15;
	rect.left = rect.right-65;
	rect.right -= 10;
	m_ctlCounter.Create(_T("00:00:00"), WS_CHILD|WS_VISIBLE|DT_CENTER, rect, this);
	m_ctlCounter.SetFont(&m_font);

	m_butStation.EnableWindow(TRUE);
	m_butPause.EnableWindow(TRUE);
	m_butRun.EnableWindow(TRUE);
	m_butAlarm.EnableWindow(FALSE);

	m_pGraphObject = new CGraphObject();
	m_pGraphObject->Create( NULL, NULL, NULL, CRect(m_iWidth*0.156,10,m_iWidth*0.786,m_iHeight*0.98), this, 555555, NULL );
	// Create graph and set graph parameters
	m_pGraphObject->CreateGraph( GT_2DLINE );
	m_pGraphObject->SetGraphBackgroundColor( RGB(220,220,220) );
	CString title;
	title = _T(" ");
	m_pGraphObject->SetGraphTitle(title);
	m_pGraphObject->SetGraphTitleColor(RGB(255,0,0));

	m_pGraphObject->SetGraphSubtitle( _T(" " ));
	m_pGraphObject->SetGraphLegendBackgroundColor( RGB(220,220,220) );
	m_pGraphObject->SetGraphTitleShadow( FALSE );
	m_pGraphObject->SetGraphSubtitleShadow( FALSE );
	// Add graph segments
	m_pGraphObject->Add2DLineGraphSegment( _T("1" ));
	m_pGraphObject->Add2DLineGraphSegment( _T("2" ));
	m_pGraphObject->Add2DLineGraphSegment( _T("3" ));
	m_pGraphObject->Add2DLineGraphSegment( _T("4" ));
	m_pGraphObject->Add2DLineGraphSegment( _T("5" ));
	m_pGraphObject->Add2DLineGraphSegment( _T("6" ));
	m_pGraphObject->Add2DLineGraphSegment( _T("7" ));
	m_pGraphObject->Add2DLineGraphSegment( _T("8" ));
	m_pGraphObject->Add2DLineGraphSegment( _T("9" ));
	m_pGraphObject->Add2DLineGraphSegment( _T("10" ));
	m_pGraphObject->Add2DLineGraphSegment( _T("11" ));
	m_pGraphObject->Add2DLineGraphSegment( _T("12" ));
	m_pGraphObject->Add2DLineGraphSegment(_T( "13" ));
	m_pGraphObject->Add2DLineGraphSegment(_T( "14" ));
	m_pGraphObject->Add2DLineGraphSegment(_T( "15" ));
	m_pGraphObject->Add2DLineGraphSegment(_T( "16" ));
	m_pGraphObject->Add2DLineGraphSegment( _T("17") );
	m_pGraphObject->Add2DLineGraphSegment( _T("18 x1000") );

	// Add graph series
 	m_pGraphObject->Add2DLineGraphSeries( _T("Def %%"), RGB(151,108,80) );
	m_pGraphObject->Add2DLineGraphSeries( _T(" "), RGB(220,220,220) );
	
	// Set graph animation
	m_pGraphObject->SetGraphAnimation( FALSE, AT_LINE_DRAW_ALL );
	//Init 数据库的部分。
	m_db = new CSqliteDB<CppSQLite3Query>;

	wstring tmpTrasf = panelSetting.szProgramName;
	string programName = ws2s(tmpTrasf);
	sprintf_s(m_cDbname,"d:\\SLACTST\\%s\\%s",programName.c_str() ,CHANELDBNAME);
	
 	m_db->SetDBName(m_cDbname);
 	m_db->Connect();
#ifdef SHEET_INSPECTION
	ShowWindow(SW_HIDE);
#endif

	m_pannelSettings = panelSetting;
	return 0;
}

BOOL CMyPanel::ClickedOpenChanel(DWORD dwProcessId)
{
	wchar_t tmpBuff[128];
	this->dwProcessId = dwProcessId;

	swprintf_s(tmpBuff,_T("%s-%d:cmd"),_T("FTS2007MICMD"),dwProcessId);
	m_uiCmdProxy.Init(tmpBuff);

	swprintf_s(tmpBuff,_T("%s-%d:report"),_T("FTS2007MICMD"),dwProcessId);
	m_channelReportProxy.Init(tmpBuff);

	swprintf_s(tmpBuff,_T("%s-%d:img"),_T("FTS2007MICMD"),dwProcessId);
	m_channelImgProxy.Init(tmpBuff);

	m_rejectSignalSentry.Stop(); //Close Old transfer memory file.
	m_rejectSignalSentry.Init(dwProcessId); 

	return TRUE;
}

VOID CMyPanel::SetState(eMTI_GUI_STATE state)
{
	m_sStateIndicator.UpdateSytemStatusSymbol(state);
	switch(state) 
	{
	case MTI_GUI_IDLE:
        SetStationBtnAccessibility();
		m_butPause.EnableWindow(FALSE);
		m_butRun.EnableWindow(TRUE);
		ClearCounter();
		break;
	case MTI_GUI_RUN:
		m_butPause.EnableWindow(TRUE);
		m_butRun.EnableWindow(FALSE);
        SetStationBtnAccessibility();

		SetTimer(UM_CONTER, 1000, NULL);
		break;
	case MTI_GUI_STOP:
        SetStationBtnAccessibility();
		m_butPause.EnableWindow(FALSE);
		m_butRun.EnableWindow(FALSE);
		m_butAlarm.EnableWindow(FALSE);
		StopCounter();
		break;
	case MTI_GUI_PAUSE:
        SetStationBtnAccessibility();
		m_butPause.EnableWindow(FALSE);
		m_butRun.EnableWindow(TRUE);
		m_butAlarm.EnableWindow(FALSE);
		PauseCounter();		
		break;
	case MTI_GUI_INIT:
        SetStationBtnAccessibility();
		m_butPause.EnableWindow(FALSE);
		m_butRun.EnableWindow(TRUE);	
		break;
	
	case MTI_GUI_EXIT:
		m_butStation.EnableWindow(FALSE);
		m_butPause.EnableWindow(FALSE);
		m_butRun.EnableWindow(FALSE);
		break;
	case MTI_GUI_ALARM:
		m_butAlarm.EnableWindow(TRUE);
		break;
	default:
		m_butStation.EnableWindow(FALSE);
		m_butPause.EnableWindow(FALSE);
		m_butRun.EnableWindow(FALSE);
		break;
	}
	m_sStateIndicator.Invalidate();
}

VOID CMyPanel::SetProgramNamePanel(const wchar_t * strName,COLORREF TxtColor, COLORREF GRDColor)
{
	m_programNamePanel.SetColor(TxtColor,GRDColor);
	m_programNamePanel.SetWindowText(strName);
	m_programNamePanel.Invalidate();
}

VOID CMyPanel::SetStatePromptPanel(const wchar_t * strMsg, COLORREF TxtColor, COLORREF GRDColor)
{
	m_statePromptPanel.SetColor(TxtColor,GRDColor);
	m_statePromptPanel.SetWindowText(strMsg);
	m_statePromptPanel.Invalidate();
}

void CMyPanel::OnTimer(UINT_PTR nIDEvent)
{
	m_shSecond++;
	if (m_shSecond == 60||m_bReflash)
	{
		if (m_shSecond == 60)
		{
			m_shMinute++;
			m_shSecond = 0;
		}
		
		m_bReflash = false;
		char sqlbuf[MSG_LEN];

		int testCounts = 0;
		int failCounts = 0;
		int totalTestCount = 0;
		int totalFailCount = 0;
		
		sprintf_s(sqlbuf, "select testcounts,failcounts from  top18events order by eventid  desc   Limit 18");
		CppSQLite3Query rst = m_db->Query(sqlbuf);

		int step = 18;
		int max=0;
		while(!rst.eof())
		{
			rst.getInt64Field("testcounts");
			testCounts = rst.getInt64Field("testcounts");
			failCounts = rst.getInt64Field("failcounts");
			totalTestCount+=testCounts;
			totalFailCount+=failCounts;
			int isetv = static_cast<int>(((float)failCounts/(float)testCounts)*1000);
			if (isetv>max)
			{
				max = isetv;
			}
			if (isetv!=0)
			{
				m_pGraphObject->Set2DLineGraphValue( step, 1,isetv);
			}
			
			//m_pGraphObject->Set2DLineGraphValue( step, 2,100);
			step--;
			rst.nextRow();
		}

		if (step == 18)
		{

			step = 18;
			while(step>0)
			{
				m_pGraphObject->Set2DLineGraphValue( step, 1,0);
				step--;
			}
		}

		step = 18;
		while(step>0)
		{
			m_pGraphObject->Set2DLineGraphValue( step, 2,max+3);
			step--;
		}

		//m_pGraphObject->Set2DLineGraphValue( 1, 1,100);
		rst.finalize();
		CString title;
		#ifdef _ENGLISH
				title.Format(_T("  count:%d,  defects:%d,  defect rate:%0.3f%%"),totalTestCount,totalFailCount,((float)(totalFailCount)/(float)(totalTestCount))*100);
		#else
				title.Format(_T("  产出:%d,    不良数:%d,    不良率:%0.3f%%"),totalTestCount,totalFailCount,((float)(totalFailCount)/(float)(totalTestCount))*100);
				
		#endif
		m_pGraphObject->SetGraphTitle( title );

		m_pGraphObject->Invalidate();
	}
	if (m_shMinute == 60)
	{
		m_shMinute = 0;
		m_shHour++;
	}
	CString strCountMsg;
	strCountMsg.Format(_T("%02d:%02d:%02d"), m_shHour, m_shMinute, m_shSecond);
	m_ctlCounter.SetWindowText(strCountMsg);
	m_ctlCounter.Invalidate();
	CButton::OnTimer(nIDEvent);
}

BOOL CMyPanel::ClickedPause()
{	
	HANDLE  hProcess = OpenProcess(PROCESS_QUERY_INFORMATION , FALSE, dwProcessId);
	if(hProcess == NULL)
	{
		AfxMessageBox(_T("This Channel is Close."));
		::CloseHandle(hProcess);
		StopCounter();
		return FALSE;
	}
	::CloseHandle(hProcess);
	char cmd[2]; cmd[0] = (char)PAUSED; cmd[1] = 0;
	m_uiCmdProxy.Write(sizeof(char),cmd, 2);
	return TRUE;
}

BOOL CMyPanel::ClickedAlarm()
{
#ifdef EOE_INSPECTION
	CWarningDlg dlg;
 	if (dlg.DoModal()==IDOK)
 	{
		m_butAlarm.EnableWindow(FALSE);

		SetState(MTI_GUI_RUN);

		CPanelManager::GetPanelManager().SetPortST(m_iRport,ALL_CLEAR);
		char cmd[2]; cmd[0] = (char)DISMISS_WARNING; cmd[1]=0;
		m_uiCmdProxy.Write(sizeof(char),cmd, 2);

 	}
 	dlg.DestroyWindow();
#endif

#ifdef SHEET_INSPECTION
	CPanelManager::GetPanelManager().SetPortST(m_iRport,ALL_CLEAR);
	char cmd[2]; cmd[0] = (char)DISMISS_WARNING; cmd[1]=0;
	m_uiCmdProxy.Write(sizeof(char),cmd, 2);
#endif
	return TRUE;
}

void CMyPanel::ChangeUserGroup(eUSER_GROUP group)
{
	HANDLE  hProcess = OpenProcess(PROCESS_QUERY_INFORMATION , FALSE, dwProcessId);
	if(hProcess == NULL)
	{
		AfxMessageBox(_T("This Channel is Close."));
		::CloseHandle(hProcess);
		StopCounter();
		return ;
	}
	::CloseHandle(hProcess);
	int userCode = -1;
	if(group == OPERATOR)
		userCode = USER_OPERATOR;
	if(group == ENGINEER)
		userCode = USER_ENGINEER;
	if(group == ADMIN) 
		userCode = USER_ADMIN;
	if(group == SADMIN)
		userCode = USER_SLAC_ADMIN;

	char cmd[2]; cmd[0] = (char)userCode; cmd[1] = 0;
	m_uiCmdProxy.Write(sizeof(char),cmd, 2);
}

BOOL CMyPanel::ClickedRun()
{
	HANDLE  hProcess = OpenProcess(PROCESS_QUERY_INFORMATION , FALSE, dwProcessId);
	if(hProcess == NULL)
	{
		AfxMessageBox(_T("This Channel is Close."));
		::CloseHandle(hProcess);
		StopCounter();
		return FALSE;
	}

	::CloseHandle(hProcess);
	char cmd[2]; cmd[0] = (char)RUNNING; cmd[1] = 0;
	m_uiCmdProxy.Write(sizeof(char),cmd, 2);
	return TRUE;
}

BOOL CMyPanel::ClickedRecount()
{
 	if(m_db != nullptr)
 	{
		char sqlbuf[MSG_LEN];
		sprintf_s(sqlbuf, "update testrecords set totalcounts=%d,failcounts=%d where recordid=1",0,0);

 		CppSQLite3Query rst = m_db->Query(sqlbuf);	
 		rst.finalize();

		sprintf_s(sqlbuf, "delete from top18events;");
		m_db->Excute(sqlbuf);
		sprintf_s(sqlbuf, "vacuum;");
		m_db->Excute(sqlbuf);
		m_bReflash = true; //reflush main UI log
 	}

	

	return TRUE;
}
BOOL CMyPanel::ClickedQuery()
{
 	CDlgShowHistoryData dlg;
 	dlg.SetDbName(m_cDbname,256);
 	dlg.InitConnect();
 	dlg.DoModal();

	return TRUE;
}


void CMyPanel::SetStationBtnAccessibility()
{
	//if (CMI_ControlCenter::GetInstance().GetIsFullScreen())
	//	m_butStation.EnableWindow(FALSE);
	//else
	//	m_butStation.EnableWindow(TRUE);
}

void CMyPanel::ProcessChannelStatusReport(char* pReportBuff)
{
	if(pReportBuff == nullptr)
		return;
	string report(pReportBuff);
	size_t sz = report.size();

	if(strlen(pReportBuff) < 3)
		return;

	std::wstring msg;
	int OK = 1;
	if(pReportBuff[0] == (char)IDLE)
	{
#ifdef _ENGLISH
		msg = _T("Ready");
#else
		msg = _T("准备就绪");
#endif
		SetStatePromptPanel(msg.c_str(),RGB(0,0,0),RGB(200,220,250));
		SetState(MTI_GUI_IDLE);
		CPanelManager::GetPanelManager().SetPortST(pReportBuff[2]-1, ALL_CLEAR);
	}
	else if (pReportBuff[0] == (char)RUNNING)
	{
#ifdef _ENGLISH
		msg = _T("Testing...");
#else
		msg = _T("检测运行中");
#endif
		SetStatePromptPanel(msg.c_str(),RGB(0,0,0),RGB(200,220,250));
		SetState(MTI_GUI_RUN);
		m_iGport = pReportBuff[2] - 1; //Green Port
		CPanelManager::GetPanelManager().SetPortST(m_iGport, OK);

		m_iRport = pReportBuff[1] - 1 ; //Red Light 
		CPanelManager::GetPanelManager().SetPortST(m_iRport,ALL_CLEAR);
	}
	else if(pReportBuff[0] == (char)PAUSED)
	{
#ifdef _ENGLISH
		msg = _T("Paused");
#else
		msg = _T("暂停");
#endif
		SetState(MTI_GUI_PAUSE);
		SetStatePromptPanel(msg.c_str(),RGB(0,0,0),RGB(200,220,250));
		CPanelManager::GetPanelManager().SetPortST(pReportBuff[2] - 1, ALL_CLEAR);
	}
	else if(pReportBuff[0] == (char)STOPPED)
	{
#ifdef _ENGLISH
		msg = _T("Stopped");
#else
		msg = _T("停止");
#endif
		SetStatePromptPanel(msg.c_str() ,RGB(0,0,0),RGB(200,220,250));
		SetState(MTI_GUI_STOP);
		CPanelManager::GetPanelManager().SetPortST(pReportBuff[2] - 1, ALL_CLEAR);
	}
	else if (pReportBuff[0] == (char)INIT)
	{
#ifdef _ENGLISH
		msg = _T("Initializing...");
#else
		msg = _T("程式初始化中");
#endif
		SetState(MTI_GUI_INIT);
		SetStatePromptPanel(msg.c_str(),RGB(0,0,0),RGB(200,220,250));
	}
	else if (pReportBuff[0] == (char)UPDATE_SETTINGS)
	{
		string programName(pReportBuff + 1, pReportBuff + 32);
		wstring wName = s2ws(programName);
		SetProgramNamePanel(wName.c_str(),RGB(0,0,0),RGB(200,220,250));

		SetStatePromptPanel(_T("Change Program Name"),RGB(0,0,0),RGB(200,220,250));
		gConfigManager.SetProgram(m_pannelSettings.szStationID, wName);
	}
	else if (pReportBuff[0] == (char)TURN_ON_RED_LIGHT)
	{
		//TLOG_WARNING(_T("Channel #%s receives a warning -- port:%d"),m_pannelSettings.szStationID.c_str(), (int)pReportBuff[1]-1);
		CPanelManager::GetPanelManager().SetPortST((int)pReportBuff[1] - 1,ALARM_SIGNAL);
#ifdef SHEET_INSPECTION
		CPanelManager::GetPanelManager().HandAlarm((int)pReportBuff[1] - 1);
#endif
		SetState(MTI_GUI_ALARM);
	}
}

UINT CMyPanel::Main(/* LPVOID lpParam */)
{
	char reportBuff[32];
	Hobject  retImage;
	m_isExit = false;
	size_t buffSize = sizeof(char) * 32;

#ifdef SHEET_INSPECTION
	::WaitForSingleObject(m_hTriggerEvent, INFINITE);
	ClickedRun();
#endif

	while(!m_isExit)
	{	
#ifdef EOE_INSPECTION
		bool bReadFlag = m_channelImgProxy.Read(&retImage);
		if(bReadFlag)
		{
			disp_obj(retImage, m_DisplayWinID_Halcon);
		}
#endif
#ifdef SHEET_INSPECTION
		char buff[2]; buff[0] = 0; buff[1] = 0;
		if(m_channelSentImagFlagBuff.Read(sizeof(char),buff,2) && (buff[0] == (char)1))
		{
			Sleep(20); // During this period, the channel is uploading image
			ResetGenImageOkFlag();
			ClearInspectionResultContainer();

			if(m_resultDataBuff.Read(sizeof(char),(unsigned char*)&m_vResultData[0], DEFAULT_SIZE))
			{
				if(GenerateImageFromStringStream())
				{
					SetGenImageOkFlag(true);
				}
				char cmd[2]; cmd[0] = 0; cmd[1] = 0;
				m_channelSentImagFlagBuff.Write(sizeof(char),cmd, 2);
			}

			if(m_errorRgnInfoBuff.Read(sizeof(ERROR_RGN_INFO),&m_vErrorRgnInfo[0], DEFAULT_ERROR_RGN_COUNTER))
			{
				RemoveDummyErrorRegion();
				SetReadErrorRgnOkFlag(true);
			}
		}
		Sleep(5);
#endif
	    ::memset((void*)reportBuff, 0x00, buffSize);
		if(m_channelReportProxy.Read(sizeof(char),reportBuff, buffSize))
		{
			ProcessChannelStatusReport(reportBuff);
		}
	}
	return 0;
}

 void CMyPanel::Stop()
 {

	 CPanelManager::GetPanelManager().SetPortST(m_iGport, ALL_CLEAR);
	 CPanelManager::GetPanelManager().SetPortST(m_iRport,ALL_CLEAR);

	 m_rejectSignalSentry.Stop();
	 Sleep(100);
	 m_isExit = true;
}
 //////////////////
 CRejectSignalSentry::CRejectSignalSentry()
 {
 }

 CRejectSignalSentry::~CRejectSignalSentry()
 {	
	 m_isExit = true;	
 }

 void CRejectSignalSentry::Stop()
 {
	 m_isExit = true;
	 m_portNumBuffer.ResetShareMemory();
 }

 void CRejectSignalSentry::Init(DWORD dwProcessID)
 {
	 wchar_t tmpBuff[128];
	 ::memset((void*)tmpBuff, 0x00, sizeof(wchar_t) * 128);
	 swprintf_s(tmpBuff,_T("%s-%d:reject"),_T("FTS2007MICMD"),dwProcessID);
	 m_portNumBuffer.Init(tmpBuff);
	 m_isExit = false;
	
	 Run();
 }

 UINT CRejectSignalSentry::Main()
 {
	 m_isExit = false;
	 char *strend;
	 char buff[6]; buff[0] = -1; buff[1] = 0;buff[2] = 0;buff[3] = 0;buff[4] = 0;buff[5]=0;
	 while(!m_isExit)
	 {	
		 
		 if (m_portNumBuffer.Read(sizeof(char),buff,6))
		 {
			 int port=strtol(&buff[0],&strend,16);
			 int delaycount = strtol(&buff[2],&strend,16);
			 ProcessChannelRejectReport(port,delaycount);
		 }
	 }
	return 0;
 }

 void CRejectSignalSentry::ProcessChannelRejectReport(int nPortNum,int encoderDelayCount)
 {
	 CPanelManager::GetPanelManager().DoReject(nPortNum,encoderDelayCount);
	
 }