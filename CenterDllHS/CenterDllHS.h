

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
		XMax = 600;
		XMin = 200;
		YMax = 600;
		YMin = 200;
		RMax = 440;
		RMin = 150;
		Graylowerlimit=90;
		OutlierRemover=100;
		LongAxis = 200;
		ShortAxis = 100;
	};
protected:
public:
	int XMax;
	int XMin;
	int YMax;
	int YMin;
	int RMax;
	int RMin;

	int Graylowerlimit,OutlierRemover;

	int LongAxis,ShortAxis;

};


class CDoProcess
{

private:
		bool ShowObject;
	CParameter m_Parameters;
	int ch;
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

