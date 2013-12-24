

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
		Thred_jin_a=1200;
		Thred_jin_b=800;
		Thred_jin_c=800;
		Regional_Internal = 150;
		Regional_Out = 200;

	};
protected:
public:
	int Thred_jin_a;
	int Thred_jin_b;
	int Thred_jin_c;

	int Regional_Internal;
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

