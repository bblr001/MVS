/*#define TIXML_USE_STL*/

#pragma  once
#include "./tinxml/tinyxml.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include "string"
#include <list>
#include <map>
#include <vector>
#include <memory>
#include "windows.h"
#include "VLCtrl.h"

using namespace std;

typedef map<string,string> Property;

const unsigned int ARRAY_CAMERA      = 0;
const unsigned int LINE_SCANE_CAMERA = 1;

class CMConfigCenter;

struct STLSDATA_PARAMETER
{
	STLSDATA_PARAMETER():
      parameterName(""),
	  parameterDesc(""),
	  settingValue(""),
	  helpDesc("")
	{
	}
	string parameterName;
	string parameterDesc;
	string settingValue;
	string helpDesc;
	list<string> valueList;
	Property property_;
};

struct STLSDATA_SUBTEST
{
	STLSDATA_SUBTEST()
	{
		RunTest = "Yes";
		order = 999;
		ShowObject = false;
		m_strSubTestName = "";
		testName = "";
	}
	STLSDATA_SUBTEST(const STLSDATA_SUBTEST& other)
		:testName(other.testName),
		m_strSubTestName(other.m_strSubTestName),
		helpDesc(other.helpDesc),
		exeName(other.exeName),
		exeVersion(other.exeVersion),
		RunTest(other.RunTest),
		ShowObject(other.ShowObject),
		order(other.order)
	{
		property_ = other.property_;
		m_vParameters.assign(other.m_vParameters.begin(), other.m_vParameters.end());
	}
	STLSDATA_SUBTEST& operator=(const STLSDATA_SUBTEST& other)
	{
		if(this == &other) return *this;
		testName         = other.testName;
		m_strSubTestName = other.m_strSubTestName;
		helpDesc         = other.helpDesc;
		exeName			 = other.exeName;
		exeVersion       = other.exeVersion;
		RunTest          = other.RunTest;
		order            = other.order;

		property_.clear();
		m_vParameters.clear();
		property_     = other.property_;
		m_vParameters = other.m_vParameters;

		return *this;
	}

	~STLSDATA_SUBTEST()
	{
		property_.clear();
		m_vParameters.clear();
	}
	string testName;
	string m_strSubTestName;
	string helpDesc;
	string exeName;
	string exeVersion;
	string RunTest;
	bool ShowObject;
	Property property_;
	std::vector<STLSDATA_PARAMETER> m_vParameters;
	int order;

};

struct STLSDATA_TEST
{
	string testName;
	string helpDesc;
	Property property_;
};

struct CHANNEL_PARAMETER
{
	CHANNEL_PARAMETER():
      parameterName(""),
	  parameterDesc(""),
	  settingValue(""),
	  helpDesc(""),
	  channelIndex("-1")
	{
	}
	string parameterName;
	string parameterDesc;
	string settingValue;
	string helpDesc;
	list<string> valueList;
	Property property_;
	string channelIndex;
};

struct LightCtrlInfo
{
	int m_iaddress; // max value -- 2
	string m_lightCtrlName;
	Property property_;
	std::vector<CHANNEL_PARAMETER> m_vParameters;
	LightCtrlInfo():m_iaddress(0)
	{
		m_vParameters.clear();
	}

};

struct STLSDATA_COMMON
{
	string commname;
	Property property_;
};

enum EMDATA_TYPE
{
	NONE=-1,TEST=0, SUBTEST,COMMON
};

union ptrUnion
{
	STLSDATA_SUBTEST*       pDataSubtest;
	STLSDATA_TEST*		    pDataTest;
	STLSDATA_COMMON*		pDataCommon;
};

struct  sData
{
	ptrUnion  data;
	EMDATA_TYPE type;
	sData():type(NONE)
	{
		memset((void*)&data, 0x00, sizeof(ptrUnion));
	}
	sData(const sData& other)
	{
		Clone(other);
	}
	sData& operator=(const sData& other)
	{
		Cleanup();

		if(this == &other)
			return *this;
		Clone(other);
		return *this;
	}
	~sData()
	{
		Cleanup();
	}

private:
	void Clone(const sData& other)
	{
		this->type = other.type;
		if(type == SUBTEST) 
			data.pDataSubtest = new STLSDATA_SUBTEST(*other.data.pDataSubtest);
		if(type == TEST)
			data.pDataTest = new STLSDATA_TEST(*other.data.pDataTest);
		if(type == COMMON)
			data.pDataCommon = new STLSDATA_COMMON(*other.data.pDataCommon);
	}

	void Cleanup()
	{
		if(type == SUBTEST)
		{
			delete data.pDataSubtest;
			data.pDataSubtest = nullptr;
		}
		if(type == TEST)
		{
			delete data.pDataTest;
			data.pDataTest = nullptr;
	    }
		if(type == COMMON)
		{
			delete data.pDataCommon;
	        data.pDataCommon = nullptr;
	    }
	}
};

class CTlsData
{
public:
	 CTlsData()
	 {
		 m_data.type = NONE;
	 }
	 CTlsData(const CTlsData& other):m_data(other.m_data)
	 {
		 //m_data = other.m_data;
	 }
	CTlsData& operator= (const CTlsData& other)
	{
		if(this == &other) return *this;
		m_data = other.m_data;
		return *this;
	}
	~CTlsData(void);

	EMDATA_TYPE GetType() 
	{
		return m_data.type;
	}
	STLSDATA_SUBTEST*		GetDataSubtest();
	STLSDATA_TEST*		    GetDataTest();
	STLSDATA_COMMON*		GetDataCommon();

private:
	sData m_data;
};

class TlsFileParser
{
public:
	 TlsFileParser();
	~TlsFileParser();
	int Init(const char *filename);
	std::vector<CTlsData> *GetTestList() {return &m_vTestData;}
	void SaveTLS(string fileName);

protected:
	int SetTestList();
	int SetCommonInfo();
	int SetRoot();
	void ReleaseMem();
protected:
	TiXmlDocument m_Doc;
	TiXmlElement* m_pRootElement;
	TiXmlElement* m_pCommonElement;
	TiXmlElement *mTestInstanceElement;
protected:
	std::vector<CTlsData> m_vTestData;
	std::vector<LightCtrlInfo> m_vLightCtrlInfo;

	string errorMsg;
};

class CTestItemList
{
protected:

	TiXmlDocument m_Doc;
	TiXmlElement *m_pRootElement;
	TiXmlElement *m_pCommonElement;
public:
	std::vector<CTlsData>* m_lTestList;
	void SaveTLS(string fileName);
	bool OpenTLS(string fileName);
	void SetTestList(std::vector<CTlsData>* pSubTestItemList);
	std::vector<CTlsData>* GetTestList(){return m_lTestList;};
public:

};

enum EMDATA_SOURCE
{
	NONE_SOURCE=-1,SINGLE_IMG_FILE=0, IMG_FILES, CAMERA_SOURCE,
};

enum ETRIGGERACTIVATION
{
	RISING_EDGE=0,FALLING_EDGE,
};

struct CameraInfo
{
	CameraInfo()
		:m_sCameraName(""),
		 m_bTriggerMode(true),
		 m_triggerEdge(RISING_EDGE),
		 m_cameraType(ARRAY_CAMERA),
		 m_gain(0),
		 m_linesPerFrame(0),
		 m_framesPerSheet(0),
		 m_triggerDelayAbs(0)
	{
	}

	string m_sCameraName;
	bool m_bTriggerMode;
	ETRIGGERACTIVATION m_triggerEdge;
	unsigned int m_cameraType; // 0 : Array Camera; 1 : Line Scan Camera;
	unsigned int m_gain;
	unsigned int m_linesPerFrame;
	unsigned int m_framesPerSheet;
	unsigned int m_triggerDelayAbs;
};

struct AlarmPortInfo
{
	int m_Green;
	int m_Red;
	int m_Yellow;
	AlarmPortInfo()
		:m_Green(0),
		 m_Red(0),
		 m_Yellow(0)
	{
	}
};

struct RejectNGProductInfo
{
	bool m_bRejectMode;
	int m_sRejectPort;
	RejectNGProductInfo()
		:m_bRejectMode(true),
		 m_sRejectPort(0)
	{
	}
};

struct WindowSizeInfo
{
	int LogWindowWidth;
	int LogWindowHeight;
	int SourceWindowWidth;
	int SourceWindowHeight;
	WindowSizeInfo()
		:LogWindowWidth(512),
		LogWindowHeight(512),
		SourceWindowWidth(512),
		SourceWindowHeight(512)
	{
	}
};

struct IMAGE_SIZE
{
	int m_ImageWidth;
	int m_ImageHeight;

	IMAGE_SIZE():m_ImageHeight(512),m_ImageWidth(512)
	{

	}
};

class ProgramData
{
	friend CMConfigCenter;
private:
	CameraInfo           m_CameraInfo;
    RejectNGProductInfo  m_RejectInfo;
    AlarmPortInfo        m_AlarmInfo;

	string m_sProgramName;
	string m_sTLSFileName;
	EMDATA_SOURCE m_eSource;
	string m_sFilePath;
	string m_sFileName;
	bool m_bSaveERRImage;
	bool m_bSavePassImage;
	bool m_bConnect2LightCtrl;

public:
	ProgramData();
	~ProgramData();
	BOOL LoadProgram(wstring openFileName);
	void SaveProgramData();
public:
	std::vector<LightCtrlInfo> *GetLightCtrlList(){return &m_vLightCtrlInfo;};
protected:	
	void SetLightCtrlList(TiXmlElement* pLightCtrlElement);
	std::vector<LightCtrlInfo> m_vLightCtrlInfo;
private:
	void LoadCameraAndLightSetting(TiXmlElement* pRootElement);
	void LoadRejectUnitSetting(TiXmlElement* pRootElement);
	void LoadBasicSetting(TiXmlElement* pRootElement);
	void LoadImageSourceSetting(TiXmlElement* pRootElement);
	void LoadLightIntensitySetting(TiXmlElement* pRootElement);

	void SaveCameraAndLightSetting(TiXmlElement* pRootElement);
	void SaveRejectUnitSetting(TiXmlElement* pRootElement);
	void SaveBasicSetting(TiXmlElement* pRootElement);
	void SaveImageSourceSetting(TiXmlElement* pRootElement);
	void SaveLightIntensitySetting(TiXmlElement* pRootElement);

	void SetSampleImageSize();
};