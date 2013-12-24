

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
		radius_inner_mean_size=7;
		radius_ext_empha_size=7;
		radius_inner2_enhance=1.5;
		radius_ext2_thred=22;
		dyn_dark_thred=45;
		dyn_light_thred=52;
		//ARMax = 560;
		ARMin = 6;
		//YMax = 420;
		//YMin = 80;
		//RMax = 340;
		//RMin = 250;
	};
protected:
public:
	int radius_inner_mean_size;
	int radius_ext_empha_size;
	float radius_inner2_enhance;
	int radius_ext2_thred;
	int dyn_dark_thred;
	int dyn_light_thred;
	string  m_region_path_name;
	//int XMax;
	int ARMin;
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

