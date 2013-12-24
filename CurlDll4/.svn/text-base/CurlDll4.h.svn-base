

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
	
		NumPart=300;
		Regional_Out = 0;
	
		m_WContrast=30;
		m_NContrast=20;
		AbsJuanYuanWidth=0;
		WidthBianYuan_Deviation=0.9;
		GrayBianYuan_Deviation=100;
	};
protected:
public:
	int  ROIWidth;
	
	float WidthBianYuan_Deviation;
	int GrayBianYuan_Deviation;
	int NBianYuan_SiteDeviationUp;
	int NBianYuan_SiteDeviationLow;

	int WBianYuan_SiteDeviationUp;
	int WBianYuan_SiteDeviationLow;

	int  NumPart;
	float Regional_Out;
	

	int   m_WContrast;
	int m_NContrast;

	int AbsJuanYuanWidth;

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

