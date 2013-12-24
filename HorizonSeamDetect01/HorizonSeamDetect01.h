/*
	罐身上下横边的检测- 
		-片料在横向存在弯曲的情况，直接画区域检测横边会造成漏检，误检
		-采用分块动态阈值检测
*/
/*
	现在只检测罐身的上边，片料的开头和结尾的横边在另外的算子中做检测
*/
#ifndef DLLEXPT
#define DLLEXPT extern "C" __declspec (dllexport)
#endif

#include <string>
using namespace std;
#include "..\Inc\MData.h"

class CDoProcess;
#define DefaultWidth 4096  // 默认图像宽度
enum IListValue {XMAX=1, YMAX, XMIN, YMIN}; //下拉菜单对应的数值
enum IListValueA {CAN1=1,CAN2} /*iList*/; //下拉菜单对应的数值

class CParameter
{
	friend CDoProcess;

public:
	CParameter()
	{
		len1 = len2 = 0;
		meanSize = 5;
		dynThreshold = 20;
		regShapSize  = 30;
	};

protected:


public:
	
	
	int len1, len2;
	int meanSize;
	int dynThreshold;
	int regShapSize;
};


class CDoProcess
{
private:
	CParameter m_Parameters;
	enum IListValueA m_ListReg;
	int ch;
	bool ShowObject;
public:
	CDoProcess();
	void AutoConfig();
	void SetParmeter(string name, string value);

	void DoProcess(CMData* pData, SubTestResult *testItem);

public:
	// Local iconic variables 
	Hobject Can1Body, Can2Body;
	HTuple  Width, Height;
	Hobject Can1UpSeam, Can1DownSeam;
	Hobject Can2UpSeam, Can2DownSeam;
	bool    FirstFrame, LastFrame;
	Hobject Can1ProcessSeam, Can2ProcessSeam;
	Hobject CanHorizonSeamDef;
	HTuple  errNum;
private:
	void JudgeFramePosition(Hobject& image, bool& firstFrame, bool& lastFrame, CMData* pData);
	void ComputeHorizonSeam(Hobject& image, Hobject& canbody, Hobject& upSeam, Hobject& downSeam, CMData* pData);
	void GetProcessSeam(Hobject& upSeam, Hobject& downSeam, bool& ff, bool& lf, Hobject& outputSeam);
	void DetectHorizonSeamDefect(Hobject& image, Hobject& processBlock,  int& srclen1, int& srclen2, int& meanSize, int& dynThresh, int& shapeSize, Hobject& defect, HTuple& defectNum, Hlong& handle, bool& isDebug);
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