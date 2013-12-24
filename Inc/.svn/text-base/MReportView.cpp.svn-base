#pragma once
#include "stdafx.h"
#include "MData.h"
#include "MReportView.h"
#include "MReportCenter.h"
#include "MainFrm.h"
#include "TLog.h"
#include "Tools.h"
#include "TypeCent.h"
#include "MCtrlCenter.h"

#include <algorithm>
using namespace std;

#pragma warning(disable:4244)

#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG

CMReportView::CMReportView()
	:m_isExit(false),
	m_hDispWnd(0),
	m_LogDisplayWinID_Halcon(0),
	m_cClock(0),
	m_UnitCount(0),
	m_UnitFailCount(0),
	m_secondCount(0),
	m_FailCount(0),
	m_totalCount(0),
	m_totalFailCount(0),
	m_db(nullptr),
	m_dataToBeReported(MAX_DATA_REPOSITORY_SIZE)
{
}

CMReportView::~CMReportView()
{
	m_vItem.clear();
	if(m_db != nullptr)
	{
		m_db->Close();
		delete m_db;
		m_db = nullptr;
	}
}

void CMReportView::InitSQLiteDB()
{
    m_db = new CSqliteDB<CppSQLite3Query>;
	char dbname[256];

	m_baseInfo.tlsname =  CMConfigCenter::GetSingletonConfigCenter()->GetTLSFileName();
	m_baseInfo.programname = CMConfigCenter::GetSingletonConfigCenter()->GetProgramName();
	m_baseInfo.line = "testline";
	m_baseInfo.programPath = ws2s(CMConfigCenter::GetSingletonConfigCenter()->GetTestProgramPath());
	m_baseInfo.fixid = "test";

	const char* cchProgName = m_baseInfo.programname.c_str();
	const char* cchTlsName =  m_baseInfo.tlsname.c_str();
	const char* cchLine = m_baseInfo.line.c_str();

	sprintf_s(dbname,"%s%s\\%s",m_baseInfo.programPath.c_str(),cchProgName,CHANELDBNAME);

	m_db->SetDBName(dbname);
	m_db->Connect();

	char sqlbuf[MSG_LEN];
	sprintf_s(sqlbuf, "SELECT commonid FROM COMMON where programname='%s' and tlsname='%s' and line='%s'", cchProgName,cchTlsName, cchLine);
	CppSQLite3Query rst = m_db->Query(sqlbuf);
	if (rst.eof())
	{	
		sprintf_s(sqlbuf, "INSERT INTO COMMON  ('programname','tlsname','line','fixid') values('%s','%s','%s','%s')",cchProgName,cchTlsName,cchLine,m_baseInfo.fixid.c_str());
		CppSQLite3Query rst = m_db->Query(sqlbuf);
		
		char sqlbuf[MSG_LEN];
		sprintf_s(sqlbuf, "SELECT commonid FROM COMMON where programname='%s' and tlsname='%s' and line='%s'",cchProgName,cchTlsName,cchLine);
		rst = m_db->Query(sqlbuf);
		m_baseInfo.commonid = rst.getStringField("commonid");
	}
	else
	{
		m_baseInfo.commonid = rst.getStringField("commonid");
	}
	rst = m_db->Query("SELECT max(eventid) as maxeventid FROM events");	
	m_strEventId = rst.getStringField("maxeventid");
	rst.finalize();

	sprintf_s(sqlbuf, "delete from testevents where eventid<(select eventid from events where event_start_time<date('now','-15 day') order by eventid desc limit 0,1);");
	m_db->Excute(sqlbuf);

	sprintf_s(sqlbuf, "delete from events where event_start_time<date('now','-30 day');");
	m_db->Excute(sqlbuf);

	sprintf_s(sqlbuf, "delete from top18events where event_start_time<date('now','-1 day');");
	m_db->Excute(sqlbuf);

	sprintf_s(sqlbuf, "vacuum;");
	m_db->Excute(sqlbuf);
}

BOOL CMReportView::Init(CMReportCenter * pReportCent)
{
	m_pReportCenter = pReportCent;
	InitSQLiteDB();
	InitWindow();
	SetUIWindow();
	return TRUE;
}

void CMReportView::SetTestRecordDef()
{
	char sqlbuf[MSG_LEN];
	sprintf_s(sqlbuf, "update testrecords set totalcounts=%d,failcounts=%d where recordid=1",0,0);
	if(m_db != nullptr)
	{
		CppSQLite3Query rst = m_db->Query(sqlbuf);	
		rst.finalize();
	}
	m_totalCount = 0;
	m_totalFailCount = 0;
}

UINT CMReportView::Main()
{
	//InitSQLiteDB();
	SelectCheckedTestItem();
	m_FailCount = 0;
	m_connectNGCount = 0;
	m_UnitCount=0;
	m_Top18UnitCount=0;
	m_Top18UnitFailCount = 0;
	char sqlbuf[MSG_LEN];
	sprintf_s(sqlbuf, "update testrecords set totalcounts=%d,failcounts=%d where recordid=1",m_totalCount,m_totalFailCount);
	CppSQLite3Query rst = m_db->Query("SELECT totalcounts,failcounts FROM testrecords where recordid=1");	
	m_totalCount       = rst.getInt64Field("totalcounts");
	m_totalFailCount   = rst.getInt64Field("failcounts");
	rst.finalize();

	set_system("flush_graphic",HTuple("true"));	
	m_isExit = false;
	clock_t cClock;
	cClock = clock();
	while(!m_isExit)
	{
		if(!m_dataToBeReported.is_not_empty())
		{
			if (m_isExit)
			{
				break;
			}
			Sleep(5);
			continue;
		}
		Sleep(3);
		DoReport();
		if ((clock() - cClock) >= 1000)
		{
			m_secondCount++;
			cClock = clock();	
			//m_sConect.Format(_T("%d"),m_reciveCount);
			//m_pListWind->SetTestListCtrlConect(0,COUNTCOLUMN,m_sConect);

			int i=0;
			for (auto it_Item = m_vItem.begin();it_Item!=m_vItem.end();it_Item++)
			{
				m_sConect.Format(_T("%d"),(*it_Item).totalFailCount);
				m_pListWind->SetTestListCtrlConect((*it_Item).order,FAILCOLUMN,m_sConect);
				
				if (i++==0)
				{
					continue;
				}
				
				if (m_FailCount>0)
				{
					m_sConect.Format(_T("%0.3f%%"),(float)(*it_Item).totalFailCount/(float)m_reciveCount*100);
					m_pListWind->SetTestListCtrlConect((*it_Item).order,FAILRATECOLUMN,m_sConect);
				}
				else
				{				
					m_pListWind->SetTestListCtrlConect((*it_Item).order,FAILRATECOLUMN,_T("0"));
				}	
			}
			m_sConect.Format(_T("(%d) %d (%0.3f%%)"),m_reciveCount,m_FailCount,((float)m_FailCount/(float)m_reciveCount)*100);
			m_pListWind->SetTestListCtrlConect(0,FAILRATECOLUMN,m_sConect);
		}
	}
	return 0;
}

void CMReportView::Stop()
{
	m_isExit = true;
	m_vItem.clear();
	if(m_db != nullptr)
	{
		m_db->Close();
		delete m_db;
		m_db = nullptr;
	}
	CloseHandle(m_hThread);
	m_hThread = nullptr;
}

void CMReportView::OnClickWarning()
{
	m_connectNGCount=0;
}

void CMReportView::DoReport()
{
	set_color(m_hDispWnd,"red");
	HTuple ReciveNeedTime,ProcessNeedTime,DisplayNeedTime,TotalNeedTime,Recive2ProcessNeedTime,Process2DisplayNeedTime;
	m_currentData.ResetFailFlag();
	m_dataToBeReported.pop_back(&m_currentData);
	
	if (!m_currentData.m_isDebug)
		m_reciveCount = m_currentData.m_reciveCount;

	m_UnitCount++;
	m_totalCount++;
	m_Top18UnitCount++;
	m_counter++;
	if (m_currentData.m_isFail)
	{
		if (!m_currentData.m_isDebug)
		{
			m_UnitFailCount++;
			m_FailCount++;
			m_totalFailCount++;
			m_Top18UnitFailCount++;
			set_color(m_currentData.m_ShowHWindow,"red");
			dilation_circle(m_currentData.m_ErrorRegist,&m_currentData.m_ErrorRegist,2.5);
			disp_obj(m_currentData.m_ErrorRegist,m_currentData.m_ShowHWindow);
			
			std::for_each(m_currentData.m_vSubTestResult.begin(), m_currentData.m_vSubTestResult.end(), [&](SubTestResult& result)
			{
				if(result.m_bFailSubTest)
				{
					set_color(m_currentData.m_ShowHWindow,"red");
					disp_circle(m_currentData.m_ShowHWindow, result.m_ErrorY, result.m_ErrorX, result.m_ErrorR);
				}
			});
		
			size_t index = 0;
			for(auto it = m_currentData.m_vSubTestResult.begin(); it != m_currentData.m_vSubTestResult.end(); ++it)
			{
				if ((*it).m_bFailSubTest)
				{
					if(index < m_vItem.size())
					{
						m_vItem[index].failcount++;
						m_vItem[index].totalFailCount++;
					}
				}
				index++;
			}

#ifdef EOE_INSPECTION
		m_connectNGCount++;
#endif

#ifdef SHEET_INSPECTION
		m_bAllPassed=false;
#endif
		}
	}

#ifdef EOE_INSPECTION
	else
	{
		m_connectNGCount=0;
	}
#endif

#ifdef EOE_INSPECTION
	if (m_connectNGCount > CMConfigCenter::GetSingletonConfigCenter()->GetAlarmThreshold())
	{
		CMCtrlCenter::GetSingletonCtrlCenter()->TriggerAlarm();
	}
#endif

#ifdef SHEET_INSPECTION
	if(m_counter % 7 == 0)
	{
		if(!m_bAllPassed)
		{
			m_connectNGCount++;
			m_bAllPassed=true;
		}
		else
			m_connectNGCount=0;

		if (m_connectNGCount > CMConfigCenter::GetSingletonConfigCenter()->GetAlarmThreshold())
		{
			CMCtrlCenter::GetSingletonCtrlCenter()->TriggerAlarm();
		}
	}
	
#endif

#ifdef EOE_INSPECTION
	if (m_connectNGCount > CMConfigCenter::GetSingletonConfigCenter()->GetAlarmThreshold())
	{
		CMCtrlCenter::GetSingletonCtrlCenter()->TriggerAlarm();
	}
#endif

	if (m_Top18UnitCount >= 1000) //write test evetns log to top18events table for main UI display.
	{
		char sqlbuf[MAX_PATH];
		memset((void*)sqlbuf, 0x00, sizeof(char)*MAX_PATH);
		sprintf_s(sqlbuf, "insert into TOP18EVENTS ('commonid','testcounts','failcounts') values(%s,%d,%d)",m_baseInfo.commonid.c_str(),m_Top18UnitCount,m_Top18UnitFailCount);
		m_Top18UnitCount = 0;
		m_Top18UnitFailCount = 0;		
		CppSQLite3Query rst = m_db->Query(sqlbuf);
		rst.finalize();
		
	}

	if ((clock() - m_cClock) >= 1000)
	{
		m_secondCount++;
		m_cClock=clock();	
	}


	if (m_secondCount>= 60)
	{
		m_secondCount=0;
		char sqlbuf[MAX_PATH];
		memset((void*)sqlbuf, 0x00, sizeof(char)*MAX_PATH);
		sprintf_s(sqlbuf, "insert into events ('commonid','testcounts','failcounts') values(%s,%d,%d)",m_baseInfo.commonid.c_str(),m_UnitCount,m_UnitFailCount);
		m_UnitCount = 0;
		m_UnitFailCount = 0;		
		CppSQLite3Query rst = m_db->Query(sqlbuf);
		
		memset((void*)sqlbuf, 0x00, sizeof(char)*MAX_PATH);
		sprintf_s(sqlbuf, "update testrecords set totalcounts=%d,failcounts=%d where recordid=1",m_totalCount,m_totalFailCount);
		rst = m_db->Query(sqlbuf);

		rst = m_db->Query("SELECT max(eventid) as maxeventid FROM events");	
		string eventid = rst.getStringField("maxeventid");

		std::for_each(m_vItem.begin(), m_vItem.end(), [&](STITEM& item)
		{
			memset((void*)sqlbuf, 0x00, sizeof(char)*MAX_PATH);
			sprintf_s(sqlbuf, "insert into testevents ('eventid','testid','failcounts') values(%s,%s,%d)",eventid.c_str(), item.testid.c_str(), item.failcount);
			CppSQLite3Query rst = m_db->Query(sqlbuf);
			item.failcount=0;
		});
		rst.finalize();
	}

	set_color(m_hDispWnd,"red");
	count_seconds(&m_currentData.m_displayEndTime);
	//ReciveNeedTime  = HTuple("  RT:") + HTuple(1000*(m_currentData.m_reciveEndTime  - m_currentData.m_reciveStartTime)) + HTuple("ms");
	ProcessNeedTime = HTuple("  PT:") + HTuple(1000*(m_currentData.m_processEndTime - m_currentData.m_processStartTime)) + HTuple("ms");
	DisplayNeedTime = HTuple("  DT:") + HTuple(1000*(m_currentData.m_displayEndTime - m_currentData.m_displayStartTime))  + HTuple("ms");
	TotalNeedTime   = HTuple("  TT:") + HTuple(1000*(m_currentData.m_displayEndTime - m_currentData.m_reciveStartTime))  + HTuple("ms");

	//Recive2ProcessNeedTime  =  HTuple("R2PT:") + HTuple(1000*(m_currentData.m_processStartTime-m_currentData.m_reciveEndTime)) + HTuple("ms");
	//Process2DisplayNeedTime =  HTuple("P2DT: ") + HTuple(1000*(m_currentData.m_displayStartTime-m_currentData.m_processEndTime)) + HTuple("ms");

	int lineWidth = 25 ; //Display time message on window lineWidth

#ifdef SHEET_INSPECTION
	lineWidth= 40 ;
#endif
 	int CurrentSite=10;
//   	set_tposition( m_hDispWnd, CurrentSite, 1);				
//   	write_string(m_hDispWnd,ReciveNeedTime);
// 	 CurrentSite += lineWidth;
  	set_tposition( m_hDispWnd,CurrentSite, 1);
  	write_string(m_hDispWnd,ProcessNeedTime);
 		 CurrentSite += lineWidth;
 	set_tposition( m_hDispWnd,CurrentSite, 1);
 	write_string(m_hDispWnd,DisplayNeedTime);
 		 CurrentSite += lineWidth;
 	set_tposition( m_hDispWnd,CurrentSite, 1);
 	write_string(m_hDispWnd,TotalNeedTime);
//  		 CurrentSite += lineWidth;
//   	set_tposition( m_hDispWnd,CurrentSite, 1);
//   	write_string(m_hDispWnd,Recive2ProcessNeedTime);
//  	 	 CurrentSite += lineWidth;
//   	set_tposition( m_hDispWnd,CurrentSite, 1);
//   	write_string(m_hDispWnd,Process2DisplayNeedTime);
}

void CMReportView::ReceiveData(CMData& data)
{
	if(m_dataToBeReported.is_not_full())
	{
		m_dataToBeReported.push_front(data);
	}
}

void CMReportView::InitWindow()
{
	if (0 != m_hDispWnd)
	{
		close_window(m_hDispWnd);
		m_hDispWnd = 0;
	} 
	auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();
	m_pWSourceWindowID = pConfigCenter->GetUIWindowID();

	auto imageSize = pConfigCenter->GetDemoImgSize();
	Hlong height = imageSize.m_ImageHeight;
	Hlong width = imageSize.m_ImageWidth;

// 	CRect clientRect;
// 	::GetClientRect((HWND)m_pWSourceWindowID, &clientRect);
// 	int crWidth = clientRect.Width();
// 	int crHeight = clientRect.Height();
// 	if(crWidth < width || crHeight < height)
// 	{
// 		double r = max(1.0 * width / crWidth, 1.0 * height / crHeight);
// 		height /= r;
// 		width /= r;
// 	}

	std::vector<unsigned char> chImage(imageSize.m_ImageHeight * imageSize.m_ImageWidth, 0);

	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width; c++)
			chImage[r * width + c] = c % 255;
	}

	Hobject initImage;
	gen_image1(&initImage,"byte",width,height,(long)&chImage[0]);

	if (0 == m_hDispWnd)
	{
		set_check("~father");	
		open_window(5, 5, width, height,m_pWSourceWindowID,"visible","",&m_hDispWnd);	
		set_part(m_hDispWnd,0,0,height-1,width-1);
		set_check("father");
	}
	set_draw(m_hDispWnd,"margin"); //margin or fill
	set_color(m_hDispWnd,"red");
	disp_obj(initImage, m_hDispWnd);
	set_line_width(m_hDispWnd,HTuple(1));
	
	set_system("flush_graphic",HTuple("true"));	
	pConfigCenter->SetShowWindowHID(m_hDispWnd);

	m_pWLogWindowID = pConfigCenter->GetLogUIWindowID();

	if (0!=m_LogDisplayWinID_Halcon)
	{
		close_window(m_LogDisplayWinID_Halcon);
		m_LogDisplayWinID_Halcon = 0;
	}
	
	if (0 == m_LogDisplayWinID_Halcon)
	{
		CRect rt;
		GetWindowRect((HWND)m_pWLogWindowID,&rt);
		CRect dispRect;
		dispRect.left = (rt.Width() - width) / 2;
		dispRect.top  = 0;
		set_check("~father");
		open_window(dispRect.top, dispRect.left, width, height,m_pWLogWindowID,"visible","",&m_LogDisplayWinID_Halcon);	
		set_part(m_LogDisplayWinID_Halcon,0,0,height-1,width-1);
		set_check("father");
	}
	set_draw(m_LogDisplayWinID_Halcon,"margin"); //margin or fill
	set_color(m_LogDisplayWinID_Halcon,"red");
	set_line_width(m_LogDisplayWinID_Halcon,HTuple(1));
	pConfigCenter->SetLogWindowHID(m_LogDisplayWinID_Halcon);
}

void CMReportView::SetUIWindow()
{
	m_pListWind =  (CTestListWnd*)((CMainFrame*)(AfxGetApp()->m_pMainWnd))->GetTestListWndID();
}
