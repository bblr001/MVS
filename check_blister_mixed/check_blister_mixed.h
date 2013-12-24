
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
	Hobject  Image, Chambers, ChambersUnion, Classes;
	Hobject  Region, ConnectedRegions, SelectedRegions, RegionTrans;
	Hobject  ImageAffinTrans, ImageReduced, ImageR, ImageG, ImageB;
	Hobject  ClassRegions, FinalClasses, ChambersRemaining, PillsOfOneType;
	Hobject  RegionDifference, MissingPills, WrongPills, WrongNumberOfPills;
	Hobject  LeftOvers, ObjectSelected;


	// Local control variables 
	HTuple  WindowHandle, PhiRef, RowRef, ColumnRef;
	HTuple  PillTypeCount, NumClasses, GMMHandle, Centers, Iter;
	HTuple  Count, FileIndex, Phi, Area1, Row, Column, HomMat2D;
	HTuple  Number, Index, Area, Row1, Column1, Mean, Deviation;
	HTuple  CountFinalClass, Size;

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

