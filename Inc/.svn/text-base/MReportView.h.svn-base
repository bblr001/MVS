#pragma once
#include "cpp/HalconCpp.h"
#include "MData.h"
#include "IMReport.h"
#include "DBControl.h"
#include "function.h"
#include "SqliteDB.h"
#include "DBControl.h"
#include "CppSQLite3.h"
#include "TypeCent.h"
#include "MConfigCenter.h"
#include "IMActiveObj.h"
#include "bounded_buffer.h"
#include "../Inc/TestListWnd.h"
#include <vector>

using namespace Halcon;
using namespace std;


class CMReportCenter;


class CMReportView:public IMActiveObj,IMReport
{
public:
	CMReportView();
	~CMReportView();

	UINT Main();
	void Stop();
	virtual void Pause()
	{
		IMActiveObj::Pause();
	}

	virtual void Resume()
	{
		m_FailCount = 0;
		m_connectNGCount = 0;
		m_UnitCount=0;
		for (auto it_Item = m_vItem.begin();it_Item!=m_vItem.end();it_Item++)
		{
			(*it_Item).totalFailCount=0;
		}
		IMActiveObj::Resume();
	}

	virtual void DoReport();
	virtual void ReceiveData(CMData& data);
	BOOL Init(CMReportCenter * pReportCent);
	void InitWindow();
	void SetUIWindow();
	void OnClickWarning();
	void SetTestRecordDef();

private:
	CMReportCenter*  m_pReportCenter;
	CTestListWnd*    m_pListWind; 

	Hlong    m_hDispWnd;
	Hlong    m_LogDisplayWinID_Halcon;
	Hlong    m_pWSourceWindowID;
	Hlong    m_pWLogWindowID;
	Hlong    m_reciveCount;

	bool     m_isExit;
	CString  m_sConect;
	clock_t  m_cClock;
	STCCOMDB m_baseInfo;

	long m_UnitCount;
	long m_totalCount;
	long m_totalFailCount;
	long m_UnitFailCount;
	long m_FailCount;

	long m_Top18UnitFailCount;
	long m_Top18UnitCount;

	int  m_connectNGCount;
	int  m_secondCount;
	CDBControl<CppSQLite3Query>* m_db;
	std::vector<STITEM> m_vItem;
	string m_strEventId;

	int m_counter; //frame counts 
	bool m_bAllPassed; // 
	static const int MAX_DATA_REPOSITORY_SIZE = 5;
	bounded_buffer<CMData>  m_dataToBeReported;
	CMData m_currentData;

private:
	void InitSQLiteDB();

public:
	void SelectCheckedTestItem()
	{
		m_vItem.clear();
		auto testsPtr = CMConfigCenter::GetSingletonConfigCenter()->GetTestItemList();
		if(testsPtr == nullptr) return;
		std::for_each(testsPtr->begin(), testsPtr->end(), [&](CTlsData& data)
		{
			auto subtestPtr = data.GetDataSubtest();
			if(!_stricmp(subtestPtr->RunTest.c_str(),"Yes"))
			{
				STITEM item;
				item.testname         = subtestPtr->testName;
				item.m_strSubTestName = subtestPtr->m_strSubTestName;
				item.order            = subtestPtr->order;

				item.failcount = 0;
				item.totalFailCount = 0;
				char sqlbuf[MSG_LEN];
				sprintf_s(sqlbuf, "select testid from tests where testname = '%s' and SubTestName = '%s'",item.testname.c_str(),item.m_strSubTestName.c_str());
				CppSQLite3Query rst = m_db->Query(sqlbuf);
				if (rst.eof())
				{	
					sprintf_s(sqlbuf, "INSERT INTO tests  ('testname','SubTestName') values('%s','%s')",item.testname.c_str(),item.m_strSubTestName.c_str());
					CppSQLite3Query rst = m_db->Query(sqlbuf);

					char sqlbuf[MSG_LEN];
					sprintf_s(sqlbuf, "select testid from tests where testname = '%s' and SubTestName = '%s'",item.testname.c_str(),item.m_strSubTestName.c_str());
					rst = m_db->Query(sqlbuf);
					item.testid = rst.getStringField("testid");
				}
				else
				{
					item.testid = rst.getStringField("testid");
				}
				rst.finalize();
				m_vItem.push_back(item);
			}
		});
	}
	void UpdataTestListItem()
	{
		if(m_db == nullptr)
		{
			return;
		}
		m_vItem.clear();
		auto testsPtr = CMConfigCenter::GetSingletonConfigCenter()->GetTestItemList();
		if(testsPtr == nullptr) 
			return;

		std::for_each(testsPtr->begin(), testsPtr->end(), [&](CTlsData& data)
		{
			auto subtestPtr = data.GetDataSubtest();
			if(!_stricmp(subtestPtr->RunTest.c_str(),"Yes"))
			{
				STITEM item;
				item.testname         = subtestPtr->testName;
				item.m_strSubTestName = subtestPtr->m_strSubTestName;
				item.order            = subtestPtr->order;

				item.failcount = 0;
				item.totalFailCount = 0;
				char sqlbuf[MSG_LEN];
				sprintf_s(sqlbuf, "select testid from tests where testname = '%s' and SubTestName = '%s'",item.testname.c_str(),item.m_strSubTestName.c_str());
				CppSQLite3Query rst = m_db->Query(sqlbuf);
				if (rst.eof())
				{	
					sprintf_s(sqlbuf, "INSERT INTO tests  ('testname','SubTestName') values('%s','%s')",item.testname.c_str(),item.m_strSubTestName.c_str());
					CppSQLite3Query rst = m_db->Query(sqlbuf);

					char sqlbuf[MSG_LEN];
					sprintf_s(sqlbuf, "select testid from tests where testname = '%s' and SubTestName = '%s'",item.testname.c_str(),item.m_strSubTestName.c_str());
					rst = m_db->Query(sqlbuf);
					item.testid = rst.getStringField("testid");
				}
				else
				{
					item.testid = rst.getStringField("testid");
				}
				rst.finalize();
				m_vItem.push_back(item);
			}
		});
	}
};
