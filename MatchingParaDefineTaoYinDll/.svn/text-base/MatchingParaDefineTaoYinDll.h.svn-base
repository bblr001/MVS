

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
		radius_detect=106;
		//thred_high = 255;
		//thred_low = 228;
		m_model_path_name="";
		//m_region_path_name="";
		//m_picture_path_name="";
		Minscore=50;
		Match_Greediness=0.9;
		//ARMin = 6;
	};
protected:
public:
	int radius_detect;
	int Minscore;
	float Match_Greediness;
	//int thred_high;
	//int thred_low;
	HTuple  ModelID;
	//Hobject  RegionDilation_model;
	//Hobject ImageReduced_icon;
	string  m_model_path_name;
	//string  m_region_path_name;
	//string  m_picture_path_name;
	//int YMax;
	//int YMin;
	//int RMax;
	//int ARMin;

};


class CDoProcess
{

private:
	CParameter m_Parameters;
		bool ShowObject;
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

