#pragma once

#include "MData.h"
#include "BaslerCamera.h"
#include "CMProcess.h"
#include "ReportDisplayUI.h"
#include "CRecvFile.h"
#include <omp.h>


class CProcess;
class CMRecvFile;
class CBaslerCamera;

class CWorkUnit
{
protected:
	friend CBaslerCamera;
	friend CProcess;
	friend CMRecvFile;

private:


	std::list<CMData*>* m_ReportDataList;
	std::list<CMData*>* m_ReciveDataList;

public:	
	CWorkUnit();
	~CWorkUnit();
	void Init(bool fromCamera);
	void SetSearchPath(string files) {m_RecvFile.SetSearchPath(files.c_str());};


	void InitWindow();
	//void InitUI(Hlong wWindowID,int Width,int Height,Hlong CurrentWID,int CurWidth,int CurHeight);
	void InitUI(Hlong wWindowID,int Width,int Height);
	//void InitUI2(CStatic* ReciveNeedTime ,CStatic* ProcessNeedTime,CStatic* DisplayNeedTime, CStatic *TotalNeedTime);
	void Open(int IndexCamera);

	void Start();

	void Pause();

	void Stop();

	void Close();

	void RunThread();

	std::list<CMData*>* GetReportDataList(){return m_ReportDataList;};

	std::list<CMData*>* GetReciveDataList(){return m_ReciveDataList;};

	void LoadTestItem(list<STLSDATA_SUBTEST*> *itemList){m_Process.LoadTestItem(itemList);};

	//UI init 

	//Process init

	//Camera init

	CRITICAL_SECTION    m_NewImageMutex;

	CRITICAL_SECTION    m_ReportDataMutex;


private:
	CDisplayUI m_DisplayUI;
	CBaslerCamera m_Camera;
	CProcess m_Process;
	CMRecvFile m_RecvFile;
	bool m_fromCamera;

};

