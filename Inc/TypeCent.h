#pragma once

#include <string>
#include <list>
#include <time.h>
#include <tchar.h>
#include <WinBase.h>
//#include "MCtrlCenter.h"
#define IDC_BTN_ID (IDC_BTN_OPER - BTN_MAX)
#define IDC_BTN_USER IDC_BTN_OPER

using namespace std;
enum eMTI_GUI_STATE {MTI_GUI_INIT,MTI_GUI_IDLE,MTI_GUI_RUN,MTI_GUI_PAUSE,MTI_GUI_STOP,MTI_GUI_ALARM,MTI_GUI_EXIT}; 

enum eUSER_GROUP {ADMIN=0,ENGINEER,OPERATOR,SADMIN};

enum eDRAW_SHAPE {NONE_SHAPE,CIRCLE,ELLIPSE,RECTANGLE,POLYGON,UNION_RGN,DIFFERENCE_RGN,UNDRAW_RGN,SAVE_RGN};

#define FAILRATECOLUMN 4
#define FAILCOLUMN 3
#define COUNTCOLUMN 3

/*class CTestChanelPage;*/


struct STCCOMDB
{
	string programname;
	string tlsname;
	string line;
	string programPath;
	string fixid;
	string commonid;
};

struct STITEM
{
	STITEM()
		:testname(""),
		 m_strSubTestName(""),
		 testid(""),
		 runtest(""),
		 failcount(0),
		 totalFailCount(0),
		 order(0)
	{
	}
	string testname;
	string m_strSubTestName;
	string testid;
	string runtest;
	long failcount;
	long totalFailCount;
	int order;
};

struct ERROR_RGN_INFO
{
	long m_row;
	long m_col;
	long m_r;
	ERROR_RGN_INFO(long row = 0.0, long col = 0.0, long r = 0.0):
		m_row(row),
		m_col(col),
		m_r(r)
	{
	}

	ERROR_RGN_INFO(const ERROR_RGN_INFO& other)
	{
		m_row = other.m_row;
		m_col = other.m_col;
		m_r   = other.m_r;
	}

	ERROR_RGN_INFO& operator=(const ERROR_RGN_INFO& other)
	{
		if(this == &other)
			return *this;
		m_row = other.m_row;
		m_col = other.m_col;
		m_r   = other.m_r;
		return *this;
	}

	// move construction
	ERROR_RGN_INFO(ERROR_RGN_INFO&& other)
	{
		m_row = other.m_row;
		m_col = other.m_col;
		m_r   = other.m_r;
	}

	ERROR_RGN_INFO& operator=(ERROR_RGN_INFO&& other)
	{
		if(this == &other)
			return *this;
		m_row = other.m_row;
		m_col = other.m_col;
		m_r   = other.m_r;
		return *this;
	}
};

struct CHANNEL_SETTING 
{
	CHANNEL_SETTING():szProgramName(_T("")),szStationID(_T(""))
	{ 
		::memset((void*)&m_pi, 0x00, sizeof(PROCESS_INFORMATION));
	}

	CHANNEL_SETTING(const CHANNEL_SETTING& other)
	{
		szProgramName  = other.szProgramName;
		szStationID    = other.szStationID;
		m_channelIndex = other.m_channelIndex;
		memcpy_s((void*)&m_pi, sizeof(PROCESS_INFORMATION), (void*)&other.m_pi, sizeof(PROCESS_INFORMATION));
	}
	CHANNEL_SETTING& operator=(const CHANNEL_SETTING& other)
	{
		if(&other == this)
			return *this;
		szProgramName  = other.szProgramName;
		szStationID    = other.szStationID;
		m_channelIndex = other.m_channelIndex;
		memcpy_s((void*)&m_pi, sizeof(PROCESS_INFORMATION), (void*)&other.m_pi, sizeof(PROCESS_INFORMATION));
		return *this;
	}
	std::wstring         szProgramName;
	std::wstring         szStationID;
	size_t               m_channelIndex;
	PROCESS_INFORMATION  m_pi;
};

#define CHANELDBNAME "testrec.db"

#define COMMONDBNAME _T("COMMONINFO.S3DB")
#define _ADMIN_STR "administrator"
#define _OPERATOR_STR "operator"
#define _ENGINEER_STR "engineer"


// TODO: 在此处引用程序需要的其他头文件
#define MSG_LEN	1024
#define FILE_LEN MAX_PATH
#define FUNC_LEN	64

#define TIME_LEN 20
#define CHART_TOTAL_STEP 18