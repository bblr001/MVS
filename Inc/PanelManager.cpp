// PanelManager.cpp: implementation of the CPanelManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../Inc/ConfigurationManager.h"
#include "PanelManager.h"
#include <assert.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern MvsConfigurationManager           gConfigManager;
extern std::vector<PROCESS_INFORMATION>  g_processInfo;
extern std::vector<HANDLE>               g_processHandle;

CPanelManager::CPanelManager()
#ifdef SHEET_INSPECTION
	:m_testFailedFlagBuff(RSLT_FLAG_BUFFER_NAME.c_str()),
	 m_pSheetInspecPanel(nullptr),
	 m_bNewLoopBgn(true)
#endif
{
	m_nPanelCount = 0;
	m_ug = OPERATOR;
#ifdef SHEET_INSPECTION
	m_hTriggerEvent = CreateEvent(NULL,TRUE,FALSE, _T("Trigger"));
	m_hMutex        = CreateMutex(NULL, FALSE, _T("UploadCommandSendFlagMutex"));
#endif
}

CPanelManager::~CPanelManager()
{
	std::for_each(m_vPanels.begin(), m_vPanels.end(),[](CMyPanel* ptr)
	{
		delete ptr; ptr = nullptr;
	});
	m_vPanels.clear();

#ifdef SHEET_INSPECTION
	delete m_pSyncClock;        m_pSyncClock = nullptr;
	delete m_pSheetInspecPanel; m_pSheetInspecPanel = nullptr;
#endif

}
//建立stationid与Panel的影射

CPanelManager& CPanelManager::GetPanelManager()
{
	static CPanelManager panelCenter;
	return panelCenter;
}

CMyPanel* CPanelManager::GetPanel(wstring szStationID)
{
	CMyPanel* retPtr = nullptr;
	auto pChannelSetting = gConfigManager.GetChannelSettingPtr();

	for(size_t t = 0; t < m_nPanelCount; ++t)
	{
		if((*pChannelSetting)[t].szStationID == szStationID)
		{
			return m_vPanels[t];
		}
	};
	return retPtr;
}

void CPanelManager::InitAllChannelProcess()
{
	STARTUPINFO si;
	ZeroMemory(&si,sizeof(si)); 
	si.cb            = sizeof(STARTUPINFO);  
	si.dwXCountChars = 500;    
	si.dwYCountChars = 500;    
	si.dwFlags       = STARTF_USESHOWWINDOW|STARTF_USESTDHANDLES;
	si.wShowWindow   = SW_HIDE;    
	si.hStdInput     = stdin;
	si.hStdOutput    = stdout;    
	si.hStdError     = stderr;

	std::wstring strCurrentPath(MAX_PATH ,0);
	size_t sz = GetCurrentDirectory(MAX_PATH,&strCurrentPath[0]);
	std::wstring subStr = strCurrentPath.substr(0, sz);
	subStr.swap(strCurrentPath);
	subStr.clear();
	std::wstring ApplicationName = strCurrentPath.append(_T("\\AOIEDIT.EXE"));

	wstring strUserGroup(L"OPERATOR");

	auto pChannelSetting = gConfigManager.GetChannelSettingPtr();
	m_nPanelCount = pChannelSetting->size();

	std::for_each(pChannelSetting->begin(), pChannelSetting->end(), [&](CHANNEL_SETTING& procSetting)
	{
		CString cmd;
		cmd.Format(_T("$%s$%s$%s$"),procSetting.szStationID.c_str(),procSetting.szProgramName.c_str(),strUserGroup.c_str());

		BOOL fRet = CreateProcess(&ApplicationName[0],cmd.GetBuffer(), NULL, NULL, TRUE, NULL, NULL, NULL, &si, &(procSetting.m_pi));
		if(fRet == false)   
		{   
			AfxMessageBox(_T("Create process  failed"));   
		}   
		else   
		{  
			g_processInfo.push_back(procSetting.m_pi);
			g_processHandle.push_back(procSetting.m_pi.hProcess);
			WaitForInputIdle(procSetting.m_pi.hProcess,INFINITE);   
			CloseHandle(procSetting.m_pi.hThread);   
			CloseHandle(procSetting.m_pi.hProcess);   
		} 
	});
}

void CPanelManager::CreateAllPanels()
{
	for(size_t t = 0; t < m_nPanelCount; ++t)
	{
 		CMyPanel *pPanel = new CMyPanel(this);
		m_vPanels.push_back(pPanel);
	}	
#ifdef SHEET_INSPECTION
	m_pSyncClock = new CSyncClock(this);
	m_pSheetInspecPanel = new SheetInspectionPanel(this);
#endif
}

void CPanelManager::InitAllPanels()
{
	auto pPanelSetting = gConfigManager.GetChannelSettingPtr();
	for(size_t t = 0; t < m_nPanelCount; ++t)
	{
		m_vPanels[t]->Init((*pPanelSetting)[t]);
	}

	m_rejector.Init();
	m_rejector.Run();
#ifdef SHEET_INSPECTION
	m_pSheetInspecPanel->Init();
#endif
}

void CPanelManager::StartAllPanels()
{
#ifdef SHEET_INSPECTION
	Run();
	m_pSyncClock->Run();
	m_pSheetInspecPanel->Run();
#endif
	std::for_each(m_vPanels.begin(), m_vPanels.end(),[](CMyPanel* pPanel)
	{
		pPanel->Run();
	});
}

void CPanelManager::CloseAllPanels()
{
	std::for_each(m_vPanels.begin(), m_vPanels.end(),[](CMyPanel* pPanel)
	{
		pPanel->Stop();
	});
	m_rejector.Stop();
#ifdef SHEET_INSPECTION
	m_pSheetInspecPanel->Stop();
	m_pSyncClock->Stop();
#endif
}

void CPanelManager::SetPortST(int port,BYTE st)
{
	m_rejector.SetPortST(port,st);
}

BYTE CPanelManager::GetPortST(int port)
{
	return m_rejector.GetPortST(port);
}

void CPanelManager::HandAlarm(int AlarmPort)
{
	m_rejector.m_alarmSentry.HandleAlarm(AlarmPort);
}

void CPanelManager::CloseAllAlarm()
{
	std::for_each(m_vPanels.begin(), m_vPanels.end(),[](CMyPanel* pPanel)
	{
		pPanel->ClickedAlarm();
	});
}

void CPanelManager::UpdatePanelUserGroup(eUSER_GROUP Group)
{
	std::for_each(m_vPanels.begin(), m_vPanels.end(),[&](CMyPanel* pPanel)
	{
		pPanel->ChangeUserGroup(Group);
	});
}

#ifdef SHEET_INSPECTION

void CPanelManager::AdjustErrorRegionCoordinate(std::vector<ERROR_RGN_INFO>* pErrorRegions, double zoomRatio, double adjustFactor, std::vector<Hobject>& retErrorMarks)
{
	if(pErrorRegions == nullptr)
		return;
	if(pErrorRegions->empty())
		return;

	auto errorRgns = *pErrorRegions;
	
	for(size_t i = 0; i < errorRgns.size(); i++)
	{
		errorRgns[i].m_row = errorRgns[i].m_row * zoomRatio;
		errorRgns[i].m_col = errorRgns[i].m_col * zoomRatio + adjustFactor;
		errorRgns[i].m_r   = errorRgns[i].m_r ;
		Hobject errorMark;
		gen_circle(&errorMark, errorRgns[i].m_row, errorRgns[i].m_col, errorRgns[i].m_r);
		retErrorMarks.push_back(errorMark);

	}
	
}

bool CPanelManager::ProcessChannelInspectionResult(Hobject& retSheetImage,std::vector<Hobject>& errorRgnMarks)
{
	if(m_vPanels.empty())
		return false;

	std::vector<ChannelInspectionResultInfo> vChannelInspecResult;
	int nChIndex = 0;
	std::for_each(m_vPanels.begin(), m_vPanels.end(),[&](CMyPanel* pPanel)
	{
		if(pPanel != nullptr)
		{
			ChannelInspectionResultInfo tmpInfo;
			tmpInfo.m_nChannelIndex = nChIndex++;
			tmpInfo.m_pImage        = pPanel->GetChannelSheetImage();
			if(pPanel->GetReadErrorRgnInfoOkFlag())
			{
				tmpInfo.m_pErrorRgns = pPanel->GetErrorRgnInfoContainerPtr();
			}
			else
			{
				tmpInfo.m_pErrorRgns = nullptr;
			}
			vChannelInspecResult.push_back(tmpInfo);
		}
	});

	if(vChannelInspecResult.size() != 3)
		return false;
	
	try{
		// Concat channel images here
		Hobject TiledImage  = *(vChannelInspecResult[0].m_pImage);
		Hobject TiledImage1 = *(vChannelInspecResult[1].m_pImage);
		Hobject TiledImage2 = *(vChannelInspecResult[2].m_pImage);
		HTuple  Width1, Height1, Width2, Height2, Width3, Height3;
		get_image_size(TiledImage,  &Width1, &Height1);
		get_image_size(TiledImage1, &Width2, &Height2);
		get_image_size(TiledImage2, &Width3, &Height3);
	
		double zoomSize = 0.0625;
		HTuple  cropLen = 600, cropLenReal = cropLen*zoomSize; // real croplength
		HTuple  cropLen1= 150, cropLen1Real= cropLen1*zoomSize;
		HTuple  cropLenInt, cropLen1Int;
		tuple_int(cropLenReal,&cropLenInt);
		tuple_int(cropLen1Real,&cropLen1Int);
		
		// cam1  :crop cam1 right side
		Hobject Rectangle;
		gen_rectangle2(&Rectangle, Height1/2, (Width1-10-cropLenInt)+(cropLenInt/2), 0, cropLenInt/2,cropLen1Int);

		Hobject ImageReduced;
		reduce_domain(TiledImage, Rectangle, &ImageReduced);
	
		Hobject Regions;
		bin_threshold(ImageReduced, &Regions);
	
		Hobject RegionDifference;
		difference(Rectangle, Regions, &RegionDifference);
	
		Hobject RegionClosing;
		closing_rectangle1(RegionDifference, &RegionClosing, 5, 5);

		HTuple  Row1, Column1, Phi, Length1, Length2;
		smallest_rectangle2(RegionClosing, &Row1, &Column1, &Phi, &Length1, &Length2);
	
		HTuple col = Column1 + Length2;
		if(col<=0)
		{
			HTuple Area, Row, Column;
			area_center(RegionClosing, &Area, &Row, &Column);
			if(Column<=0)
			{
				Column = (Width1-cropLenInt)+(cropLenInt/2);
			}
			col = Column + 5;
		}
	
		Hobject  ImagePart;
		// debug for test
		if(col<=0 || Height1<=0)
		{
			col = Width1;
		}
		crop_part(TiledImage, &ImagePart, 0, 0, col, Height1);
		HTuple  Imgpart_Width, Imgpart_Height;
		get_image_size(ImagePart, &Imgpart_Width, &Imgpart_Height);

		// cam2  :crop cam2 left side
		Hobject Rectangle2;
		gen_rectangle2(&Rectangle2, Height2/2, cropLenInt/2+10, 0, cropLenInt/2, cropLen1Int);
	
		Hobject ImageReduced1;
		reduce_domain(TiledImage1, Rectangle2, &ImageReduced1);
	
		Hobject Regions1; 
		bin_threshold(ImageReduced1, &Regions1);

		Hobject RegionDifference1;
		difference(Rectangle2, Regions1, &RegionDifference1);

		Hobject RegionClosing1;
		closing_rectangle1(RegionDifference1, &RegionClosing1, 5, 5);
	
		HTuple  Row2, Column2, Phi1, Length11, Length21;
		smallest_rectangle2(RegionClosing1, &Row2, &Column2, &Phi1, &Length11, &Length21);
	
		HTuple  col1 = Column2+Length21;
		if(col1<=0)
		{
			HTuple Area, Row, Column;
			area_center(RegionClosing1, &Area, &Row, &Column);
			if(Column<=0)
			{
				Column = cropLenInt/2;
			}
			col1 = Column + 5;
		}
	
		Hobject ImagePart1;
	
		if(Width2-col1<=0 || Height2<=0)
		{
			col1 = 0;
			Width2-col1 = Width2;
		}
		crop_part(TiledImage1, &ImagePart1, 0, col1, Width2-col1, Height2);
	
		HTuple  Width4, Height4;
		get_image_size(ImagePart1, &Width4, &Height4);
	
		// cam2  :crop cam2 right side
		Hobject Rectangle4;
		gen_rectangle2(&Rectangle4, Height4/2, Width4-10-(cropLenInt/2), 0, cropLenInt/2, cropLen1Int);

		Hobject ImageReduced2;
		reduce_domain(ImagePart1, Rectangle4, &ImageReduced2);
	
		Hobject Regions2;
		bin_threshold(ImageReduced2, &Regions2);
	
		Hobject RegionDifference2;
		difference(Rectangle4, Regions2, &RegionDifference2);

		Hobject RegionClosing2;
		closing_rectangle1(RegionDifference2, &RegionClosing2, 5, 5);

		HTuple  Row3, Column3, Phi2, Length12, Length22;
		smallest_rectangle2(RegionClosing2, &Row3, &Column3, &Phi2, &Length12, &Length22);

		HTuple  col2 = Column3-Length22;
		if(col2<=0)
		{
			HTuple Area, Row, Column;
			area_center(RegionClosing2, &Area, &Row, &Column);
			if(Column<=0)
			{
				Column = Width4-(cropLenInt/2);
			}
			col2 = Column - 5;
		}

		Hobject ImagePart2;
	
		if(col2<=0 || Height4<=0)
		{
			col2 = Width2;
			Height4 = Height2;
		}
		crop_part(ImagePart1, &ImagePart2, 0, 0, col2, Height4);

		HTuple  Imgpart1_Width, Imgpart1_Height;
		get_image_size(ImagePart2, &Imgpart1_Width, &Imgpart1_Height);

		// cam3  :crop cam3 left side
		Hobject Rectangle6;
		gen_rectangle2(&Rectangle6, Height3/2, cropLenInt/2, 0, cropLenInt/2, cropLen1Int);

		Hobject ImageReduced3;
		reduce_domain(TiledImage2, Rectangle6, &ImageReduced3);

		Hobject Regions3;
		bin_threshold(ImageReduced3, &Regions3); 

		Hobject RegionDifference3;
		difference(Rectangle6, Regions3, &RegionDifference3);

		Hobject RegionClosing3;
		closing_rectangle1(RegionDifference3, &RegionClosing3, 5, 5);

		HTuple  Row4, Column4, Phi3, Length13, Length23;
		smallest_rectangle2(RegionClosing3, &Row4, &Column4, &Phi3, &Length13, &Length23);
	
		HTuple  col3 = Column4-Length23;
		if(col3<=0)
		{
			HTuple Area, Row, Column;
			area_center(RegionClosing3, &Area, &Row, &Column);
			if(Column<=0)
			{
				Column = cropLenInt/2;
			}
			col3 = Column - 5;
		}

		Hobject ImagePart3;
	
		if(Width3-col3<=0 || Height3<=0)
		{
			col3 = 0;
			Width3-col3 = Width3;
		}
		crop_part(TiledImage2, &ImagePart3, 0, col3, Width3-col3, Height3);

		HTuple  Imgpart2_Width, Imgpart2_Height;
		get_image_size(ImagePart3, &Imgpart2_Width, &Imgpart2_Height);	

		// cam123  : conjoin ImagePart1 ImagePart2, ImagePart3 together
		Hobject ObjectsConcat1;
		concat_obj(ImagePart, ImagePart2, &ObjectsConcat1);

		Hobject TiledImage12;
		auto tmp = (HTuple(-1).Append(-1));
		tile_images_offset(ObjectsConcat1, &TiledImage12, (HTuple(0).Append(0)), HTuple(0).Concat(Imgpart_Width), 
			tmp, tmp, tmp, tmp, Imgpart_Width+Imgpart1_Width, Imgpart_Height);

		HTuple  Imgpart12_Width, Imgpart12_Height;
		get_image_size(TiledImage12, &Imgpart12_Width, &Imgpart12_Height);

		Hobject ObjectsConcat2;
		concat_obj(TiledImage12, ImagePart3, &ObjectsConcat2);
		Hobject TiledImage123;
		tile_images_offset(ObjectsConcat2, &TiledImage123, (HTuple(0).Append(0)), HTuple(0).Concat(Imgpart12_Width), 
			tmp, tmp, tmp, tmp, Imgpart12_Width+Imgpart2_Width, Imgpart_Height);

		retSheetImage = TiledImage123;

		// Adjust error regions coordinate here
		AdjustErrorRegionCoordinate(vChannelInspecResult[0].m_pErrorRgns, zoomSize, 0.0, errorRgnMarks);
		AdjustErrorRegionCoordinate(vChannelInspecResult[1].m_pErrorRgns, zoomSize, Imgpart_Width[0].D() - col1[0].D(), errorRgnMarks);
		AdjustErrorRegionCoordinate(vChannelInspecResult[2].m_pErrorRgns, zoomSize, Imgpart12_Width[0].D()-col3[0].D(), errorRgnMarks); 
	}
	catch(...)
	{
		// 图像裁剪过程出错
		return false;
	}
	return true;
}

UINT CPanelManager::Main()
{
	while(!m_bExit)
	{
		char buff[2]; buff[0] = 0; buff[1] = 0;
		if(GetNewLoopBeginFlag() && m_testFailedFlagBuff.Read(sizeof(char),buff,2) && (buff[0] == (char)1))
		{
			DisableWriteTestFailFlag();

			SetNewLoopBeginFlag(false);
			m_vPanels[0]->SendUploadImageCommand();
			m_vPanels[2]->SendUploadImageCommand();
			m_vPanels[1]->SendUploadImageCommand();
		}
		Sleep(5);
	}
	return 0;
}

void CPanelManager::Close()
{
	m_bExit = true;
}

void CPanelManager::RunAllChannels()
{
}

void CPanelManager::PauseAllChannels()
{
	m_pSyncClock->Pause();
}

void CPanelManager::ResumeAllChannels()
{
	m_pSyncClock->Resume();
}

#endif  // SHEET_INSPECTION




