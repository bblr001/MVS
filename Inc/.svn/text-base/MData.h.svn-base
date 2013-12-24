#pragma once

#include "cpp/HalconCpp.h"
#include "TypeCent.h"
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <atlstr.h>
using namespace std;
using namespace Halcon;
//#define ENGLISH_VERSION

#define  MAX_CHANGE_COUNT 30
//#define  PI 3.1415926
struct SubTestResult
{
	SubTestResult()
		:m_bFailSubTest(false),
	     m_ErrorX(0),
		 m_ErrorY(0),
		 m_ErrorR(0) 
	{
	}
	SubTestResult(const SubTestResult& other)
	{
		m_bFailSubTest   = other.m_bFailSubTest;
		m_ErrorX         = other.m_ErrorX;
		m_ErrorR         = other.m_ErrorR;
		m_ErrorY         = other.m_ErrorY;
	}

	SubTestResult& operator=(const SubTestResult& other)
	{
		if(this == &other) return *this;
		m_bFailSubTest   = other.m_bFailSubTest;
		m_ErrorX         = other.m_ErrorX;
		m_ErrorR         = other.m_ErrorR;
		m_ErrorY         = other.m_ErrorY;

		return *this;
	}
	SubTestResult(SubTestResult&& other)
	{
		m_bFailSubTest   = other.m_bFailSubTest;
		m_ErrorX         = other.m_ErrorX;
		m_ErrorR         = other.m_ErrorR;
		m_ErrorY         = other.m_ErrorY;
	}
	SubTestResult& operator=(SubTestResult&& other)
	{
		if(this == &other) return *this;
		m_bFailSubTest   = other.m_bFailSubTest;
		m_ErrorX         = other.m_ErrorX;
		m_ErrorR         = other.m_ErrorR;
		m_ErrorY         = other.m_ErrorY;
		return *this;
	}

	bool m_bFailSubTest;
	Hlong	m_ErrorX;
	Hlong	m_ErrorY;
	Hlong	m_ErrorR;
	

	void ResetFailFlag()
	{
		m_bFailSubTest = false;
	}
};

class CMData
{
public:
	CMData():
	m_reciveCount(0),
	m_ShowHWindow(0),
	m_orientationPhi(0.0),
	m_center_x(0.0),
	m_center_y(0.0),
	r_real(0.0),
	m_center_x2(0.0),
	m_center_y2(0.0),
	r_real2(0.0),
	m_orientationPhi3(0.0),
	m_center_x3(0.0),
	m_center_y3(0.0),
	m_isFail(false),
	m_isDebug(false)
	{
		m_vSubTestResult.reserve(32);
		gen_empty_obj(&m_ErrorRegist); // ADD FOR INITIALLIZATION OBJECT
#ifdef SHEET_INSPECTION
		m_errorRgns.reserve(64);
		//m_errorRgns.clear();

		m_vseam1_len1  = 0.0;  
		m_vseam1_len2  = 0.0;
	 
		m_vseam7_len1  = 0.0; 
		m_vseam7_len2  = 0.0;
	 
		m_vseam4_len1  = 0.0;
		m_vseam4_len2  = 0.0;
#endif
	}
	~CMData()
	{
		m_vSubTestResult.clear();
		
#ifdef SHEET_INSPECTION
		m_errorRgns.clear();
#endif
	}
	CMData(const CMData& other)
	{
		copyMembers(other);
	}

	CMData& operator=(const CMData& other)
	{
		if(this == &other) return *this;
		copyMembers(other);
		return *this;
	}
	// move constructor and assign operator
	CMData(CMData&& other)
	{
		copyMembers(other);
	}

	CMData& operator=(CMData&& other)
	{
		if(this == &other) return *this;
		copyMembers(other);

		return *this;
	}
	void ResetFailFlag()
	{
		m_isFail = false;
	}
public:
	bool    m_isFail;
	bool    m_isDebug;
	Hlong	m_reciveCount;
	Hlong   m_ShowHWindow;

	double	m_orientationPhi;
	double  m_center_x;
	double  m_center_y;
	double  r_real;

	double  m_center_x2;
	double  m_center_y2;
	double  r_real2;

	double	m_orientationPhi3;
	double  m_center_x3;
	double  m_center_y3;

	Hobject  m_Image;
	Hobject  m_ErrorRegist;

	Hobject  m_TestRegist1;
	Hobject  m_TestRegist2;

	HTuple   m_reciveStartTime;
	HTuple   m_reciveEndTime;
	HTuple   m_processStartTime;
	HTuple   m_processEndTime;
	HTuple	 m_displayStartTime;
	HTuple   m_displayEndTime;
	std::vector<SubTestResult> m_vSubTestResult;
#ifdef SHEET_INSPECTION
	std::vector<ERROR_RGN_INFO> m_errorRgns;

	double  m_vseam1_len1;  // hanfeng1 half width
	double  m_vseam1_len2;  // hanfeng1 half height
	 
	double  m_vseam7_len1;  // hanfeng2 half width
	double  m_vseam7_len2;  // hanfeng2 half height
	 
	double  m_vseam4_len1;  // hanfeng3 half width
	double  m_vseam4_len2;  // hanfeng3 half height

#endif


private:
	void copyMembers(const CMData& other)
	{
		m_isFail   = other.m_isFail;
		m_isDebug  = other.m_isDebug;
		m_orientationPhi = other.m_orientationPhi;
	
		m_center_x = other.m_center_x;
		m_center_y = other.m_center_y;
		r_real     = other.r_real;

		m_center_x2 = other.m_center_x2;
		m_center_y2 = other.m_center_y2;
		r_real2     = other.r_real2;

		m_orientationPhi3 = other.m_orientationPhi3;
		m_center_x3 = other.m_center_x3;
		m_center_y3 = other.m_center_y3;

		m_Image           = other.m_Image;
		m_ErrorRegist     = other.m_ErrorRegist;

		m_TestRegist1     = other.m_TestRegist1;
		m_TestRegist2     = other.m_TestRegist2;


		m_reciveStartTime = other.m_reciveStartTime;
		m_reciveEndTime   = other.m_reciveEndTime;

		m_processStartTime = other.m_processStartTime;
		m_processEndTime   = other.m_processEndTime;

		m_displayStartTime = other.m_displayStartTime;
		m_displayEndTime   = other.m_displayEndTime;

		m_reciveCount    = other.m_reciveCount;
		m_ShowHWindow    = other.m_ShowHWindow;
		if(!other.m_vSubTestResult.empty())
		{
			m_vSubTestResult.assign(other.m_vSubTestResult.begin(), other.m_vSubTestResult.end());
		}

#ifdef SHEET_INSPECTION
		if(!other.m_errorRgns.empty())
		{
			m_errorRgns.assign(other.m_errorRgns.begin(), other.m_errorRgns.end());
		}

		m_vseam1_len1  = other.m_vseam1_len1;
		m_vseam1_len2  = other.m_vseam1_len2;

		m_vseam7_len1  = other.m_vseam7_len1;
		m_vseam7_len2  = other.m_vseam7_len2;

		m_vseam4_len1  = other.m_vseam4_len1;
		m_vseam4_len2  = other.m_vseam4_len2;
#endif
	}
};
typedef void (* DllDoProcess )(int index,CMData* pData,SubTestResult *testItem);

typedef void (* DLLSetParameter)(int ch,string name,string value);

typedef void (* DLLAutoConfig)(string name);

struct STDoProcess
{
	DllDoProcess process;
	int order;
	CString m_dllName;
	HMODULE m_hDllHandle;
	DLLSetParameter parameter;
};

struct STSetParameter
{
	DLLSetParameter parameter;
	int order;
};