

#ifndef   DLLEXPT
#define DLLEXPT extern "C" __declspec (dllexport )
#endif

#include <string>
using namespace std;
#include "..\Inc\MData.h"

class CDoProcess;

class CParameter
{
	friend CDoProcess;
public:
	CParameter()
	{
		MaskSize=23;
		DynThreshold=10;
		AreaLowlimit=200;
		AreaUpperLimit=600;
		RECLowLimit=0.6;
		BlockRadiusLowLimit=20;
		BlockRadiusUpperLimit=200;

	};
protected:
public:
	int MaskSize;
	float DynThreshold;
	int AreaLowlimit,AreaUpperLimit;
	float RECLowLimit;

	int BlockRadiusLowLimit,BlockRadiusUpperLimit;
};


class CDoProcess
{

private:
	CParameter m_Parameters;
	int ch;
	bool ShowObject;
public:
	CDoProcess();
	void AutoConfig();
	void SetParmeter(string name,string value);

	void DoProcess(CMData* pData,SubTestResult *testItem);
};

CDoProcess m_Process[MAX_CHANGE_COUNT];

DLLEXPT void AutoConfig()
{
	printf("AutoConfig");
};

DLLEXPT void SetParameter(int order,string name,string value)
{
	m_Process[order].SetParmeter(name,value);
};

DLLEXPT void SLACDllDoProcess(int order, CMData* pData,SubTestResult *testItem)
{
	m_Process[order].DoProcess(pData,testItem);

};


