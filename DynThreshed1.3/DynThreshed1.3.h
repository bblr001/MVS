
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


		BlackMaskSize = 3;
		WhiteMaskSize = 23;

		BlackPointDynThresh = 5.5;
		WhitePointDynThresh = 5.5;

		WhitePointSize = 4;
		SeriousWhitePointSize = 1;

		BlackPointSize = 4;
		SeriousBlackPointSize = 1;

		SeriousBlackPointDynThresh=20;
		SeriousWhitePointDynThresh=20;

		ROIWidth = 3;
		Regional_Out = 0;
	};
protected:
public:
	double Regional_Out;
	int   ROIWidth;

	float BlackPointDynThresh,WhitePointDynThresh;
	float SeriousBlackPointDynThresh,SeriousWhitePointDynThresh;

	int BlackMaskSize,WhiteMaskSize,BlackPointSize,WhitePointSize,SeriousBlackPointSize,SeriousWhitePointSize;




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

