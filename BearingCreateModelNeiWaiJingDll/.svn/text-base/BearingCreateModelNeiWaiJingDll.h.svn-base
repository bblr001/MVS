

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

		region_erosion1_size=4;
		region_erosion2_size=7;
		radius_inner_thred=60;
		radius_ext_extract_size=1000;
		m_thred_low1=60;
		m_thred_high1=220;
		m_thred_low2=60;
		m_thred_high2=248;
		CenterOcrModelName="";	
		CenterOcrModelRegion="";
		CenterOcrModelRegion1="";
		CenterOcrModelRegion2="";

		XMax1 = 360;
		XMin1 = 200;
		YMax1 = 280;
		YMin1 = 220;
		XMax2 = 360;
		XMin2 = 200;
		YMax2 = 180;
		YMin2 = 80;
		//RMax = 340;
		//RMin = 250;
	};
protected:
public:
	int region_erosion1_size;
	int region_erosion2_size;
	int radius_inner_thred;
	int radius_ext_extract_size;
	int m_thred_low1;
	int m_thred_high1;
	int m_thred_low2;
	int m_thred_high2;
	string CenterOcrModelName;
	string CenterOcrModelRegion;
	string CenterOcrModelRegion1;
	string CenterOcrModelRegion2;
	int XMax1;
	int XMin1;
	int YMax1;
	int YMin1;
	int XMax2;
	int XMin2;
	int YMax2;
	int YMin2;
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

