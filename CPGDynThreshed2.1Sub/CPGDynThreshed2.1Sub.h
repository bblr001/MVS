

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


		BlackMaskSize = 3;
		WhiteMaskSize = 23;

		BlackPointDynThresh = 5.5;
		BlackPointSize = 4;
		SeriousBlackPointDynThresh=20;
		SeriousBlackPointSize = 1;

		WhitePointDynThresh = 5.5;
		WhitePointSize = 4;
		SeriousWhitePointDynThresh=20;
		SeriousWhitePointSize = 1;

		erosion = 2.5;
		ShapeThreshold =30;
		ShapeSize =20;

		//ZoomRegion=0; 
		//ZoomSubRegion=0;

	};
protected:
public:
	Hobject Test_Regist,Test_Regist_Sub;

	float BlackPointDynThresh,WhitePointDynThresh;
	float SeriousBlackPointDynThresh,SeriousWhitePointDynThresh;

	int BlackMaskSize,WhiteMaskSize,BlackPointSize,WhitePointSize,SeriousBlackPointSize,SeriousWhitePointSize;

	double erosion;
	int ShapeThreshold,ShapeSize/*,ZoomRegion,ZoomSubRegion*/;


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

	double StoredModePhiSub;
	double StoredModelCenterRowSub;
	double StoredModelCenterColumnSub;
	double StoredRadiusSub;
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

