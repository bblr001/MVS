

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
		radius_inner=185;
		radius_ext=197;
		radius_inner2=99;
		radius_ext2=117;
		radius_ext_empha_size=7;
		radius_inner2_enhance=1.5;
		radius_ext2_thred=22;
		ARMin = 6;
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
	int radius_inner2;
	int radius_ext2;
	int radius_ext_empha_size;
	float radius_inner2_enhance;
	int radius_ext2_thred;
	int ARMin;

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

