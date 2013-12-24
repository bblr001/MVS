

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
		Width = 3;
		ThresholdValue = 18;
		NumPart=300;
		Regional_Out = 0;
	};
protected:
public:
	int  Width;
	float ThresholdValue;
	int  NumPart;
	float Regional_Out;
	int Thred_no_butu;
	int Thred_Sing_MeanGrayLowerLimit;
	Hobject Test_Regist;
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


	Hobject  Circle1, Circle2, JuanYuanRegion, JuanYuanDomain,JuanYuanDomain1;
	Hobject  PolarTransImage, JuanYuanPartitioned, ResultDefect;
	Hobject  BackTransRegion;

	Hobject  CheckRegion,RegionIntersection,TestRegion;

	// Local control variables 
	HTuple  Pointer, Type, WidthOri, HeightOri;

	HTuple  PolarTransImageWidth, PolarTransImageHeight;
	HTuple  Mean, Deviation, Mean_Lenght, Mean_deviation;
	HTuple  i, Exp, Abs, AbsSorted, LocationId, Length;

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

