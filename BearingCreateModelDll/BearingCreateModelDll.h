

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

		radius_inner=129;
		radius_ext=167;
		radius_inner_thred=60;
		radius_ext_extract_size=1000;
		m_contrast_low=20;
		m_contrast_high=80;
		CenterOcrModelName="";	
		CenterOcrModelRegion="";
		CenterOcrModelPicture="";

		//XMax = 560;
		//XMin = 80;
		//YMax = 420;
		//YMin = 80;
		//RMax = 340;
		//RMin = 250;
	};
protected:
public:
	int radius_inner;
	int radius_ext;
	int radius_inner_thred;
	int radius_ext_extract_size;
	int m_contrast_low;
	int m_contrast_high;
	string CenterOcrModelName;
	string CenterOcrModelRegion;
	string CenterOcrModelPicture;
	//int XMax;
	//int XMin;
	//int YMax;
	//int YMin;
	//int RMax;
	//int RMin;

};


class CDoProcess
{

private:
	CParameter m_Parameters;
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

