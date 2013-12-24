#pragma once

#include <pylon/PylonIncludes.h>
#include "pylon_utilities.h"
#include "cpp/HalconCpp.h"
#include "MData.h"
#include "IMReport.h"

#include "IMActiveObj.h"

//#include <process.h>
#include <list>
//#include "..\BaslerCameraTestDlg.h"

using namespace Halcon;
using namespace Pylon;
using namespace GenApi;
using namespace GenICam; 
using namespace std;


class CMReportCenter;

class CMReportView:public IMActiveObj,IMReport
{

	
// shared data 
public:
	CMReportView();
	~CMReportView();

	UINT Main();
	void Stop();

	void Init(CMReportCenter * pReportCent);
	void InitWindow();
	void SetUIWindow();
	virtual void Report(CMData* pData);

private:
	CMReportCenter * m_pReportCenter;
	CList<CMData*>		m_localDatas;//本地異常數據,尾进头出


	Hlong    m_SourceDisplayWinID_Halcon;
	DisplayWindows *m_WindowSize;

	int	m_pSourceWindowWidth,m_pSourceWindowHeight;
	Hlong m_pWSourceWindowID;

	virtual void DoReport(CMData* pData);

	CRITICAL_SECTION    m_ReportDataMutex;


	bool m_isExit;


	Hlong	ReportCount;

	CString m_sConect;
};
