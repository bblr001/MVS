

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
		Regional_Out=10.0;
		ROIWidth=5;

		BlackMaskSize=9;
		BlackLineDynThresh=5.0;
		BlackLinesLength=8;
		BlackPointDynThresh=5.0;
		BlackPointSize=5;
		SeriousBlackPointDynThresh=5.0;
		SeriousBlackPointSize=5;

		WhiteMaskSize=23;
		WhiteLineDynThresh=5.0;
		WhiteLinesLength=8;
		WhitePointDynThresh=5.0;
		WhitePointSize=8;
		SeriousWhitePointDynThresh=5.0;
		SeriousWhitePointSize=5;

		MeanGrayUpperLimit=100;
		MeanGrayLowerLimit=50;

	};
protected:
public:
	double Regional_Out;
	int   ROIWidth;

	float BlackLineDynThresh,WhiteLineDynThresh;
	float BlackPointDynThresh,WhitePointDynThresh;
	float SeriousBlackPointDynThresh,SeriousWhitePointDynThresh;

	int BlackMaskSize,WhiteMaskSize;
	
	int WhiteLinesLength,WhitePointSize,SeriousWhitePointSize;
	int BlackLinesLength,BlackPointSize,SeriousBlackPointSize;
	int MeanGrayUpperLimit,MeanGrayLowerLimit;


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

