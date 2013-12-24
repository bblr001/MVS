

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


		BlackLineDynThresh=4.5;
		WhiteLineDynThresh=4.5;

		SeriousBlackPointDynThresh=20;
		SeriousWhitePointDynThresh=20;

		BlackMaskSize = 3;
		WhiteMaskSize = 23;

		BlackPointDynThresh = 5.5;
		WhitePointDynThresh = 5.5;

		WhiteLinesLength = 8;
		WhitePointSize = 4;
		SeriousWhitePointSize = 1;

		BlackLinesLength = 8;
		BlackPointSize = 4;
		SeriousBlackPointSize = 1;
	};
protected:
public:
	Hobject Test_Regist;

	float BlackLineDynThresh,WhiteLineDynThresh;
	float BlackPointDynThresh,WhitePointDynThresh;
	float SeriousBlackPointDynThresh,SeriousWhitePointDynThresh;

	int BlackMaskSize,WhiteMaskSize;

	int WhiteLinesLength,WhitePointSize,SeriousWhitePointSize;
	int BlackLinesLength,BlackPointSize,SeriousBlackPointSize;


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

