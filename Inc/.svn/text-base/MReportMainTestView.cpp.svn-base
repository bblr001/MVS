#pragma once
#include "stdafx.h"
#include "MData.h"
#include "MReportMainTestView.h"
#include "MReportCenter.h"
//#include "MainFrm.h"
#include "Tools.h"

#define ERROR_RSIZE 20

CMReportView::CMReportView()
{
	InitializeCriticalSection(&m_ReportDataMutex);
	m_isExit =false;
	ReportCount=0;
	m_SourceDisplayWinID_Halcon=0;
}

CMReportView::~CMReportView()
{
	//close_window(windowID);
	//close_window(m_SourceDisplayWinID_Halcon);
}

void CMReportView::Report(CMData* pData)
{
	EnterCriticalSection(&m_ReportDataMutex);
	m_localDatas.AddTail(pData->Clon());
	LeaveCriticalSection(&m_ReportDataMutex);


}

void CMReportView::Init(CMReportCenter * pReportCent)
{
	m_pReportCenter = pReportCent;

	m_WindowSize = pReportCent->GetWindowSize();
 	m_pWSourceWindowID=m_WindowSize->m_hWnd;
 	m_pSourceWindowWidth=m_WindowSize->m_Width;
 	m_pSourceWindowHeight=m_WindowSize->m_Height;

	InitWindow();
	SetUIWindow();

}

UINT CMReportView::Main()
{
	CMData* pData;

	set_system("flush_graphic",HTuple("true"));	
	m_isExit = false;
	//while (WAIT_OBJECT_0 == WaitForMultipleObjects(2,m_EventHandles,FALSE,INFINITE))
	while(!m_isExit)
	{
		pData=NULL;
		if (!m_localDatas.IsEmpty())
		{
			EnterCriticalSection(&m_ReportDataMutex);
			pData=m_localDatas.RemoveHead();
			LeaveCriticalSection(&m_ReportDataMutex);
			if (pData==NULL)
			{	
				continue;
			}
			DoReport(pData);
			delete(pData);
			pData=NULL;
		}
		else
		{
			Sleep(500);
		}
	}
	return 0;
}

void CMReportView::Stop()
{

	m_isExit=true;
	//WaitForSingleObject(m_hThread,INFINITE);

	while(!m_localDatas.IsEmpty())
	{
		EnterCriticalSection(&m_ReportDataMutex);
		delete(m_localDatas.RemoveHead());
		LeaveCriticalSection(&m_ReportDataMutex);
		
	}


	m_hThread = NULL;


}
#define FAILCOLUMN 6
#define COUNTCOLUMN 5

inline void CMReportView::DoReport(CMData* pData)
{

	HTuple ReciveNeedTime,ProcessNeedTime,DisplayNeedTime,TotalNeedTime,Recive2ProcessNeedTime,Process2DisplayNeedTime;

	ReportCount++;
	pData->DisplayCount = ReportCount;


	//count_seconds(&pData->DisPlayStartTime);
	disp_obj(pData->m_Image,m_SourceDisplayWinID_Halcon);
	disp_circle(m_SourceDisplayWinID_Halcon,pData->Center_y,pData->Center_x,pData->r_real);

	m_sConect.Format(_T("%d"),pData->ReciveCount);
	//m_pListWind->SetTestListCtrlConect(0,COUNTCOLUMN,m_sConect);

	if (pData->isFail)
	{
		//m_pListWind->SetTestListCtrlConect(0,FAILCOLUMN+1);
		int index=0;
		for (list<SubTestResult*>::iterator it = pData->plSubTestResult.begin(); it!=pData->plSubTestResult.end();it++)
		{
			if ((*it)->isFailSubTest)
			{
				set_color(m_SourceDisplayWinID_Halcon,"blue");
				disp_circle(m_SourceDisplayWinID_Halcon,(*it)->m_ErrorY,(*it)->m_ErrorX,(*it)->m_ErrorR);
				disp_obj(pData->m_Image,m_SourceDisplayWinID_Halcon);
				//m_sConect.Format(_T("%d"),index);
				//m_pListWind->SetTestListCtrlConect(index,FAILCOLUMN);
			}
			index++;
			
		}	
	}

// 	else
// 	{
// 		m_sConect.Format(_T("%d"),index);
// 		m_pListWind->SetTestListCtrlConect(index,FAILCOLUMN);
// 		index++;
// 	}


 	set_color(m_SourceDisplayWinID_Halcon,"red");
 	count_seconds(&pData->DisPlayEndTime);
 	ReciveNeedTime = HTuple("RT=") + HTuple(1000*(pData->ReciveEndTime-pData->ReciveStartTime)) + HTuple("ms");
 	ProcessNeedTime = HTuple("PT=") + HTuple(1000*(pData->ProcessEndTime - pData->ProcessStartTime)) + HTuple("ms");
 	DisplayNeedTime = HTuple("DT=") + HTuple(1000*(pData->DisPlayEndTime - pData->DisPlayStartTime))  + HTuple("ms");
 	TotalNeedTime =  HTuple("TT=") + HTuple(1000*(pData->DisPlayEndTime - pData->ReciveStartTime))  + HTuple("ms");

	Recive2ProcessNeedTime =  HTuple("R2PTime = ") + HTuple(1000*(pData->ProcessStartTime-pData->ReciveEndTime)) + HTuple("ms");
	Process2DisplayNeedTime =  HTuple("P2DTime = ") + HTuple(1000*(pData->DisPlayStartTime-pData->ProcessEndTime)) + HTuple("ms");
	
 	set_tposition( m_SourceDisplayWinID_Halcon, 1, 1);				
 	write_string(m_SourceDisplayWinID_Halcon,ReciveNeedTime);
 
 	set_tposition( m_SourceDisplayWinID_Halcon,20, 1);
 	write_string(m_SourceDisplayWinID_Halcon,ProcessNeedTime);
 
  	set_tposition( m_SourceDisplayWinID_Halcon,40, 1);
  	write_string(m_SourceDisplayWinID_Halcon,DisplayNeedTime);
 
	set_tposition( m_SourceDisplayWinID_Halcon,60, 1);
	write_string(m_SourceDisplayWinID_Halcon,TotalNeedTime);

	set_tposition( m_SourceDisplayWinID_Halcon,80, 1);
	write_string(m_SourceDisplayWinID_Halcon,Recive2ProcessNeedTime);

	set_tposition( m_SourceDisplayWinID_Halcon,100, 1);
	write_string(m_SourceDisplayWinID_Halcon,Process2DisplayNeedTime);


}




void CMReportView::InitWindow()
{
	
	Hobject  image;

	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0; //删除文件名，只获得路径
	wstring m_sLocalPath = szFilePath;
	m_sLocalPath+=_T("Sample.tiff");

	string logfile = ws2s(m_sLocalPath);
	read_image(&image, logfile.c_str());

	if (0!=m_SourceDisplayWinID_Halcon)
	{
		close_window(m_SourceDisplayWinID_Halcon);
		m_SourceDisplayWinID_Halcon=0;
	}

	if (0==m_SourceDisplayWinID_Halcon)
	{
		set_check("~father");
		open_window(0,0,m_pSourceWindowWidth,m_pSourceWindowHeight,m_pWSourceWindowID,"visible","",&m_SourceDisplayWinID_Halcon);	
		set_check("father");
	}
	set_draw(m_SourceDisplayWinID_Halcon,"margin"); //margin or fill
	set_color(m_SourceDisplayWinID_Halcon,"red");
	disp_obj(image, m_SourceDisplayWinID_Halcon);
	set_line_width(m_SourceDisplayWinID_Halcon,HTuple(1));

}

void CMReportView::SetUIWindow()
{
	//m_pListWind=   (CTestListWnd*) ((CMainFrame*)(AfxGetApp()->m_pMainWnd))->GetTestListWndID();


}
