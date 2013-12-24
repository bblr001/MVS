

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
		WThresholdValue = 1.5;
		BThresholdValue = -1.5;
		BDefectSize=3;
		WDefectSize=3;
		Regional_Out = 0;
	};
protected:
public:
	float Regional_Out;
	int   ROIWidth;
	float WThresholdValue;
	float BThresholdValue;
	int   WDefectSize;
	int   BDefectSize;

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

	Hobject image;
	Hobject  ROI,Circle1,Circle2;

	Hobject ImageTest,ImageGauss,ThresholdRegion,Defects , DefectsConnectedRegions,SelectedRegion1,SelectedRegion2;

	Hlong error_number;  


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

