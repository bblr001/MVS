

#ifndef   DLLEXPT
#define DLLEXPT extern "C" __declspec (dllexport )
#endif

#include <string>
using namespace std;
#include "../Inc/MData.h"

class CDoProcess;

class CParameter
{
	friend CDoProcess;
public:
	CParameter()
	{
		Regional_Out=0;
		ROIWidth = 1;
		Minscore = 0.5;
		Greediness = 0.9;
		MinscoreSub = 0.5;
		GreedinessSub = 0.9;
		LayerSub =0;
	};
protected:
public:
	HTuple ModelID,ModelIDSub;
	string modelName,modelNameSub;
	int ROIWidth,LayerSub;
	double Minscore,Regional_Out;
	double Greediness;
	double MinscoreSub;
	double GreedinessSub;

};


class CDoProcess
{

private:
	CParameter m_Parameters;
	int ch;
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


