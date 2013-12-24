// bottle.cpp : 定义 DLL 应用程序的导出函数。
//


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

		m_Contrast = 125;
		Select_Shape_Size=40;


	};
protected:
public:
	Hlong m_Contrast;
	Hlong Select_Shape_Size;



};


class CDoProcess
{

private:
	CParameter m_Parameters;
	int ch;
		bool ShowObject;


	Hobject  Image, Regions, DarkRegion, RegionOpening;
	Hobject  RegionClosing, RegionFillUp, RegionBorder, RegionDilation;
	Hobject  ImageReduced, Edges, ContoursSplit, UnionContours;
	Hobject  LongestContour, Circle, RegionErosion, RegionDifference;
	Hobject  ImagePolar, ImagePart, ImageScaleMax, ImageMean;
	Hobject  Regions1, Connection, SelectedRegions, RegionClosing1;
	Hobject  RegionUnion, XYTransRegion, ImageRotate, RegionMirror;


	// Local control variables 
	HTuple  SmoothX, ThresholdOffset, MinDefectSize;
	HTuple  PolarResolution, RingSize, StoreEmptyRegion;
	HTuple  WindowHandle, Index, Length, Row, Column, Radius;
	HTuple  StartPhi, EndPhi, PointOrder, Number;
	
public:
	CDoProcess();
	~CDoProcess();
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

