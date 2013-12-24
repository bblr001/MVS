#ifndef DLLEXPT
#define DLLEXPT extern "C" __declspec (dllexport)
#endif

#include <string>
using namespace std;
#include "..\Inc\MData.h"

class CDoProcess;
#define DefaultWidth 4096
enum IListValue {XMAX=1, YMAX, XMIN, YMIN}; //下拉菜单对应的数值
enum IListValueA {REG01=1,REG04,REG07} /*iList*/; //下拉菜单对应的数值  对应的焊缝区域

class CParameter
{
	friend CDoProcess;

public:
	CParameter()
	{
		CROP_HEIGHT =900;
		
		templateSize =7;
		tmpDynThreshold =20;
		tmpRegShap_min  =20;
		///
		hwidth_offset  = 0;
		hheight_offset = 0;
	};

protected:

public:
	int CROP_HEIGHT;
public:
	// ADD
	int templateSize;          //模板大小
	int tmpDynThreshold;       //动态阈值大小
	int tmpRegShap_min;        //缺陷区域大小
	///
	int hwidth_offset;
	int hheight_offset;
};


class CDoProcess
{
private:
	CParameter m_Parameters;
	enum IListValueA m_ListReg;
	int ch;

public:
	CDoProcess();
	void AutoConfig();
	void SetParmeter(string name, string value);

	void DoProcess(CMData* pData, SubTestResult *testItem);
	string m_ProcessName;
public:
	double pt1_Lrow,pt1_Lcolumn,pt1_Rrow,pt1_Rcolumn;
	double pt2_Lrow,pt2_Lcolumn,pt2_Rrow,pt2_Rcolumn;

public:
	Hobject currentImg;
	HTuple currentImg_Width,currentImg_Height;
	HTuple Reg01Pt1_row,Reg01Pt1_column,Reg01Pt2_row,Reg01Pt2_column; // ROI1
	HTuple Reg02Pt1_row,Reg02Pt1_column,Reg02Pt2_row,Reg02Pt2_column; // ROI2
	HTuple Reg03Pt1_row,Reg03Pt1_column,Reg03Pt2_row,Reg03Pt2_column; // ROI3
	HTuple Reg04Pt1_row,Reg04Pt1_column,Reg04Pt2_row,Reg04Pt2_column; // ROI4
	HTuple Reg05Pt1_row,Reg05Pt1_column,Reg05Pt2_row,Reg05Pt2_column; // ROI5
	HTuple Reg06Pt1_row,Reg06Pt1_column,Reg06Pt2_row,Reg06Pt2_column; // ROI6
	HTuple Reg07Pt1_row,Reg07Pt1_column,Reg07Pt2_row,Reg07Pt2_column; // ROI7
	HTuple Reg08Pt1_row,Reg08Pt1_column,Reg08Pt2_row,Reg08Pt2_column; // ROI8
	HTuple Reg09Pt1_row,Reg09Pt1_column,Reg09Pt2_row,Reg09Pt2_column; // ROI9

	// local variant
	// ROI对应的矩形区域
	Hobject Rectangle01,Rectangle02,Rectangle03,Rectangle04,Rectangle05,Rectangle06,Rectangle07,Rectangle08,Rectangle09;
	// 由矩形区域得到的ROI
	Hobject Image_Region01,Image_Region02,Image_Region03,Image_Region04,Image_Region05,Image_Region06,Image_Region07,Image_Region08,Image_Region09;
	// 均值图像
	Hobject Image_Mean01,Image_Mean02,Image_Mean03,Image_Mean04,Image_Mean05,Image_Mean06,Image_Mean07,Image_Mean08,Image_Mean09;
	// 
	Hobject defect01,defect02,defect03,defect04,defect05,defect06,defect07,defect08,defect09;
	Hobject Connect_defect01,Connect_defect02,Connect_defect03,Connect_defect04,Connect_defect05,Connect_defect06,Connect_defect07,Connect_defect08,Connect_defect09;
	Hobject Selected_defect01,Selected_defect02,Selected_defect03,Selected_defect04,Selected_defect05,Selected_defect06,Selected_defect07,Selected_defect08,Selected_defect09;
	HTuple  errorNumber01,errorNumber02,errorNumber03,errorNumber04,errorNumber05,errorNumber06,errorNumber07,errorNumber08,errorNumber09;
	Hobject  tmpRectangle,/*m_TestRegion,*/MianXinDomain;
	Hobject  tmpMean_image;
	Hobject  tmpDefect;
	Hobject  tmpConDefect;
	Hobject  tmpSelected_defect;
	HTuple tmpPt1_row,tmpPt1_column;
	HTuple tmpPt2_row,tmpPt2_column;
	HTuple  tmpErrorNum;
	Hobject RegionDilation;

	HTuple tmpRow,tmpColumn,tmpPhi,tmplen1,tmplen2;
	// add variable for new method
public:
	Hobject hanImageReduced,hanModelImages,hanModelRegions;
	Hobject RegionClosing1,RegionErosion,ImageReduced2,ImageMean,RegionDynThresh1;

	Hobject rect, rect1;
	HTuple  phi, phi1, Rows, Columns, Length, Length1;
	HTuple  Rows1, Columns1, len, len1;
	HTuple  centerRow, centerCol;
	HTuple  hWidth, hHeight, hWidth1, hHeight1;
	HTuple  testw,  testh;    
	Hobject errUnion, ImageResult;
	// ADD
	Hobject errCon;
	HTuple  errNum;

	// ADD FOR INCREATEMENT
	HTuple  pt1_row, pt1_col, pt1_phi, pt1_len1, pt1_len2;
	HTuple  pt2_row, pt2_col, pt2_phi, pt2_len1, pt2_len2;
	HTuple  pt3_row, pt3_col, pt3_phi, pt3_len1, pt3_len2;

	
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