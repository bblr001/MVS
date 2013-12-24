

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


		BlackMaskSize =1;
		BThresholdLower = 1;
		BThresholdUpper = 10;
		BDefectSize=300;
		BDefectSizeUpper=1000;
		WhiteMaskSize =1;
		WThresholdLower = 1;
		WThresholdUpper = 10;
		WDefectSize=300;
		WDefectSizeUpper=1000;

	};
protected:
public:
	Hobject Test_Regist;

	double   WhiteMaskSize,BlackMaskSize;
	int  BThresholdLower,BThresholdUpper;
	int  WThresholdLower,WThresholdUpper; 
	int  BDefectSize,WDefectSize,BDefectSizeUpper,WDefectSizeUpper;

};


class CDoProcess
{

private:
	CParameter m_Parameters;
	int ch;
	bool ShowObject;

	double StoredModePhi;
	double StoredModelCenterRow;
	double StoredModelCenterColumn;
	double StoredRadius;
public:
	CDoProcess();
	void AutoConfig();
	void SetParmeter(string name,string value);

	void DoProcess(CMData* pData,SubTestResult *testItem);
	string m_ProcessName;
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

