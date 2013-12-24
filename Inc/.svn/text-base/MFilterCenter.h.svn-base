#pragma once
#include <vector>
#include <list>
#include "IMActiveObj.h"
#include "TlsFileParser.h"
#include "..\Inc\TestItemManage.h"
#include "ShareMem.h"

using namespace std;

class CMCtrlCenter;
class CMConfigCenter;
class CRejector;

class CMFilterCenter : public IMActiveObj
{
public:
	CMFilterCenter(void);
	~CMFilterCenter(void);
	BOOL Init();
	void Start();
	void Stop();
	void FilterData(CMData* testData);

	virtual void Pause()
	{
		IMActiveObj::Pause();
	}

	virtual void Resume();

	BOOL SetTestItemList(list<CTlsData*> *itemList);

	bool UpdateTestItem();

	void UpdateTestItemParameter(int order, string paramName);

	void UpdateTestItemParameter();

protected:
	virtual UINT Main();	
	void DoFilter(CMData& pData);
private:
	CMCtrlCenter* m_pCtrlCenter;
	CTestItemManage m_pTestItemManage;
	std::list<STDoProcess>* m_pDoProcessList;

	bool       m_bRejectNGProduct;
	bool       m_isExit;
#ifdef SHEET_INSPECTION
	std::vector<CMData> m_vTmpResult;
	size_t              m_counter;
	bool                m_bAllPassed;
#endif
};
