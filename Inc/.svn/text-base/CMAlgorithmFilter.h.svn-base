#pragma once


#include <pylon/PylonIncludes.h>
#include "pylon_utilities.h"
#include "cpp/HalconCpp.h"
#include "MData.h"

#include "IMActiveObj.h"
#include "..\Inc\TestItemManage.h"
#include "IMFilter.h"
#include "TypeCent.h"
#include "RejectNGProduct.h"
#include <list>

using namespace Halcon;
using namespace Pylon;
using namespace GenApi;
using namespace GenICam; 
using namespace std;



class CMFilterCenter;

class CMAlgorithmFilter: protected IMFilter
{

// shared data 
public:
	CMAlgorithmFilter();
	BOOL Init(CMFilterCenter* pFilterCenter);
	~CMAlgorithmFilter();
	void Stop();
	void Start();

	BOOL SetTestItemList(list<CTlsData*> *itemList);
	void SetChanel(int ch);

	CTestItemManage* m_pTestItemManage;
private:
	CMFilterCenter *m_pFilterCenter;
	list<DllDoProcess>* m_pDoProcessList;



	void FilterData(CMData* testData);

	//virtual EMFILTER_RESULT FilterData(CMData* testData);
	Hlong FilterCount;

	RejectNGProduct m_RejectThread;
	int m_RejectPort;
	bool m_bRunRejectNGProductThread;

};
