

#ifndef   DLLEXPT
#define DLLEXPT extern "C" __declspec (dllexport )
#endif

#include <string>
using namespace std;
#include "..\Inc\MData.h"

class CDoProcess;

enum IListValue {XMAX=1,YMAX,XMIN,YMIN}; //下拉菜单对应的数值
class CParameter
{
	friend CDoProcess;
public:
	CParameter()
	{
		Thred_Center=0;
	};
protected:
public:
	int Thred_Center;
	Hobject Test_Regist;
	IListValue iList;

};



class CDoProcess
{

private:
		bool ShowObject;
	CParameter m_Parameters;
	int ch;

	double StoredModePhi;

	double StoredModelCenterRow;

	
	double StoredModelCenterColumn;

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

