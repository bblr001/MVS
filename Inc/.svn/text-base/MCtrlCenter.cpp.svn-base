#include "StdAfx.h"
#include "MCtrlCenter.h"
#include "MConfigCenter.h"
#include "AOIEditVer3.h"
#include "MainFrm.h"
#include "TCppML.h"
#include "TLog.h"
#include "TypeCent.h"

#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG
//////////////////
IPCHub::IPCHub():
	m_uiCmdTransferProxy(IPC_CMD_BUS(CreateUICmdShareMemID().c_str())),
	m_chStatusTransferProxy(IPC_REPORT_BUS(CreateChRptShareMemID().c_str())),
	m_imgTransferProxy(IPC_IMAGE_BUS(CreateImgShareMemID().c_str()))
#ifdef SHEET_INSPECTION
	,
	m_uploadResultFlag(CreateUploadImageFlagShareMemID().c_str()),
	m_channelTestFailFlag(RSLT_FLAG_BUFFER_NAME.c_str()),
	m_channelTestResult(CreateChTestResultShareMemID().c_str()),
	m_errorRgnInfo(CreateChannelErrorRgnInfoShareMemID().c_str()),
	m_channelSentImgFlag(CreateChannelSentImageFlagShareMemID().c_str())
#endif
{
	m_isExit = false;
	Run();
}

IPCHub::~IPCHub()
{	
	m_isExit = true;	
}

wstring IPCHub::CreateUICmdShareMemID()
{
	DWORD dwProcessID = GetCurrentProcessId();
	wchar_t tmpBuff[128];
	::memset((void*)tmpBuff, 0x00, sizeof(wchar_t)*128);
	swprintf_s(tmpBuff,_T("%s-%d:cmd"),_T("FTS2007MICMD"),dwProcessID);
	wstring ret = tmpBuff;

	return ret;
}

wstring IPCHub::CreateChRptShareMemID()
{
	DWORD dwProcessID = GetCurrentProcessId();
	wchar_t tmpBuff[128];
	::memset((void*)tmpBuff, 0x00, sizeof(wchar_t)*128);
	swprintf_s(tmpBuff,_T("%s-%d:report"),_T("FTS2007MICMD"),dwProcessID);
	wstring ret = tmpBuff;

	return ret;
}

wstring IPCHub::CreateImgShareMemID()
{
	DWORD dwProcessID = GetCurrentProcessId();
	wchar_t tmpBuff[128];
	::memset((void*)tmpBuff, 0x00, sizeof(wchar_t)*128);
	swprintf_s(tmpBuff,_T("%s-%d:img"),_T("FTS2007MICMD"),dwProcessID);
	wstring ret = tmpBuff;

	return ret;
}

wstring IPCHub::CreateUploadImageFlagShareMemID()
{
	DWORD dwProcessID = GetCurrentProcessId();
	wchar_t tmpBuff[128];
	::memset((void*)tmpBuff, 0x00, sizeof(wchar_t)*128);
	swprintf_s(tmpBuff, _T("UploadImageCommand#%d"), dwProcessID);
	wstring ret = tmpBuff;
	return ret;
}

wstring IPCHub::CreateChTestResultShareMemID()
{
	DWORD dwProcessID = GetCurrentProcessId();
	wchar_t tmpBuff[128];
	::memset((void*)tmpBuff, 0x00, sizeof(wchar_t)*128);
	swprintf_s(tmpBuff,_T("ChannelInspectionResult#%d"),dwProcessID);
	wstring ret = tmpBuff;

	return ret;
}

wstring IPCHub::CreateChannelErrorRgnInfoShareMemID()
{
	DWORD dwProcessID = GetCurrentProcessId();
	wchar_t tmpBuff[128];
	::memset((void*)tmpBuff, 0x00, sizeof(wchar_t)*128);
	swprintf_s(tmpBuff,_T("ChannelErrorRgnInfo#%d"),dwProcessID);
	wstring ret = tmpBuff;

	return ret;
}

wstring IPCHub::CreateChannelSentImageFlagShareMemID()
{
	DWORD dwProcessID = GetCurrentProcessId();
	wchar_t tmpBuff[128];
	::memset((void*)tmpBuff, 0x00, sizeof(wchar_t)*128);
	swprintf_s(tmpBuff, _T("ChannelSendImgFlagBuff#%d"), dwProcessID);
	wstring ret = tmpBuff;

	return ret;
}

void IPCHub::Close()
{
	m_isExit = true;
}

void IPCHub::ExecuteUICmd(char* cmdData)
{
	CMainFrame* pMainFrm = (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
	auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();

	int cmdCode = cmdData[0];
 	if(cmdCode == RUNNING)
 	{
		pMainFrm->SysRun();	
 	}
	if(cmdCode == PAUSED)
	{
		pMainFrm->SysPause();
	}
	if (cmdCode == UPDATE_TLS_FILE)
	{
		pMainFrm->PostMessage(WM_MI_TLSUPDATE_MESSAGE);
	}				
 	if(cmdCode == DISMISS_WARNING)
 	{
 		CMCtrlCenter::GetSingletonCtrlCenter()->OnClickWarning();
 	}
 	if(cmdCode == USER_ADMIN)
 	{
  		pConfigCenter->SetUserGroup(ADMIN);
  		pMainFrm->SetUserMode(ADMIN);
  		theApp.m_strUser=_T("ADMIN");
		pMainFrm->m_RibbonLbUser->SetText(_T("ADMIN"));
  		theApp.UpdateTitle();
	}
 	if(cmdCode == USER_SLAC_ADMIN)
 	{
 		pConfigCenter->SetUserGroup(SADMIN);
 		pMainFrm->SetUserMode(SADMIN);
 		theApp.m_strUser=_T("ADMIN");
		pMainFrm->m_RibbonLbUser->SetText(_T("ADMIN"));
 		theApp.UpdateTitle();
 	}
 	if(cmdCode == USER_ENGINEER)
 	{
 		pConfigCenter->SetUserGroup(ENGINEER);
 		pMainFrm->SetUserMode(ENGINEER);
 		theApp.m_strUser=_T("ENGINEER");
		pMainFrm->m_RibbonLbUser->SetText(_T("ENGINEER"));
 		theApp.UpdateTitle();
 	}
 	if(cmdCode == USER_OPERATOR)
 	{
 		pConfigCenter->SetUserGroup(OPERATOR);
 		pMainFrm->SetUserMode(OPERATOR);
 		theApp.m_strUser=_T("OPERATOR");
		pMainFrm->m_RibbonLbUser->SetText(_T("OPERATOR"));
		theApp.UpdateTitle();
	}			
}

UINT IPCHub::Main()
{
	m_isExit = false;

	auto pCtrlCenter = CMCtrlCenter::GetSingletonCtrlCenter();
	if(pCtrlCenter != nullptr)
	{
		pCtrlCenter->m_pChannelStatusTransferProxy  = &m_chStatusTransferProxy;
		pCtrlCenter->m_pImgTransferProxy            = &m_imgTransferProxy;
#ifdef SHEET_INSPECTION
		pCtrlCenter->m_pChTestFailFlag     = &m_channelTestFailFlag;
		pCtrlCenter->m_pChTestResultBuff   = &m_channelTestResult;
		pCtrlCenter->m_pErrorRgnInfoBuff   = &m_errorRgnInfo;
		pCtrlCenter->m_pChannelSentImgFlag = &m_channelSentImgFlag;
		pCtrlCenter->m_pUploadResultFlag   = &m_uploadResultFlag;
#endif
	}
 	while (!m_isExit)
 	{
		char retCmd[2]; retCmd[0] = (char)-1; retCmd[1] = 0;
		if(m_uiCmdTransferProxy.Read(sizeof(char),retCmd,2) && retCmd[0] != (char)-1)
		{
			ExecuteUICmd(retCmd);
		}
#ifdef SHEET_INSPECTION
		char buff[2];buff[0] = 0; buff[1] = 0;
		if(m_uploadResultFlag.Read(sizeof(char),buff, 2) && buff[0] == (char)1)
		{
			CMData retData;
			if(pCtrlCenter->ConcatChannelInspectionResult(retData))
			{
				pCtrlCenter->UploadChannelInspectionResult(retData);
			}
		}
#endif
		Sleep(5);
 	}
	return 0;
}

std::shared_ptr<CMCtrlCenter>  CMCtrlCenter::m_pSingletonCtrlCenter;


CMCtrlCenter::CMCtrlCenter():
	m_r_buffer_f(COUNT_OF_DATA),
	m_f_buffer_r(COUNT_OF_DATA),
	m_sysStatus(STOPPED),
	m_pChannelStatusTransferProxy(nullptr),
	m_pImgTransferProxy(nullptr)
#ifdef SHEET_INSPECTION
	,
	m_pChTestFailFlag(nullptr),
	m_pChTestResultBuff(nullptr),
	m_pChannelSentImgFlag(nullptr),
	m_resultRepository(3)
#endif
{  
	m_bSelfRunMode = true;
	m_hCameraStopEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
	m_bAlreadInit = FALSE;
}

CMCtrlCenter::~CMCtrlCenter(void)
{
}

bool CMCtrlCenter::Init()
{
	if (m_bAlreadInit)
	{
		return true;
	}
	
	auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();
	
	if (!m_recvCenter.Init())
	{
		return FALSE;
	}
	if (!m_filterCenter.Init())
	{
		return FALSE;
	}
	if (!m_reportCenter.Init())
	{
		return FALSE;
	}
	int nPortNum = pConfigCenter->GetRejectPort();
	m_rejectSignalManager.SetPortNumber(nPortNum);

	char report[4];
	report[0] = (char)INIT;
	report[1] = (char)(1 + pConfigCenter->GetRPort());
	report[2] = (char)(1 + pConfigCenter->GetGPort());
	report[3] = 0;
	m_pChannelStatusTransferProxy->Write(sizeof(char),report, 4);

	Sleep(100);

	report[0] = (char)IDLE;
	m_pChannelStatusTransferProxy->Write(sizeof(char),report, 4);

	TLOG_NOTICE(_T("SYSTEM Inited"));
	m_bAlreadInit = TRUE;
	return TRUE;
}

bool CMCtrlCenter::Start()
{
	try
	{	
		Init();

		if (m_sysStatus == STOPPED)
		{	
			m_cmd.Run();
			Sleep(50);

			m_rejectSignalManager.Run();
			Sleep(50);

			m_reportCenter.Start();	
			Sleep(50);

			m_filterCenter.Start();
			Sleep(50);

			m_recvCenter.Start();
			
			m_sysStatus = RUNNING;

			auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();
			char report[4];
			report[0] = (char)RUNNING;
			report[1] = (char)(1 + pConfigCenter->GetRPort());
			report[2] = (char)(1 + pConfigCenter->GetGPort());
			report[3] = 0;
			m_pChannelStatusTransferProxy->Write(sizeof(char), report, 4);

			TLOG_NOTICE(_T("System is started."));
		}
		return TRUE;
	}
	catch (...)
	{
		AfxMessageBox(_T("Run Error"));
	}
	return FALSE;
}

void CMCtrlCenter::Pause()
{
	if (m_sysStatus == RUNNING)
	{ 	
		m_rejectSignalManager.Pause();

		m_recvCenter.Pause();
		Sleep(100);
		m_filterCenter.Pause();
		Sleep(100);
		m_reportCenter.Pause();

		m_sysStatus = PAUSED;

		auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();
		char report[4];
		report[0] = (char)PAUSED;
		report[1] = (char)(1 + pConfigCenter->GetRPort());
		report[2] = (char)(1 + pConfigCenter->GetGPort());
		report[3] = 0;
		m_pChannelStatusTransferProxy->Write(sizeof(char), report, 4);

		TLOG_NOTICE(_T("System is paused."));
	}
}

void CMCtrlCenter::Resume()
{
	if (m_sysStatus == PAUSED)
	{ 	
		m_rejectSignalManager.Resume();
		m_reportCenter.Resume();
		Sleep(50);
		m_filterCenter.Resume();
		Sleep(150);
		m_recvCenter.Resume();

		m_sysStatus = RUNNING;

		auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();
		char report[4];
		report[0] = (char)RUNNING;
		report[1] = (char)(1 + pConfigCenter->GetRPort());
		report[2] = (char)(1 + pConfigCenter->GetGPort());
		report[3] = 0;
		m_pChannelStatusTransferProxy->Write(sizeof(char), report, 4);

		TLOG_NOTICE(_T("System is running."));
	}
}

void CMCtrlCenter::Stop() 
{
	if (m_sysStatus != STOPPED)
	{ 
		m_cmd.Close();
		m_recvCenter.Stop();
		Sleep(50);
		m_filterCenter.Stop();
		Sleep(50);
		m_reportCenter.Stop();
		
		m_rejectSignalManager.Stop();

		m_sysStatus = STOPPED;

		auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();
		char report[4];
		report[0] = (char)STOPPED;
		report[1] = (char)(1 + pConfigCenter->GetRPort());
		report[2] = (char)(1 + pConfigCenter->GetGPort());
		report[3] = 0;
		m_pChannelStatusTransferProxy->Write(sizeof(char), report, 4);
		m_bAlreadInit=FALSE;
		TLOG_NOTICE(_T("System is stopped."));
	}
}

void CMCtrlCenter::TriggerAlarm()
{
	if (m_bSelfRunMode)
	{
		return;
	}
	wstring tmp = theApp.m_strStaionID;
	if (tmp.compare(_T("")) == 0)
	{
		return;
	}
	auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();
	char report[4];
	report[0] = (char)TURN_ON_RED_LIGHT;
	report[1] = (char)(1 + pConfigCenter->GetRPort());
	report[2] = (char)(1 + pConfigCenter->GetGPort());
	report[3] = 0;
	m_pChannelStatusTransferProxy->Write(sizeof(char), report, 4);
}

void CMCtrlCenter::UpdateChannelSettings()
{
	if(m_pChannelStatusTransferProxy == nullptr)
	{
		return;
	}
	if (m_bSelfRunMode)
	{
		return;
	}
	wstring tmp = theApp.m_strStaionID;
	if (tmp.compare(_T("")) == 0)
	{
		return;
	}
	string programName = CMConfigCenter::GetSingletonConfigCenter()->GetProgramName();
	std::vector<char> report;
	report.push_back((char)UPDATE_SETTINGS);
	report.insert(report.begin() + 1,programName.begin(), programName.end());
	report.push_back(0);
	m_pChannelStatusTransferProxy->Write(sizeof(char), &report[0], report.size());
}

void CMCtrlCenter::GenerateRejectionSignal(HTuple receiveTime)
{
	m_rejectSignalManager.AddRejectionSignal(receiveTime);
}

#ifdef SHEET_INSPECTION

void CMCtrlCenter::BackupChannelInspectionResult(SheetInspcData& data)
{
	if(!m_resultRepository.is_not_full())
	{
		SheetInspcData ret;
		m_resultRepository.pop_back(&ret);
	}
	m_resultRepository.push_front(data);
}

// Æ´½Ó8Ö¡Í¼Ïñ
bool CMCtrlCenter::ConcatChannelInspectionImages(SheetInspcData& data,CMData& retData)
{

	Hobject tmpImg0 = data.m_data[0].m_Image;
	Hobject tmpImg1 = data.m_data[2].m_Image;
	Hobject tmpImg2 = data.m_data[4].m_Image;
	Hobject tmpImg3 = data.m_data[6].m_Image;

	//  concat 0-2
	HTuple Width1, Height1;
	get_image_size(tmpImg0, &Width1, &Height1);
	Hobject ObjectsConcat01;
	concat_obj(tmpImg0, tmpImg1, &ObjectsConcat01);
	Hobject tileImage01;
	auto tmpValue0 = HTuple(0).Append(0);
	auto tmpValue = HTuple(-1).Append(-1);
	tile_images_offset(ObjectsConcat01, &tileImage01, HTuple(0).Concat(Height1), tmpValue0, tmpValue, tmpValue, tmpValue, tmpValue, Width1, Height1+Height1);
	//  concat 02-4
	HTuple Width2, Height2;
	get_image_size(tileImage01, &Width2, &Height2);
	concat_obj(tileImage01, tmpImg2, &ObjectsConcat01);
	Hobject tileImage012;
	tile_images_offset(ObjectsConcat01, &tileImage012, HTuple(0).Concat(Height2), tmpValue0, tmpValue, tmpValue, tmpValue, tmpValue, Width1, Height2+Height1);
	// concat 024-6
	HTuple Width3, Height3;
	get_image_size(tileImage012, &Width3, &Height3);
	concat_obj(tileImage012, tmpImg3, &ObjectsConcat01);
	Hobject tileImage0123;
	tile_images_offset(ObjectsConcat01, &tileImage0123, HTuple(0).Concat(Height3), tmpValue0, tmpValue, tmpValue, tmpValue, tmpValue, Width1, Height3+Height1);

	copy_image(tileImage0123, &retData.m_Image);

	return true;
}

// Æ´½Ó8Ö¡Í¼ÏñÖÐ7¸ö¹ÞÉí£¬º¸·ì£¬ºá±ßµÄ´íÎóÇøÓò
bool  CMCtrlCenter::ConcatChannelInspectionErrorReg(SheetInspcData& data,CMData& retData)
{
	m_vErrorRgnInfo.clear();

	auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();
	unsigned int linePerFrame = pConfigCenter->GetLineCountPerFrame();
	unsigned int frameCountPerSheet = pConfigCenter->GetFrameCountPerSheet();
	
	wchar_t sz[256];
	memset(sz, 0, 256*sizeof(wchar_t));
	for(size_t i = 0; i < frameCountPerSheet - 1; i++ )
	{ 
		std::for_each(data.m_data[i].m_errorRgns.begin(), data.m_data[i].m_errorRgns.end(), [&](ERROR_RGN_INFO& errorRgn)
		{
			errorRgn.m_row = errorRgn.m_row + i  * linePerFrame;
		});
		m_vErrorRgnInfo.insert(m_vErrorRgnInfo.end(), data.m_data[i].m_errorRgns.begin(), data.m_data[i].m_errorRgns.end());
	}
	
	return true;
}

bool CMCtrlCenter::ConcatChannelInspectionResult(CMData& retData)
{
	SheetInspcData data;
	m_resultRepository.pop_back(&data);
	if(!ConcatChannelInspectionImages(data, retData))
		return false;
	if(!ConcatChannelInspectionErrorReg(data, retData))
		return false;

	return true;
}

void CMCtrlCenter::PackageChannelInspectionResult(Hobject rsltImage, unsigned char*& pRet,long& width, long& height)
{ 
	char  chType[128];
	Hobject zoomImg;
	long w, h;
	get_image_size(rsltImage,&w, &h);
	zoom_image_size(rsltImage, &zoomImg, 0.0625*w, 0.0625*h, "nearest_neighbor");	
	get_image_pointer1(zoomImg, (long*)&pRet, chType, &width, &height);
}

void CMCtrlCenter::UploadChannelInspectionResult(CMData& retData)
{
	// To notify the main UI that the image is sent.
	char buff[2]; buff[0] = 1; buff[1] = 0;
	m_pChannelSentImgFlag->Write(sizeof(char), buff,2);

	unsigned char* pImage = nullptr;
	long width = 0, height = 0;
	PackageChannelInspectionResult(retData.m_Image, pImage, width, height);
	m_pChTestResultBuff->Write((unsigned char*)pImage, width, height);

	// Send Error Region Information here
	if(!m_vErrorRgnInfo.empty())
	{
		size_t sz = m_vErrorRgnInfo.size();
		std::vector<ERROR_RGN_INFO> tmpContainer;
		ERROR_RGN_INFO tmpValue;
		tmpValue.m_row = sz;
		tmpValue.m_col = sz;
		tmpValue.m_r   = sz;
		tmpContainer.push_back(tmpValue);
		tmpContainer.insert(tmpContainer.begin() + 1, m_vErrorRgnInfo.begin(), m_vErrorRgnInfo.end());
		tmpContainer.swap(m_vErrorRgnInfo);
		m_pErrorRgnInfoBuff->Write(sizeof(ERROR_RGN_INFO), &m_vErrorRgnInfo[0], sz + 1);
		m_vErrorRgnInfo.clear();
	}
	// There is no need to upload image again
	m_pUploadResultFlag->EnableWriteBuff();
}

#endif


