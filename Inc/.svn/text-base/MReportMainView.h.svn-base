#pragma once

#include <pylon/PylonIncludes.h>

#include "cpp/HalconCpp.h"
#include "MData.h"
#include "IMReport.h"
#include "ShareMem.h"
#include "bounded_buffer.h"
#include "IMActiveObj.h"
#include "../Inc/TestListWnd.h"

//#include <process.h>
#include <list>
//#include "..\BaslerCameraTestDlg.h"

using namespace Halcon;
using namespace Pylon;
using namespace GenApi;
using namespace GenICam; 
using namespace std;


class CMReportCenter;

class CMReportMainView:public IMActiveObj,IMReport
{
public:
	CMReportMainView();
	~CMReportMainView();

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
	virtual void DoReport();
	virtual void ReceiveData(CMData& data);
	BOOL Init(CMReportCenter * pReportCent);

private:
	CMReportCenter * m_pReportCenter;
	bool m_isExit;

private:
	static const int MAX_DATA_REPOSITORY_SIZE = 2;
	bounded_buffer<CMData> m_dataToBeReported;
	CMData m_currentData;
};
