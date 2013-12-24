#pragma once

#include "stdafx.h"
#include "CMAlgorithmFilter.h"
#include "MFilterCenter.h"

#include "MData.h"
#include <omp.h>

CMAlgorithmFilter::CMAlgorithmFilter()
{
	m_pTestItemManage = new CTestItemManage();
	FilterCount=0;
	m_RejectPort = 0;
	m_bRunRejectNGProductThread=false;
}

void CMAlgorithmFilter::SetChanel(int ch)
{
	m_pTestItemManage->SetChanel(ch);
}
BOOL CMAlgorithmFilter::Init(CMFilterCenter* pFilterCenter)
{
	// -----------------  WAIT FOR EVENTS  ----------------------------- 
	m_pFilterCenter = pFilterCenter;
	m_bRunRejectNGProductThread = pFilterCenter->GetRunRejectNGProductThread();
	if (m_bRunRejectNGProductThread)
	{
		m_RejectPort = pFilterCenter->GetRejectPort();
		m_RejectThread.Init();
		m_RejectThread.SetSingeDelayTime(m_pFilterCenter->GetSingeDelayTime());
	}
	return TRUE;
}

BOOL CMAlgorithmFilter::SetTestItemList(list<CTlsData*> *itemList)
{

	if (m_pTestItemManage->SetTestItemList(itemList))
		m_pDoProcessList = m_pTestItemManage->GetDoProcessList();
	else 
		return FALSE;
	return TRUE;
}

CMAlgorithmFilter::~CMAlgorithmFilter()
{
	delete m_pTestItemManage;
}

void CMAlgorithmFilter::FilterData(CMData* testData)
{

	FilterCount++;
	testData->FilterCount = FilterCount;
#pragma omp parallel
		{
		#pragma omp parallel for
			for(list<DllDoProcess>::iterator it=m_pDoProcessList->begin();it!=m_pDoProcessList->end();it++)
 			{
				SubTestResult *testItem = new SubTestResult();
				
 				(*it)(testData,testItem);
				testData->plSubTestResult.push_back(testItem);
			}
			if (testData->isFail) 
			{
				//Call Reject product....
 				CRejectData* pRejectData = new CRejectData();
 				pRejectData->m_RejectPort = m_RejectPort;
 
 				m_RejectThread.DoReject(pRejectData);
				return ;
			}
		}		
	return ;

}



void CMAlgorithmFilter::Stop()
{
	m_RejectThread.Stop();
}


void CMAlgorithmFilter::Start()
{
	m_RejectThread.Run();
}