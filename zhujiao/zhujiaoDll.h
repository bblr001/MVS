

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
		Thred_jiao=350;
		Thred_no_jiao=10;
		Regional_Internal = 150;
		Regional_Out = 200;

	};
protected:
public:
	int Thred_jiao;
	int Thred_no_jiao;
	int Thred_jiao_outer;
	int Thred_jiao_inter;

	int Regional_Internal;
	int Regional_Out;

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

