

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

// 		Thred_qian_a=1000;
// 		Thred_qian_b=2000;
		Thred_white=189;
		Thred_black=115;
		Thred_white_point=140;
		Thred_black_point=80;
		Regional_Out = 200;
		Regional_Internal=100;
	};
protected:
public:
// 	int Thred_qian_a;
// 	int Thred_qian_b;
	int Regional_Out;
	int Regional_Internal;
	Hlong Thred_white, Thred_black, Thred_white_point, Thred_black_point;

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

