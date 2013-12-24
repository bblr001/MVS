

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
		Thred_Center1=25;
		Thred_Center2=25;
		XMax = 600;
		XMin = 200;
		YMax = 500;
		YMin = 200;
		RMax = 340;
		RMin = 250;
	};
protected:
public:
	int Thred_Center1;
	int Thred_Center2;
	int XMax;
	int XMin;
	int YMax;
	int YMin;
	int RMax;
	int RMin;

};


class CDoProcess
{

private:
	bool ShowObject;
	CParameter m_Parameters;
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

