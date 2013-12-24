

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
		Thred_Center=80;
		Regional_Out=60;
		Thred_Error_qian=0;
		Thred_qian_a=1000;
		Thred_qian_b=2000;
	};
protected:
public:
	int Thred_Center;
	int Thred_Error_qian;
	int Thred_qian_a;
	int Thred_qian_b;

	int Regional_Out;

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

