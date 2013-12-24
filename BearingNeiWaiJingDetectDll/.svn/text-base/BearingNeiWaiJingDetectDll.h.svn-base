

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
		//thred_high = 255;
		//thred_low = 228;
		radius_ext_empha_size=7;
		radius_inner2_enhance=1.5;
		radius_ext2_thred=22;
		ARMin = 6;
		radius_ext_empha_size2=7;
		radius_inner2_enhance2=1.5;
		radius_ext2_thred2=22;
		ARMin2 = 6;
		m_model_path_name="";
		m_region_path_name="";
		m_region1_path_name="";
		m_region2_path_name="";
		//YMax = 420;
		//YMin = 80;
		//RMax = 340;
		//RMin = 250;
	};
protected:
public:
	//int thred_high;
	//int thred_low;
	int radius_ext_empha_size;
	float radius_inner2_enhance;
	int radius_ext2_thred;
	int ARMin;
	int radius_ext_empha_size2;
	float radius_inner2_enhance2;
	int radius_ext2_thred2;
	int ARMin2;
	HTuple  ModelID;
	Hobject  RegionModel;
	Hobject  RegionUnion1;
	Hobject  RegionUnion2;
	string  m_model_path_name;
	string  m_region_path_name;
	string  m_region1_path_name;
	string  m_region2_path_name;
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

