//CanBodyDetect01.h
/*
	印刷片料罐身缺陷检测
*/

#ifndef DLLEXPT
#define DLLEXPT extern "C" __declspec (dllexport)
#endif

#include <string>
using namespace std;
#include "..\Inc\MData.h"
#include <vector>

using namespace std;

class CDoProcess;

enum IListValue {REG_1=1,REG_2}; //下拉菜单对应的数值

// 算法要设置的参数
class CParameter
{
	friend CDoProcess;

public:
	CParameter()
	{

		Width_offset =5;
		Height_offset=5;

		MakeSize =5;
		ThresholdValue =20;
		ErrorSize =50;

		// 罐身缺印
		losePrintGrayValue =245;
	};

protected:

public:

	int Width_offset, Height_offset;

	// 罐身缺印
	int losePrintGrayValue;

	// ADD VARIABLE
	int MakeSize;
	int ThresholdValue;
	int ErrorSize;
};

class CDoProcess
{
private:
	CParameter m_Parameters;
	IListValue m_ListReg;
	int ch;
	bool ShowObject;

public:
	CDoProcess();
	void AutoConfig();
	void SetParmeter(string name, string value);
	void DoProcess(CMData* pData, SubTestResult *testItem);

	// local variant definition here
public:
	Hobject  ImageMean, DynThresh,ThreshConnect,PointDynThresh;
	Hobject  rect;	
	Hobject  m_TestRegion;

	Hobject  MianXinDomain,SERIOUS_BlackPoint, SERIOUS_WhitePoint,WhiteImageMean;
	Hobject  SeriousWhiteConnected,SeriousBlackConnected;
	Hobject  BlackImageMean, BlackPointDynThresh, BLACK_POINT;
	Hobject  SeriousBlackPointDynThresh, SeriousWhitePointDynThresh;
	Hobject  testRegion;
	HTuple   Number;
		
	HTuple   testArea, testRow, testColumn, testNumber;
};


CDoProcess m_Process[MAX_CHANGE_COUNT];

DLLEXPT void AutoConfig()
{
	printf("AutoConfig");
};

DLLEXPT void SetParameter(int order, string name, string value)
{
	m_Process[order].SetParmeter(name, value);
};

DLLEXPT void SLACDllDoProcess(int order, CMData* pData, SubTestResult *testItem)
{
	m_Process[order].DoProcess(pData, testItem);
}