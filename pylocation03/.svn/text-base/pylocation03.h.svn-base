#ifndef DLLEXPT
#define DLLEXPT extern "C" __declspec (dllexport)
#endif

#include <string>
using namespace std;
#include "..\Inc\MData.h"

class CDoProcess;

struct MyPoint;
struct CalPoint;

#define DefaultWidth 4096
enum IListValue {XMAX=1, YMAX, XMIN, YMIN}; //下拉菜单对应的数值
enum IListValueA {REG01=1,REG04,REG07} /*iList*/; //下拉菜单对应的数值  对应的焊缝区域

class CParameter
{
	friend CDoProcess;

public:
	CParameter()
	{
		rect01_col_offset = 150;
		rect07_col_offset = 2050;
		rect04_col_offset = 4000;

		rect01_thresh_Min = 180;
		rect07_thresh_Min = 180;
		rect04_thresh_Min = 180;
	};

protected:

public:
	int rect01_col_offset, rect07_col_offset, rect04_col_offset;

	int rect01_thresh_Min, rect07_thresh_Min, rect04_thresh_Min;

};
struct MyPoint
{
	HTuple row;
	HTuple col;
	MyPoint()
	{
		row = HTuple();
		col = HTuple();
	}
};
struct CalPoint
{
	MyPoint pt1;
	MyPoint pt2;
	MyPoint pt3;
	MyPoint pt4;
};

class CDoProcess
{
private:
	CParameter m_Parameters;
	enum IListValueA m_ListReg;
	int ch;
	bool ShowObject;
	CalPoint myCalPoint;
public:
	CDoProcess();
	void AutoConfig();
	void SetParmeter(string name, string value);

	void DoProcess(CMData* pData, SubTestResult *testItem);

public:
	CalPoint computeAxes(HTuple &row, HTuple &col, HTuple &phi, HTuple &height, HTuple &width);
	bool     computeLocationBlock(Hobject& srcObj, Hobject& rect, double param, Hobject& retRect, Hlong& hw, HTuple &thresh);
	bool     computeVirticalSeam(Hobject& srcObj, Hobject& rect, double param, Hobject& retRect, HTuple& center_row, HTuple& center_col, HTuple& phi, HTuple& len1, HTuple& len2);
	void     locateCanBody(CalPoint& src1Point, CalPoint& src2Point, Hobject& retObj);
public:
	
	// Local iconic variables 
	Hobject  Image, Image1, ObjectsConcat1, TiledImage;
	Hobject  Region, ConnectedRegions, SelectedRegions, RegionErosion1;
	Hobject  Rect01, Rect07, ImageReduced01, Region01, RegionErosion01;
	Hobject  Rectangle1, ImageReduced02, Region02, RegionErosion02;
	Hobject  Rectangle7, Rect04, ImageReduced04, Region04, RegionErosion04;
	Hobject  Rectangle4, ImageReduced_01, Region_01, RegionErosion_01;
	Hobject  ImageReduced_07, Region_07, RegionErosion_07, ImageReduced_04;
	Hobject  Region_04, RegionErosion_04, Circle, Circle1, Circle2;
	Hobject  Circle3, Circle4, testRegion01, testRegion02;


  // Local control variables 
	HTuple  H1, W1, Width3, Height3, rect01_row, rect01_col;
	HTuple  rect01_phi, rect01_Length1, rect01_Length2, rect07_row;
	HTuple  rect07_col, rect07_phi, rect07_Length1, rect07_Length2;
	HTuple  rect04_row, rect04_col, rect04_phi, rect04_Length1;
	HTuple  rect04_Length2, rec01_Row, rec01_Column, rec01_Phi;
	HTuple  rec01_Length1, rec01_Length2, rec07_Row, rec07_Column;
	HTuple  rec07_Phi, rec07_Length1, rec07_Length2, rec04_Row;
	HTuple  rec04_Column, rec04_Phi, rec04_Length1, rec04_Length2;
	HTuple  rec01_Sin, rec01_Cos, tmp01_r1, tmp01_r2, rec01_pt1_row;
	HTuple  rec01_pt1_col, rec01_pt2_row, rec01_pt2_col, rec01_pt3_row;
	HTuple  rec01_pt3_col, rec01_pt4_row, rec01_pt4_col, rec07_Sin;
	HTuple  rec07_Cos, tmp07_r1, tmp07_r2, rec07_pt1_row, rec07_pt1_col;
	HTuple  rec07_pt2_row, rec07_pt2_col, rec07_pt3_row, rec07_pt3_col;
	HTuple  rec07_pt4_row, rec07_pt4_col, rec04_Sin, rec04_Cos;
	HTuple  tmp04_r1, tmp04_r2, rec04_pt1_row, rec04_pt1_col;
	HTuple  rec04_pt2_row, rec04_pt2_col, rec04_pt3_row, rec04_pt3_col;
	HTuple  rec04_pt4_row, rec04_pt4_col, test01_row, test01_col;
	HTuple  test02_row, test02_col;

	HTuple tile_Width, tile_Height;

	Hobject MainBlock;
	Hobject rect01_disp, rect07_disp, rect04_disp;

	Herror  err;
	char    message[MAX_STRING];
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

