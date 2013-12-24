#pragma once

#include "..\Inc\PCI2312\Pci2312.h"
#include "IMActiveObj.h"
#include "TypeCent.h"
#include "TLog.h"

#include "..\AOIEdit3\\bounded_buffer.h"

const int  ENABLE_REJECT  = 1;
const int  DISABLE_REJECT = 0;

const int ALARM_SIGNAL = 1;
const int ALL_CLEAR    = 0;

#pragma comment(lib, "..\\Inc\\PCI2312\\PCI2312.lib")
using namespace std;

const UINT ALARM_DISMISS_PORT = 0;
enum REJECT_STEP{NONE=0,INIT_SITE,START_REJECT,END_REJECT};

class CAlarmSentry : public IMActiveObj
{
public:
	CAlarmSentry():m_alarmSignals(2)
	{
		m_bExit = false;
	}
	~CAlarmSentry()
	{
	}

	UINT Main();
	virtual void Pause()
	{
		IMActiveObj::Pause();
	}
	virtual void Resume()
	{
		IMActiveObj::Resume();
	}
	void Stop()
	{
		m_bExit = true;
	}
	void HandleAlarm(int signal)
	{
		if (!m_alarmSignals.is_not_empty())
		{
			m_alarmSignals.push_front(signal);
		}
	}
private:
	bounded_buffer<int> m_alarmSignals;
	bool                m_bExit;
};

struct RejectData
{
	RejectData():port(0),singDelayCounts(0),startSite(0),step(NONE)
	{

	}
	RejectData(const RejectData& other)
	{
		bgn   = other.bgn;
		port  = other.port;
		singDelayCounts= other.singDelayCounts;
		startSite = other.startSite;
		step = other.step;
	}

	RejectData& operator=(const RejectData& other)
	{
		if(this == &other)
			return *this;
		bgn  = other.bgn;
		port = other.port;
		singDelayCounts= other.singDelayCounts;
		startSite = other.startSite;
		step = other.step;
		return *this;
	}

	LARGE_INTEGER  bgn;
	int port;
	long singDelayCounts;
	long startSite;
	REJECT_STEP step;
};

class CRejector:public IMActiveObj
{
public:
	CRejector();
	~CRejector();
	bool Init();
	UINT Main();
	void Stop();

	virtual void Pause()
	{
		IMActiveObj::Pause();
	}
	virtual void Resume()
	{
		IMActiveObj::Resume();
	}
	LARGE_INTEGER  last_bgn[32];
	void TriggerRejectionSignal(int port,int delaycounts,int rejectSignal);
	void SetPortST(int port,BYTE st);
	BYTE GetPortST(int port);
private:

	BYTE m_bDISts[16];

	BYTE m_bDOSts[16];

	HANDLE m_hPCI2312Device;
	HANDLE m_hEventInt;
	int    m_SingeDelayTime;
	int    m_nRejectPort;
	int    m_nAlarmPort;

	int		m_Reject_Delay;
	bool	m_Encoder2ARTCard;
	bool   m_isExit;
	bool   m_bPciIsReady;
	bounded_buffer<RejectData> m_signalTimestamp;

	RejectData m_rejectData;
public:
	CAlarmSentry m_alarmSentry;
};

