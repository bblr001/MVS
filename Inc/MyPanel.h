#pragma once

//
#include "MyButton.h"
#include "TypeCent.h"
#include "..\Inc\MyLabel.h"
#include "GraphObject.h"
#include "ShareMem.h"
#include "DBControl.h"
#include "function.h"
#include <cpp/HalconCpp.h>
#include "SqliteDB.h"
#include "CppSQLite3.h"
#include "IMActiveObj.h"
#include "../SLACMVSN/ui_decorator.h"
#include <vector>
#include <algorithm>

using namespace std;

#define UM_CONTER	1110

class CPanelManager;
/////////////////////////////////////////////////////////////////////////////
// CMyPanel window

using namespace Halcon;

class CRejectSignalSentry: public IMActiveObj
{
public:
	CRejectSignalSentry();
	~CRejectSignalSentry();	
	void Stop();
	void Init(DWORD dwProcessID);
protected:
	UINT Main();
	virtual void Pause()
	{
		IMActiveObj::Pause();
	}
	virtual void Resume()
	{
		IMActiveObj::Resume();
	}

private:		
	void ProcessChannelRejectReport(int nPortNum,int encoderDelayCount);
	PORT_NUM_BUFFER  m_portNumBuffer;	
	bool             m_isExit;
};

class CMyPanel : public CButton,public IMActiveObj
{
public:
	CMyPanel(CPanelManager* pPanelManager);
	virtual ~CMyPanel();
	virtual void Pause()
	{
		IMActiveObj::Pause();
	}
	virtual void Resume()
	{
		IMActiveObj::Resume();
	}
	virtual UINT Main();
	void Stop();	
	CToolTipCtrl m_tip;	
	VOID SetState(eMTI_GUI_STATE state);
	VOID SetProgramNamePanel(const wchar_t * strName,COLORREF TxtColor = RGB(0,0,0), COLORREF GRDColor = RGB(180,180,180));
	VOID SetStatePromptPanel(const wchar_t * strMsg,COLORREF TxtColor = RGB(0,0,255), COLORREF GRDColor = RGB(180,180,180));

	int Init(CHANNEL_SETTING& panelSetting);
	BOOL ClickedRun();
	BOOL ClickedPause();
	void ChangeUserGroup(eUSER_GROUP group);
	BOOL ClickedShowNGPic();
	BOOL ClickedShowAllPic();
	BOOL ClickedOpenChanel(DWORD dwProcessId);
	BOOL ClickedAlarm();
	BOOL ClickedRecount();
	BOOL ClickedQuery();
	// Generated message map functions
	friend UINT WorkThread(LPVOID lpParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void ClearCounter()
	{
		if(!m_bClearCounter) return;
		if (m_ctlCounter.m_hWnd != NULL)
		{
			m_ctlCounter.SetWindowText(_T("00:00:00"));
		}
	};
	void StopCounter()
	{
		KillTimer(UM_CONTER);
		m_bClearCounter = TRUE;
		m_shHour = 0;
		m_shMinute = 0;
		m_shSecond = 0;
	}
	void PauseCounter()
	{
		KillTimer(UM_CONTER);
	}
	DECLARE_MESSAGE_MAP()
private:
	int m_iHeight;
	int m_iWidth;
	CFont m_font;
	bool m_bReflash;
	CRejectSignalSentry m_rejectSignalSentry; //Transfer Reject Data from AOIEDIT

	DWORD dwProcessId;
	CMyButEnter m_butStation;
	CMyButEnter m_butRun;
	CMyButEnter m_butPause;
	CMyButEnter m_butAlarm;

	CMyButEnter m_butQuery;
	CMyButEnter m_butRecount;

	CMyLabel m_sStateIndicator;
	CMyLabel m_programNamePanel;	
	CMyLabel m_statePromptPanel;
	CGraphObject* m_pGraphObject;
	
	CStatic			m_ctlCounter;
	CStatic			m_Static_MonitorPhoto; // image display window
	Hlong			m_DisplayWinID_Halcon;
	short			m_shHour, m_shMinute,m_shSecond;
	BOOL			m_bClearCounter;

	IPC_CMD_BUS      m_uiCmdProxy;	      // Sent UI commands to channels
	IPC_REPORT_BUS   m_channelReportProxy;  // Channels send commands to the main UI
	IPC_IMAGE_BUS    m_channelImgProxy;     // Process the images sent by channels

	CDBControl<CppSQLite3Query>* m_db;
	bool m_isExit;
	char m_cStartTime[TIME_LEN];
	ui_decorator m_ui_decorator;
	CPanelManager* m_pPanelManager;
	char m_cDbname[MAX_PATH];
	int        m_iGport; //Green Port
	int        m_iRport; //Red Light 
	CHANNEL_SETTING m_pannelSettings;

#ifdef SHEET_INSPECTION
	CHANNEL_RESULT_BUFFER       m_resultDataBuff;
	ERROR_RGN_INFO_BUFFER       m_errorRgnInfoBuff;
	FLAG_BUFFER                 m_uiPullImgCmdBuff;// channel will poll this flag, if it is set, then the inspection result will be send to the main UI
	FLAG_BUFFER                 m_channelSentImagFlagBuff;
	std::vector<unsigned char>  m_vResultData;  // convert those string into an image, and then display it on SheetInspectionPanel
	std::vector<ERROR_RGN_INFO> m_vErrorRgnInfo;
	Hobject                     m_channelSheetImage; 
	bool                        m_bGenImgOk;
	bool                        m_bReadErrorRgnOk;
	HANDLE                      m_hTriggerEvent;
	HANDLE                      m_hMutex;
	bool GenerateImageFromStringStream()
	{
		if(!m_vResultData.empty())
		{
			// Parse the string to get width and height of the image
			auto ret = std::find(m_vResultData.begin(), m_vResultData.end(),(unsigned char)'x');
			if(ret == m_vResultData.end())
				return false;
			size_t xIndex = std::distance(m_vResultData.begin(),ret);
			size_t width  = m_vResultData[xIndex-1] * 100 + m_vResultData[xIndex-2] * 10 + m_vResultData[xIndex-3];
			size_t height = m_vResultData[xIndex+1] + m_vResultData[xIndex+2] * 10 + m_vResultData[xIndex+3] * 100;

			std::vector<unsigned char> chImage;
			chImage.assign(m_vResultData.begin() + 7, m_vResultData.begin() + width * height);
			gen_image1(&m_channelSheetImage, "byte", width, height,(long)&chImage[0]);
			return true;
		}
		return false;
	}
	void ClearInspectionResultContainer()
	{
		m_vResultData.clear();
		m_vResultData = std::vector<unsigned char>(DEFAULT_SIZE, 0);

		m_vErrorRgnInfo.clear();
		m_vErrorRgnInfo = std::vector<ERROR_RGN_INFO>(DEFAULT_ERROR_RGN_COUNTER,ERROR_RGN_INFO());
	}
	void RemoveDummyErrorRegion()
	{
		if(m_vErrorRgnInfo.empty())
			return;
		auto rgn = m_vErrorRgnInfo[0];
		if(rgn.m_row == 0.0 && rgn.m_col == 0.0 && rgn.m_r == 0.0)
		{
			m_vErrorRgnInfo.clear();
			return;
		}

		size_t errorRgnCounter = (size_t)rgn.m_row;
		if(errorRgnCounter > (DEFAULT_ERROR_RGN_COUNTER - 1))
			errorRgnCounter = DEFAULT_ERROR_RGN_COUNTER - 1;
		std::vector<ERROR_RGN_INFO> tmpRgns;
		tmpRgns.assign(m_vErrorRgnInfo.begin() + 1, m_vErrorRgnInfo.begin() + errorRgnCounter);
		m_vErrorRgnInfo.clear();
		m_vErrorRgnInfo.swap(tmpRgns);
	}
public:
	bool GetGenImageOkFlag()
	{
		bool ret = false;
		WaitForSingleObject(m_hMutex, INFINITE);
		ret = m_bGenImgOk;
		ReleaseMutex(m_hMutex);
		return ret;
	}
	void SetGenImageOkFlag(bool flag)
	{
		WaitForSingleObject(m_hMutex, INFINITE);
		m_bGenImgOk = flag;
		ReleaseMutex(m_hMutex);
	}
	bool GetReadErrorRgnInfoOkFlag()
	{
		bool ret = false;
		WaitForSingleObject(m_hMutex, INFINITE);
		ret = m_bReadErrorRgnOk;
		ReleaseMutex(m_hMutex);
		return ret;
	}
	void SetReadErrorRgnOkFlag(bool flag)
	{
		WaitForSingleObject(m_hMutex, INFINITE);
		m_bReadErrorRgnOk = flag;
		ReleaseMutex(m_hMutex);
	}
	std::vector<ERROR_RGN_INFO>* GetErrorRgnInfoContainerPtr()
	{
		return &m_vErrorRgnInfo;
	}
	void ResetGenImageOkFlag()
	{
		WaitForSingleObject(m_hMutex, INFINITE);
		m_bGenImgOk = false;
		ReleaseMutex(m_hMutex);
	}
	void ResetReadErrorRgnOkFlag()
	{
		WaitForSingleObject(m_hMutex, INFINITE);
		m_bReadErrorRgnOk = false;
		ReleaseMutex(m_hMutex);
	}
	Hobject* GetChannelSheetImage()
	{
		return &m_channelSheetImage;
	}
	void SendUploadImageCommand()
	{
		char cmd[2];cmd[0] = 1, cmd[1] = 0;
		m_uiPullImgCmdBuff.Write(sizeof(char),cmd,2);
	}
#endif

private:
	void InitButtons(CHANNEL_SETTING& panelSetting);
	void SetStationBtnAccessibility();
	void ProcessChannelStatusReport(char* pReportBuff);

};
