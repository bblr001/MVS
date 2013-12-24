#ifndef DLLEXPT
#define DLLEXPT extern "C" __declspec (dllexport)
#endif

#include <string>
using namespace std;
#include "..\Inc\MData.h"

class CDoProcess;
#define DefaultWidth 4096  // 默认图像宽度
enum IListValue {XMAX=1, YMAX, XMIN, YMIN}; //下拉菜单对应的数值

class CParameter
{
	friend CDoProcess;

public:
	CParameter()
	{
		CROP_HEIGHT =900;

		Row1 =500;
		Row2 =850;
		Row3 =1400;

		Col1 =100;
		Col2 =2050;
		Col3 =4000;

		Rect01_threshold_min =140;
		Rect02_threshold_min =140;
		Rect03_threshold_min =140;
		Rect04_threshold_min =140;
		Rect05_threshold_min =140;
		Rect06_threshold_min =140;
		Rect07_threshold_min =140;

		//  ADD
		reg1_Col = 1000;
		reg2_Col = 3000;
		width_Min = 1000;
		width_Max = 2000;
		height_Min= 600;
		height_Max= 1200;
	};

protected:

public:
	int CROP_HEIGHT;
public:
	int Row1,Row2,Row3;  // 第一行，第二行，第三行
	int Col1,Col2,Col3;  // 第一列，第二列，第三列

	int Rect01_threshold_min;
	int Rect02_threshold_min;
	int Rect03_threshold_min;
	int Rect04_threshold_min;
	int Rect05_threshold_min;
	int Rect06_threshold_min;
	int Rect07_threshold_min;
//  ADD 
	int reg1_Col, reg2_Col;
	int width_Min, width_Max;
	int height_Min,height_Max;
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
	void SetParmeter(string name, string value);

	void DoProcess(CMData* pData, SubTestResult *testItem);

public:
	// Local iconic variables 
	Hobject  Image01, Image02, TiledImage01, Rect01;
	Hobject  Rect02, Rect06, Rect07, RectImage01, Region01, Rec01;
	Hobject  RectImage02, Region02, Rec02, RectImage06, Region06;
	Hobject  Rec06, RectImage07, Region07, Rec07, Rect03, Rect05;
	Hobject  Rect04, RectImage03, Region03, Rec03, RectImage05;
	Hobject  Region05, Rec05, RectImage04, Region04, Rec04;


	// Local control variables 
	HTuple  Width01, Height01;
	HTuple  Width02, Height02, Width_Tile, Height_Tile, Rec01_Row1;
	HTuple  Rec01_Column1, Rec01_Row2, Rec01_Column2, Rec02_Row1;
	HTuple  Rec02_Column1, Rec02_Row2, Rec02_Column2, Rec06_Row1;
	HTuple  Rec06_Column1, Rec06_Row2, Rec06_Column2, Rec07_Row1;
	HTuple  Rec07_Column1, Rec07_Row2, Rec07_Column2, R8pt1_row;
	HTuple  R8pt1_column, R8pt2_row, R8pt2_column, Rec03_Row1;
	HTuple  Rec03_Column1, Rec03_Row2, Rec03_Column2, Rec05_Row1;
	HTuple  Rec05_Column1, Rec05_Row2, Rec05_Column2, Rec04_Row1;
	HTuple  Rec04_Column1, Rec04_Row2, Rec04_Column2, R9pt1_row;
	HTuple  R9pt1_column, R9pt2_row, R9pt2_column;

	HTuple Rec01_Row,Rec01_Column,Rec01_phi,Rec01_len1,Rec01_len2;
	HTuple Rec07_Row,Rec07_Column,Rec07_phi,Rec07_len1,Rec07_len2;
	HTuple Rec04_Row,Rec04_Column,Rec04_phi,Rec04_len1,Rec04_len2;
	Hobject rectangle1, rectangle2;

	/// add location from guanshen body
	// Local iconic variables 
	Hobject  Image1, Image2, ObjectsConcat, TiledImage1;
	Hobject  Region, ConnectedRegions, SelectedRegions, SelectedRegions1;
	Hobject  RegionErosion, Rectangle1, Rectangle2, Rectangle3;
	Hobject  Circle, Circle1, RegionLines, ImageReduced, ConnectedRegions1;
	Hobject  RegionErosion1, Rectangle4, ImageReduced1, Region1;
	Hobject  ConnectedRegions11, RegionErosion11;


	// Local control variables 
	HTuple  Number, Row, Column, Phi, Length1, Length2;
	HTuple  Row1, Column1, Phi1, Length11, Length12, Row11;
	HTuple  Column11, Phi11, Length121, Length22, han1_row;
	HTuple  han1_col, han1_phi, han1_hwidth, han1_hheight, han7_row;
	HTuple  han7_col, han7_phi, han7_hwidth, han7_hheight;
	
	// revise at 2013/08/14 for adding rotate rectangle
	HTuple  Rec02_Row,  Rec02_Column,  Rec02_phi,  Rec02_len1, Rec02_len2;
	HTuple  Rec06_Row,  Rec06_Column,  Rec06_phi,  Rec06_len1, Rec06_len2;
	// revise at 2013/08/14 for adding guanshen center point axes
	HTuple  Reg1_row, Reg1_col,  Reg2_row, Reg2_col;
	HTuple  Reg1_hwidth, Reg1_hheight, Reg2_hwidth, Reg2_hheight;
	HTuple  Reg1_phi, Reg2_phi;
	// ADD 
	//HTuple Rec02_Row1, Rec02_Column1, Rec02_Row2, Rec02_Column2;
	//HTuple Rec06_Row1, Rec06_Column1, Rec06_Row2, Rec06_Column2;
	HTuple Rec03_Row,Rec03_Column,Rec03_phi,Rec03_len1,Rec03_len2;
	HTuple Rec05_Row,Rec05_Column,Rec05_phi,Rec05_len1,Rec05_len2;
private:
	void PreProcess();
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