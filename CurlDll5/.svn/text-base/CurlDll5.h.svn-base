

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
		ROIWidth = 3;
		ThresholdValue = 18;
		PartSize=3;
		WindowSize=3;
		Regional_Out = 0;
		MaxGray=190;
	};
protected:
public:
	int  ROIWidth;
	double ThresholdValue;
	int  PartSize;
	int MaxGray;
	int WindowSize;
	double Regional_Out;
};


class CDoProcess
{

private:
	CParameter m_Parameters;
	bool ShowObject;
	int ch;
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
	//printf("AutoConfig");

};

DLLEXPT void SetParameter(int order,string name,string value)
{
	m_Process[order].SetParmeter(name,value);
};

DLLEXPT void SLACDllDoProcess(int order, CMData* pData,SubTestResult *testItem)
{
	m_Process[order].DoProcess(pData,testItem);

};

