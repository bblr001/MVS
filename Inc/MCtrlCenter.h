#pragma once

#include "IMActiveObj.h"
#include "MConfigCenter.h"
#include "MRecvCenter.h"
#include "MReportCenter.h"
#include "MFilterCenter.h"
#include "MData.h"
#include "bounded_buffer.h"
#include "VLCtrl.h"
#include <memory>
#include <vector>
#include <algorithm>


using namespace std;

const int COUNT_OF_DATA = 5;

extern CRITICAL_SECTION g_critical_section;

class CMConfigCenter;

class IPCHub: public IMActiveObj
{
public:
	IPCHub();
	~IPCHub();	
	void Close();
	virtual void Pause()
	{
		IMActiveObj::Pause();
	}
	virtual void Resume()
	{
		IMActiveObj::Resume();
	}
protected:
	virtual UINT Main();

private:		
	IPC_CMD_BUS    m_uiCmdTransferProxy;
	IPC_REPORT_BUS m_chStatusTransferProxy; // Channel Report Transfer Proxy:be resonsible for sending status report of channel to the main UI
	IPC_IMAGE_BUS  m_imgTransferProxy;
#ifdef SHEET_INSPECTION
	FLAG_BUFFER           m_uploadResultFlag;
	FLAG_BUFFER           m_channelTestFailFlag;
	FLAG_BUFFER           m_channelSentImgFlag;
	CHANNEL_RESULT_BUFFER m_channelTestResult;
	ERROR_RGN_INFO_BUFFER m_errorRgnInfo;
#endif
	bool m_isExit;

private:
	wstring CreateUICmdShareMemID();
	wstring CreateChRptShareMemID();
	wstring CreateImgShareMemID();
	wstring CreateChTestResultShareMemID();
	wstring CreateChannelErrorRgnInfoShareMemID();
	wstring CreateUploadImageFlagShareMemID();
	wstring CreateChannelSentImageFlagShareMemID();
	void ExecuteUICmd(char* cmdData);
};



const int REJECTION_DELAY = 200;

class CRejectSignalManager : public IMActiveObj
{
public:
	CRejectSignalManager()
		:m_chRejectSignalTransferProxy(PORT_NUM_BUFFER(CreateRejectShareMemID().c_str())),
		 m_rejectionSignals(30),
		 m_nPortNum(-1),
	     m_bExit(false)
	{
	}
	~CRejectSignalManager()
	{
		m_bExit = true;
	}
	virtual void Pause()
	{
		IMActiveObj::Pause();
	}

	virtual void Stop()
	{
		m_bExit=true;
	}
	virtual void Resume()
	{
		IMActiveObj::Resume();
	}
	void SendRejectionSignal()
	{
		char tmp[6];
		char  buff[2];
		char  buff2[4];
		_itoa_s(m_nPortNum,buff,16);
		_itoa_s(m_EncoderDelaySingleCounts,buff2,16);
		tmp[0]=buff[0];
		tmp[1]='$';tmp[2]=buff2[0];tmp[3]=buff2[1];tmp[4]=buff2[2];
		tmp[5]='$';

		m_chRejectSignalTransferProxy.Write(sizeof(char),tmp, 6);
	}
	void SetPortNumber(int nPortNum)
	{
		m_nPortNum = nPortNum;
	}
	void AddRejectionSignal(HTuple startedTime)
	{
		m_rejectionSignals.push_front(startedTime);
	}
protected:
	virtual UINT Main()
	{
		HTuple	now;
		m_bExit = false;
		int RejectDelayTime= CMConfigCenter::GetSingletonConfigCenter()->GetTimeInterval();

		m_EncoderDelaySingleCounts = CMConfigCenter::GetSingletonConfigCenter()->GetEncoderDelaySingleCounts();
		while(!m_bExit)
		{
			HTuple bgnTime;
			m_rejectionSignals.pop_back(&bgnTime);
			count_seconds(&now);
			if((now - bgnTime) * 1000 >= RejectDelayTime)
			{
				SendRejectionSignal();
			}
			else
			{
				m_rejectionSignals.push_front(bgnTime);
			}
		}
		return 0;
	}
private:
	wstring CreateRejectShareMemID()
	{
		DWORD dwProcessID = GetCurrentProcessId();
		wchar_t tmpBuff[128];
		::memset((void*)tmpBuff, 0x00, sizeof(wchar_t)*128);
		swprintf_s(tmpBuff,_T("%s-%d:reject"),_T("FTS2007MICMD"),dwProcessID);
		wstring ret = tmpBuff;

		return ret;
	}
private:
	PORT_NUM_BUFFER             m_chRejectSignalTransferProxy;	//For transferring Reject Signal to SLACMVS main window
	bounded_buffer<HTuple>  m_rejectionSignals;
	int                     m_nPortNum;
	bool                    m_bExit;
	int						m_EncoderDelaySingleCounts;

};

struct SheetInspcData
{
	SheetInspcData()
	{
	}
	SheetInspcData(const SheetInspcData& other)
	{
		m_data.assign(other.m_data.begin(), other.m_data.end());
	}
	SheetInspcData& operator=(const SheetInspcData& other)
	{
		if(&other == this)
			return *this;
		m_data.assign(other.m_data.begin(), other.m_data.end());
		return *this;
	}
	bool InserData(std::vector<CMData>& src)
	{
		if(src.size() != 7)
			return false;
		m_data.assign(src.begin(), src.end());
		return true;
	}
	std::vector<CMData> m_data;
};

class CMCtrlCenter
{
public:	
	~CMCtrlCenter(void);
	static CMCtrlCenter* GetSingletonCtrlCenter()
	{
		EnterCriticalSection(&g_critical_section);
		if(m_pSingletonCtrlCenter == nullptr)
		{
			m_pSingletonCtrlCenter.reset(new CMCtrlCenter);
		}
		LeaveCriticalSection(&g_critical_section);
		return m_pSingletonCtrlCenter.get();
	}

public:
	CMRecvCenter		   m_recvCenter;
	CMReportCenter		   m_reportCenter;
	CMFilterCenter		   m_filterCenter;
	bool				   m_bSelfRunMode;
	IPC_REPORT_BUS*		   m_pChannelStatusTransferProxy;
	IPC_IMAGE_BUS*		   m_pImgTransferProxy;
	IPCHub		           m_cmd;
	CRejectSignalManager   m_rejectSignalManager;
	CVLCtrl                m_VLproxy;    // Used to adjust the light
	bounded_buffer<CMData> m_r_buffer_f; // buffer between receive center and filter center
	bounded_buffer<CMData> m_f_buffer_r; // buffer between filter center and report center
	HANDLE                 m_hCameraStopEvent;
	BOOL				   m_bAlreadInit;
public:
	void UpdateSingleFrame()// 更新信号状态
	{
		m_recvCenter.UpdateSingleFrame();
	} 
	void TriggerCamera()
	{
		m_recvCenter.TriggerCamera();
	}
	CMData GetFrameFromReport()//从处理完的数据中取一个数据在调试时使
	{
		return m_reportCenter.GetFrameFromReport();
	} 
	void RecvOneFrame()//给参数调试时用. 
	{
		m_recvCenter.RecvOneFrame();
	} 
	void UpdateTestItem()
	{
		m_filterCenter.UpdateTestItem();
		// Updta the test list here
		m_reportCenter.UpdataTestList();
	}
	void UpdateTestItemParameter(int order, string paramName)
	{
		m_filterCenter.UpdateTestItemParameter( order,  paramName);
	}
	void UpdateTestItemParameter()
	{
		m_filterCenter.UpdateTestItemParameter();
	}
	void OnClickWarning()
	{
		m_reportCenter.OnClickWarning();
	}
	void SetTestRecordDef()
	{
		m_reportCenter.SetTestRecordDef();
	}
	int GetSysStatus()
	{
		return m_sysStatus;
	}
	bool IsLightCtrollerConnected()
	{
		return m_VLproxy.GetConnectedFlag();
	}
	void UpdateMainWndImage(Hobject* Image)
	{
		if(m_pImgTransferProxy != nullptr)
		{
			m_pImgTransferProxy->Write(Image);
		}
	}
	bool Init();
	bool Start();
	void Stop() ;
	void Pause();
	void Resume();
	void UpdateChannelSettings();
	void TriggerAlarm();
	void GenerateRejectionSignal(HTuple receiveTime);
#ifdef SHEET_INSPECTION
	FLAG_BUFFER*                   m_pChTestFailFlag;
	FLAG_BUFFER*                   m_pChannelSentImgFlag;
	FLAG_BUFFER*                   m_pUploadResultFlag;
	CHANNEL_RESULT_BUFFER*         m_pChTestResultBuff;
	ERROR_RGN_INFO_BUFFER*         m_pErrorRgnInfoBuff;
	bounded_buffer<SheetInspcData> m_resultRepository;
	std::vector<ERROR_RGN_INFO>    m_vErrorRgnInfo;
	void BackupChannelInspectionResult(SheetInspcData& data);
	void PackageChannelInspectionResult(Hobject rsltImage, unsigned char*& pRet, long& width, long& height);
	bool ConcatChannelInspectionImages(SheetInspcData& data,CMData& retData);
	bool ConcatChannelInspectionErrorReg(SheetInspcData& data,CMData& retData);
	bool ConcatChannelInspectionResult(CMData& retData);
	void UploadChannelInspectionResult(CMData& retData);
#endif
private:
	static std::shared_ptr<CMCtrlCenter> m_pSingletonCtrlCenter;
	CMCtrlCenter();
	int m_sysStatus; // Running, Paused, Stopped;
};
