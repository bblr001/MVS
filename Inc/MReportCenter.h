#pragma once
#include "imactiveobj.h"
#include "IMActiveObj.h"
#include "IMReport.h"

#include "MReportFile.h"
#include "MReportMainView.h"
#include "MReportView.h"
#include "MConfigCenter.h"

#include <vector>
#include <algorithm>

using namespace std;

class CMData;

//报告中心，把数据报告给显示程序、服务器

class CMReportCenter:public IMActiveObj
{
public:	
	~CMReportCenter(void);
	BOOL Init();	

	bool m_isExit;

	void Start();
	void Stop();
	virtual void Pause();

	virtual void Resume()
	{
		m_reportFile.Resume();
		m_reportMainView.Resume();
		m_reportView.Resume();
		IMActiveObj::Resume();
	}
	
	void OnClickWarning();

	void SetTestRecordDef(){m_reportView.SetTestRecordDef();};

	virtual UINT Main();	

	CMData GetFrameFromReport()
	{
		CMConfigCenter::GetSingletonConfigCenter()->SetHasFrameFlag(m_bHasFrame);
		return m_currentData;
	};

	void UpdataTestList()
	{
		m_reportView.UpdataTestListItem();
	}

	CMData GetCurrentData()
	{
		return m_currentData;
	}
protected:
	friend class CMCtrlCenter;
	CMReportCenter(void);

private:
	std::vector<IMReport*> m_vReport;
	CMData m_currentData;
	CMReportView     m_reportView;
	CMReportFile     m_reportFile;
	CMReportMainView m_reportMainView;
	bool m_bIsSaveFailImage;
	bool m_bHasFrame;
	bool m_bHasMainUI;
};
