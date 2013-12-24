#include "StdAfx.h"
#include "MConfigCenter.h"
#include <direct.h>

std::shared_ptr<CMConfigCenter> CMConfigCenter::m_pSingletonConfigCenter;

CMConfigCenter::CMConfigCenter(void)
{
	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0; //删除文件名，只获得路径
	m_sLocalPath = szFilePath;
	m_bDebugFlag = false;
	m_bProgramChanged = false;
	m_errorImgPaused = false;
	m_TimeInterval=30;
	m_nAlarmThreshold=30;
	m_Rect.SetRectEmpty();
	m_UserGroup = OPERATOR;
	m_bHasFrame = false;
	m_pTestItemList = nullptr;
	m_nTimeInterval = 0;
	m_sTestProgramPath = L"d:\\SLACTST\\";
	m_EncoderDelaySingleCounts = 0;
}
CMConfigCenter::~CMConfigCenter(void)
{
}

