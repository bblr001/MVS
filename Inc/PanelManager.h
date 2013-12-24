
#pragma once
#include <string>
#include <utility>
#include <map>
#include <vector>
#include <algorithm>
#include "MyPanel.h"
#include "rejector.h"

#ifdef SHEET_INSPECTION
#include "SheetInspectionPanel.h"
#include "../AOIEdit3/bounded_buffer.h"
#endif

using namespace std;

class CSyncClock;

class CPanelManager 
#ifdef SHEET_INSPECTION
	: public IMActiveObj
#endif
{
public:
	virtual ~CPanelManager();
	CPanelManager();
#ifdef SHEET_INSPECTION
	virtual void Pause()
	{
		IMActiveObj::Pause();
	}
	virtual void Resume()
	{
		IMActiveObj::Resume();
	}
	virtual UINT Main();
	void Close();
	void  TriggerAllChannels()
	{
		::SetEvent(m_hTriggerEvent);
	}
	void RunAllChannels();
	void PauseAllChannels();
	void ResumeAllChannels();
	bool GetSheetImageReadyFlag()
	{
		bool ret = true;
		std::for_each(m_vPanels.begin(), m_vPanels.end(),[&](CMyPanel* pPanel)
		{
			if(!pPanel->GetGenImageOkFlag())
			{
				ret = false;
			}
		});
		return ret;
	}
	void ResetSheetImageReadyFlag()
	{
		std::for_each(m_vPanels.begin(), m_vPanels.end(),[](CMyPanel* pPanel)
		{
			pPanel->ResetGenImageOkFlag();
		});

		char buff[2]; buff[0] = 0; buff[1] = 0;
		m_testFailedFlagBuff.Write(sizeof(char),buff, 2); // 
	}
	bool ProcessChannelInspectionResult(Hobject& retSheetImage, std::vector<Hobject>& errorRgnMarks);
	bool GetNewLoopBeginFlag()
	{
		return m_bNewLoopBgn;
	}
	void SetNewLoopBeginFlag(bool flag)
	{
		WaitForSingleObject(m_hMutex, INFINITE);
		m_bNewLoopBgn = flag;
		ResetEvent(m_hTriggerEvent);
		ReleaseMutex(m_hMutex);
	}
	void DisableWriteTestFailFlag()
	{
		m_testFailedFlagBuff.DisableWriteBuff();
	}
	void EnableWriteTestFailFlag()
	{
		m_testFailedFlagBuff.EnableWriteBuff();
	}
#endif

public:
	static CPanelManager& GetPanelManager();
	CMyPanel* GetPanel(wstring sStation);
	void SetPortST(int port,BYTE st);
	BYTE GetPortST(int port);
	void HandAlarm(int AlarmPort);
	void DoReject(int port,int encoderDelayCount)
	{
		m_rejector.TriggerRejectionSignal(port,encoderDelayCount,ENABLE_REJECT);
	};
	void InitAllChannelProcess();
	void CreateAllPanels();
	void InitAllPanels();
	void StartAllPanels();
	void CloseAllPanels();
	void CloseAllAlarm();
	std::vector<CMyPanel*>* GetPanelContainerPtr()
	{
		return &m_vPanels;
	}
	void UpdatePanelUserGroup(eUSER_GROUP Group);
	eUSER_GROUP GetUserGroup()
	{
		return m_ug;
	}
	void SetUserGroup(eUSER_GROUP ug)
	{
		m_ug = ug;
	}
	wstring MapUserGroup2String(eUSER_GROUP ug)
	{
		wstring strUserGroup(L"");
		if(ug == ADMIN)    strUserGroup = L"ADMIN";
		if(ug == ENGINEER) strUserGroup = L"ENGINEER";
		if(ug == OPERATOR) strUserGroup = L"OPERATOR";
		if(ug == SADMIN)   strUserGroup = L"SADMIN";
		return strUserGroup;
	}
private:
	size_t                          m_nPanelCount;
	std::vector<CMyPanel*>          m_vPanels;
	CRejector                       m_rejector; //Do reject 
	eUSER_GROUP                     m_ug;       // current user group
#ifdef SHEET_INSPECTION
	CSyncClock*            m_pSyncClock;
	FLAG_BUFFER            m_testFailedFlagBuff;  // The main UI will poll this flag, if this flag is set, it means that one channel get failed test result.
	SheetInspectionPanel*  m_pSheetInspecPanel;   // 
	HANDLE                 m_hTriggerEvent;
	HANDLE                 m_hMutex;
	bool                   m_bExit;
	bool                   m_bNewLoopBgn;
	void AdjustErrorRegionCoordinate(std::vector<ERROR_RGN_INFO>* pErrorRegions, double zoomRatio, double adjustFactor, std::vector<Hobject>& retErrorMarks);
#endif
private:
	CPanelManager(CPanelManager const &);
	CPanelManager& operator=(CPanelManager const &);
};

class CSyncClock : public IMActiveObj
{
public:
	CSyncClock(CPanelManager* pPanelManager)
		:m_pPanelManager(pPanelManager),
		 m_bExit(false)
	{
		m_hSyncEvent = CreateEvent(NULL, TRUE, FALSE, _T("SyncEventForTest"));
	}
	virtual ~CSyncClock()
	{
	}
	virtual void Pause()
	{
		IMActiveObj::Pause();
	}
	virtual void Resume()
	{
		IMActiveObj::Resume();
	}
	virtual UINT Main()
	{
		LARGE_INTEGER bgn;
		QueryPerformanceCounter(&bgn);
		LARGE_INTEGER freq;
		QueryPerformanceFrequency(&freq);

		while(!m_bExit)
		{
			LARGE_INTEGER now;
			QueryPerformanceCounter(&now);
			if((now.QuadPart - bgn.QuadPart) * 1000 / (double)freq.QuadPart >= 1000)
			{
				PulseEvent(m_hSyncEvent);
				bgn = now;
			}
			Sleep(10);
		}
		return 0;
	}
	void Stop()
	{
		m_bExit = true;
	}
private:
	bool            m_bExit;
	CPanelManager*  m_pPanelManager;
	HANDLE          m_hSyncEvent;
};

struct ChannelInspectionResultInfo
{
	int                           m_nChannelIndex;
	Hobject*                      m_pImage;
	std::vector<ERROR_RGN_INFO>*  m_pErrorRgns;

	ChannelInspectionResultInfo()
		:m_nChannelIndex(-1),
		 m_pImage(nullptr),
         m_pErrorRgns(nullptr)
	{
	}
	ChannelInspectionResultInfo(const ChannelInspectionResultInfo& other)
	{
		m_nChannelIndex = other.m_nChannelIndex;
		m_pImage        = other.m_pImage;
		m_pErrorRgns    = other.m_pErrorRgns;
	}
	ChannelInspectionResultInfo& operator=(const ChannelInspectionResultInfo& other)
	{
		if(this == &other) return *this;
		m_nChannelIndex = other.m_nChannelIndex;
		m_pImage        = other.m_pImage;
		m_pErrorRgns    = other.m_pErrorRgns;
		return *this;
	}
};

