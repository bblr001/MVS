
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
		XMax = 600;
		XMin = 200;
		YMax = 600;
		YMin = 200;
		RMax = 440;
		RMin = 150;

	};
protected:
public:
	Hlong m_Contrast;
	Hlong Select_Shape_Size;
	int XMax;
	int XMin;
	int YMax;
	int YMin;
	int RMax;
	int RMin;


};


class CDoProcess
{

private:
		bool ShowObject;
	CParameter m_Parameters;
	int ch;
	Hobject  Image, Rectangle1, Rectangle2, TemplateBottleRegion;
	Hobject  Domain, SearchROIBottle, ImageReduced, TemplateLabelRegion;
	Hobject  SearchROILabel, ModelImages, ModelRegions, SearchROIs;
	Hobject  GrayRegions;


	// Local control variables 
	HTuple  WindowHandle, BottleModelRow, BottleModelColumn;
	HTuple  BottleModelLength1, BottleModelLength2, BottleModelPhi;
	HTuple  Area, RowBottleRef, ColumnBottleRef, ModelIDBottle;
	HTuple  LabelRow1, LabelRow2, LabelColumn1, LabelColumn2;
	HTuple  Area1, RowLabelRef, ColumnLabelRef, ModelIDLabel1;
	HTuple  ModelIDLabel2, ModelIDsLabel, Index, RowBottle;
	HTuple  ColumnBottle, AngleBottle, ScoreBottle, Row, Column;
	HTuple  Angle, Score, FoundModel, Diffy, Diffx, Diffa;
	HTuple  Time, Color, ModelColor;

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

