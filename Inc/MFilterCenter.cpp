#include "StdAfx.h"
#include "MFilterCenter.h"
#include "MCtrlCenter.h"
#include "MConfigCenter.h"
#include "AOIEditVer3.h"
#include <intrin.h>
#include <excpt.h>

#pragma intrinsic(_ReadWriteBarrier)

#pragma warning(disable:4005)

#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG

CMFilterCenter::CMFilterCenter(void)
{
	m_isExit = false;
	m_bRejectNGProduct = false;
#ifdef SHEET_INSPECTION
	m_counter = 0;
	m_bAllPassed = true;
#endif
}

CMFilterCenter::~CMFilterCenter(void)
{
	m_isExit=true;
}

BOOL CMFilterCenter::Init()
{
	
	set_system("parallelize_operators", "true");
	return TRUE ;
}

void CMFilterCenter::Resume()
{
	IMActiveObj::Resume();
}

bool CMFilterCenter::UpdateTestItem()
{
	if (m_pTestItemManage.SetTestItemList(CMConfigCenter::GetSingletonConfigCenter()->GetTestItemList()))
	{
		m_pDoProcessList = m_pTestItemManage.GetDoProcessList();
	}
	else 
	{
		AfxMessageBox(_T("Test Item Error"));
		MessageBox(NULL,_T("Cannot find camera !"),theApp.m_strStaionID,MB_OK);
		return false;
	}
	return true;
}

void CMFilterCenter::UpdateTestItemParameter(int order, string paramName)
{
	m_pTestItemManage.UpdateTestItemParameter(order,paramName);
}

void CMFilterCenter::UpdateTestItemParameter()
{
	m_pTestItemManage.UpdateTestItemParameter();
}

UINT CMFilterCenter::Main()
{

	auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();
	m_bRejectNGProduct = pConfigCenter->GetRejectMode()&&(!CMCtrlCenter::GetSingletonCtrlCenter()->m_bSelfRunMode);

	m_isExit = false;
	if(!UpdateTestItem())
		return -1;

	CMData retData;
	// 
	m_pCtrlCenter = CMCtrlCenter::GetSingletonCtrlCenter();
	while (!m_isExit)
	{
		if(!m_pCtrlCenter->m_r_buffer_f.is_not_empty())
		{
			if (m_isExit)
			{
				break;
			}
			Sleep(1);
			continue;
		}

		m_pCtrlCenter->m_r_buffer_f.pop_back(&retData);
		count_seconds(&retData.m_processStartTime);	
		DoFilter(retData);	
		count_seconds(&retData.m_processEndTime);
		m_pCtrlCenter->m_f_buffer_r.push_front(retData);	
	}
	return 0;
}

void CMFilterCenter::Start()
{
	Run();
}
//¹ýÂËÊý¾Ý
inline void CMFilterCenter::DoFilter(CMData& data )
{
	data.m_vSubTestResult.clear();
#ifdef SHEET_INSPECTION
	data.m_errorRgns.clear();
#endif
	auto tmpProcList = *m_pDoProcessList;
	std::for_each(tmpProcList.begin(), tmpProcList.end(),[&](STDoProcess processor)
	{
		SubTestResult testItem;
		processor.process(processor.order, &data, &testItem);
		data.m_vSubTestResult.push_back(testItem);
	});

	if (data.m_isFail && (!data.m_isDebug))
	{ 
#ifdef EOE_INSPECTION
		if(m_bRejectNGProduct)
		{
			m_pCtrlCenter->GenerateRejectionSignal(data.m_reciveStartTime);
		}
#endif

#ifdef SHEET_INSPECTION
		m_bAllPassed = false;
#endif
	}
#ifdef SHEET_INSPECTION
	m_counter++;
	m_vTmpResult.push_back(data);

	if(m_counter % 7 == 0)
	{
		SheetInspcData shots;
		shots.InserData(m_vTmpResult);
		m_pCtrlCenter->BackupChannelInspectionResult(shots);
		HTuple sheetStartTime = m_vTmpResult[0].m_reciveStartTime;

		m_vTmpResult.clear();
		m_counter = 0;

		if(!m_bAllPassed)
		{
			char flag[2]; flag[0] = (char)1; flag[1] = 0;
			m_pCtrlCenter->m_pChTestFailFlag->Write(sizeof(char),flag,2);
			m_bAllPassed = true;

			if(m_bRejectNGProduct)
			{
				m_pCtrlCenter->GenerateRejectionSignal(sheetStartTime);
			}
		}
	}
#endif
}

void CMFilterCenter::Stop()
{
	auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();
	if (pConfigCenter->GetImgSource() == IMG_FILES)
	{
		::WaitForSingleObject(m_pCtrlCenter->m_recvCenter.m_imageFilePump.m_hThread, INFINITE);
	}
	if (pConfigCenter->GetImgSource() == CAMERA_SOURCE)
	{
		::WaitForSingleObject(m_pCtrlCenter->m_hCameraStopEvent, INFINITE);
	}
	m_isExit = true;	
	Sleep(100);
	CloseHandle(m_hThread);
	m_hThread = NULL;
}
