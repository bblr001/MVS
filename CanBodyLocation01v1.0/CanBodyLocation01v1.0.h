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
		Col1  = 600;
		Col2  = 1300;
		Col3  = 2000;
		Col4  = 2700;
		Col5  = 3460;
	};
protected:
public:
	int Col1, Col2, Col3, Col4, Col5;
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
	Hobject Rect01, Rect07, Rect02, Rect06;
	Hobject Rect03, Rect05, Rect04;

	double Rect01_row, Rect01_col, Rect01_phi, Rect01_len1, Rect01_len2;
	double Rect07_row, Rect07_col, Rect07_phi, Rect07_len1, Rect07_len2;
	double Rect02_row, Rect02_col, Rect02_phi, Rect02_len1, Rect02_len2;
	double Rect06_row, Rect06_col, Rect06_phi, Rect06_len1, Rect06_len2;
	double Rect03_row, Rect03_col, Rect03_phi, Rect03_len1, Rect03_len2;
	double Rect05_row, Rect05_col, Rect05_phi, Rect05_len1, Rect05_len2;
	double Rect04_row, Rect04_col, Rect04_phi, Rect04_len1, Rect04_len2;

	double Can1_Row, Can1_Col, Can1_Phi, Can1_Len1, Can1_Len2;
	double Can2_Row, Can2_Col, Can2_Phi, Can2_Len1, Can2_Len2;

	Hobject LocationCan1, LocationCan2;
	Hobject Can1Body, Can2Body;

	HTuple absPhi;
	HTuple tmpCan1_row, tmpCan1_col, tmpCan1_phi, tmpCan1_len1, tmpCan1_len2;
	HTuple tmpCan2_row, tmpCan2_col, tmpCan2_phi, tmpCan2_len1, tmpCan2_len2;
	Hobject tmpCan1, tmpCan2;
	HTuple  Can1_phi, Can2_phi;
	HTuple  sinn, coss;

	HTuple len1, len2, row, col;
	const int Row1;
	const int Row2;
	const int Row3;
	const int Len1;
	const int Len2;
private:
	void PreProcess();
private:
	void GenLocationBlock(Hobject& locationBlock, int row, int col, int len1, int len2, CMData* pData);
	void ComputeWeldingLineCenter(Hobject& Image, Hobject& Region, double& row, double& col, double& phi);
	bool ComputeCanBody(Hobject& image, Hobject& locationCan, double& len1, double& len2, Hobject& canBody);
	void ComputeHorizonSeam(Hobject& image, Hobject& canbody, Hobject& upperHorizonSeam, Hobject& lowerHorizonSeam, CMData* pData);
	///// judge current frame position
	void LocationFramePostion(Hobject& image, Hobject& locationBlockUp, Hobject& locationBlockDown, double& weldingLineRow, double& weldingLineRow1, bool& isFirstFrame, bool& isLastFrame, CMData* pData);
	void ComputeVerticalSeam(Hobject& image, Hobject& canbody, Hobject& leftVerticalSeam, Hobject& rightVerticalSeam, CMData* pData);
	/////
	void ComputeVerticalSeamV2(Hobject& image, Hobject& canbody, Hobject& leftVerticalSeam, Hobject& rightVerticalSeam, Hlong& wHandle);
	///// return canbody
	bool GetCanBody(Hobject& srcCanBody, Hobject& dstCanBody);
	///// return vertical seam
	void GetVerticalSeam(Hobject& verticalSeam,  HTuple& row, HTuple& col, HTuple& phi, HTuple& len1, HTuple& len2);
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