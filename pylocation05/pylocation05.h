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
		rect01_col_offset = 150;
		rect07_col_offset = 2050;
		rect04_col_offset = 3600;
	};

protected:

public:
	int rect01_col_offset, rect07_col_offset, rect04_col_offset;
};

struct PNT
{
	double m_row;
	double m_col;
	PNT()
	  :m_row(0.0),
	   m_col(0.0)
	{
	}
	PNT(double row, double col)
		:m_row(row),
		 m_col(col)
	{
	}
	PNT(const PNT& other)
	{
		m_row = other.m_row;
		m_col = other.m_col;
	}
	PNT& operator=(const PNT& other)
	{
		if(this == &other)
			return *this;
		m_row = other.m_row;
		m_col = other.m_col;
		return *this;
	}
};

struct WeldRegion
{
	PNT lt;
	PNT rt;
	PNT rb;
	PNT lb;
	WeldRegion()
	{
	}
	WeldRegion(const WeldRegion& other)
	{
		lt = other.lt;
		rt = other.rt;
		rb = other.rb;
		lb = other.lb;
	}
	WeldRegion& operator=(const WeldRegion& other)
	{
		if(this == &other)
			return *this;
		lt = other.lt;
		rt = other.rt;
		rb = other.rb;
		lb = other.lb;
		return *this;
	}
};

class CDoProcess
{
private:
	CParameter m_Parameters;
	enum IListValueA m_ListReg;
	int ch;

	WeldRegion myCalPoint;
public:
	CDoProcess();
	void AutoConfig();
	void SetParmeter(string name, string value);

	void DoProcess(CMData* pData, SubTestResult *testItem);

private:
	bool    LocateWeldingLine(int nWeldColHint, WeldRegion& rgnPnts, Hlong hDispWnd);
	Hobject m_currentImage;
	double  CalculateEdgeRow(Hobject& targetRect, bool bFirstFrame, bool bLastFrame);
	double  CalculateBeginColumn();
	double  CalculateBeginRowLeft(double& LeftCol);
	double  CalculateBeginRowRight(double& RightCol);
	WeldRegion ShufflePoints(double bgnRow, double endRow, PNT pt1, PNT pt2, PNT pt3, PNT pt4);
	void GenerateWeldRegion(const WeldRegion& rgnPnts,CMData* pData, int weldIndex, Hlong hDispWnd);
	void GenerateCanBodyRegion(const WeldRegion& leftWeldPnts, const WeldRegion& rightWeldPnts,Hobject& canBodyRgn,Hlong hDispWnd);
	void CalculateCenterWeldRegion(const WeldRegion& leftWeldPnts, const WeldRegion& rightWeldPnts, CMData* pData, int weldIndex, Hlong hDispWnd, WeldRegion& retRgn);

	double CalculateLastFrameRowLeft(double& LeftCol);   // compute last frame row left 
	double CalculateLastFrameRowRight(double& RightCol);  // compute last frame row right
	bool   CalculateLocationBlockCenter(Hobject& src, Hobject& srcRegion, int &estimateCol);
private:
	double m_bgnCol;
	double m_dBeginRowLeft;
	double m_dBeginRowRight;
	HTuple m_imgWidth, m_imgHeight;
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

