#pragma once

#include <pylon/PylonIncludes.h>
#include "cpp/HalconCpp.h"
#include "MData.h"
#include "IMReport.h"
#include "IMActiveObj.h"
#include "bounded_buffer.h"
//#include <process.h>
#include <list>
#include <string>

using namespace Halcon;
using namespace Pylon;
using namespace GenApi;
using namespace GenICam; 
using namespace std;

class CMReportFile:public IMActiveObj,IMReport
{
public:
	CMReportFile();
	~CMReportFile();

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
	BOOL Init(CMReportCenter * pReportCent);

private:
	virtual void DoReport();
	virtual void ReceiveData(CMData& data);
	int m_ErrorFileCount;
	int m_nPassFileCount;
	wstring m_LocalPath;
	wstring m_LocalLogPath;
	wstring m_CurrentLocalLogPath;
	wstring m_LogImagePath;
	wstring m_LogPassImagePath;
	wstring m_LogFailImagePath;
	wstring m_LogFileName;
	TCHAR m_TempContect[512];
	bool m_bSaveFailedImage;
	bool m_bSavePassImage;
	bool m_isExit;

	CMData m_currentData;
private:
	static const int MAX_DATA_REPOSITORY_SIZE = 10;
	bounded_buffer<CMData>  m_dataToBeReported;
};
