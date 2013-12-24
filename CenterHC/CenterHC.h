

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
		LongAxis = 200;
		ShortAxis = 100;
		m_Contrast = 125;
		Select_Shape_Size=40;
		XMax = 600;
		XMin = 200;
		YMax = 600;
		YMin = 200;
		RMax = 440;
		RMin = 150;

	};
protected:
public:
	int LongAxis,ShortAxis;
	Hlong m_Contrast;
	Hlong Select_Shape_Size;
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

