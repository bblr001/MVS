

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
		XMax = 560;
		XMin = 80;
		YMax = 420;
		YMin = 80;
		OffSet_Row = 0;
		OffSet_Column = 0;
		Greediness=0.9;
		MinScore=0.85;
		m_radius=145;
	};
protected:
public:
	int XMax;
	int XMin;
	int YMax;
	int YMin;
	int OffSet_Row;
	int OffSet_Column;
	int m_radius;
	HTuple  ModelID;
	Hobject  Model_XLD_Contours;
	HTuple Region_Model_center;
	string  m_model_path_name;
	string  m_xld_path_name;
	string  m_tuple_path_name;
	float Greediness;
	float MinScore;
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

