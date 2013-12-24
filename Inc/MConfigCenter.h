#pragma once

#include <string>
#include <set>
#include "MData.h"
#include <list>
#include "TlsFileParser.h"
#include "Tools.h"
#include "TypeCent.h"
#include <memory>
using namespace std;

extern CRITICAL_SECTION g_critical_section;

class CMConfigCenter
{
public:
	virtual ~CMConfigCenter(void);
	static CMConfigCenter* GetSingletonConfigCenter()
	{
		EnterCriticalSection(&g_critical_section);
		if(m_pSingletonConfigCenter == nullptr)
		{
			m_pSingletonConfigCenter.reset(new CMConfigCenter);
		}
		LeaveCriticalSection(&g_critical_section);
		return m_pSingletonConfigCenter.get();
	}

protected:
	friend class CMCtrlCenter;
	CMConfigCenter(void);
private:
	wstring m_sLocalPath; //程式所在路径
	wstring m_sTestProgramPath; // 检测程式所在路径. 默认是在D:\\SLACTST 如果需要自己定义的话可以在 host.ini文件夹中定义.
	//UI Display Window
	Hlong m_uiWinodwID; //主界面显示窗口的 wnd
	Hlong m_logWindowID; //错误显示窗口的 wnd

	ProgramData	m_ProgramData; // 程式解析出的数据. process.cfg 文件内的信息
	wstring m_sRecvFileSearchPath; //查询的文件夹名.
	std::vector<CTlsData>*  m_pTestItemList; //当前的检测项目list

private:
	eUSER_GROUP m_UserGroup;
	bool m_bDebugFlag;
	bool m_bHasFrame;
	bool m_bProgramChanged;
	bool m_errorImgPaused;
	CRect m_Rect;
	CRect m_dispRect;

	int m_ErrorFileCount;
	eMTI_GUI_STATE m_States;
	int m_TimeInterval;
	Hlong m_ShowWindowHID_Halcon;
	Hlong m_LogWindowHID_Halcon;
	IMAGE_SIZE m_ImageSize;
	IMAGE_SIZE m_demoImgSize;

	int m_nAlarmThreshold;
	int m_nTimeInterval;
	int m_EncoderDelaySingleCounts;

	Hobject m_LogWindowImage;
	Hobject m_roi;
public:
	void SetRoiOfCurrentImage(Hobject roi)
	{
		m_roi = roi;
	}
	Hobject GetRoiOfCurrentImage()
	{
		return m_roi;
	}

	void SetDispRect(CRect rect)
	{
		m_dispRect = rect;
	}
	CRect GetDispRect()
	{
		return m_dispRect;
	}
	Hobject GetLogWindowImage(){return m_LogWindowImage;};
	void SetLogWindowImage(Hobject st){m_LogWindowImage=st;};
	BOOL LoadProgramConfig(wstring program){return m_ProgramData.LoadProgram(program);} //给需要解析的程式名. 自动解析process.cfg文件.
	
	void SetTestItemList(std::vector<CTlsData>* itemList){m_pTestItemList = itemList;}; //检测程式参数的list文件
	std::vector<CTlsData>* GetTestItemList(){return m_pTestItemList;}; // 使用及写入时需要用此功能

	void SetTLSFileName(string tlsFileName){m_ProgramData.m_sTLSFileName = tlsFileName;};
	string GetTLSFileName(){return m_ProgramData.m_sTLSFileName;};

	CRect* GetUISize() {return &m_Rect;};

	std::vector<LightCtrlInfo>* GetLightCtrlInfosPtr()
	{
		if(m_ProgramData.m_vLightCtrlInfo.empty())
			return nullptr;

		return &m_ProgramData.m_vLightCtrlInfo;
	}

	IMAGE_SIZE GetImageSize()
	{
		return m_ImageSize;
	}
	void SetImageSize(int sw,int sh)
	{
		m_ImageSize.m_ImageHeight = sh;
		m_ImageSize.m_ImageWidth=sw;
	}

	IMAGE_SIZE GetDemoImgSize()
	{
		return m_demoImgSize;
	}

	void SetDemoImgSize(int w, int h)
	{
		m_demoImgSize.m_ImageWidth = w;
		m_demoImgSize.m_ImageHeight = h;
	}

	bool GetProgramChangedFlag() {return m_bProgramChanged;}
	void SetProgramChangedFlag(bool flag) { m_bProgramChanged = flag;}

	Hlong GetUIWindowID(){return m_uiWinodwID;};
	void SetUIWindowID(Hlong id){m_uiWinodwID = id;};
	void SetShowWindowHID(Hlong ShowWindowHID){m_ShowWindowHID_Halcon = ShowWindowHID;};
	Hlong GetShowWindowHID(){return m_ShowWindowHID_Halcon;};

	Hlong GetLogUIWindowID(){return m_logWindowID;}; //取主界面显示的Wnd ID
	void SetLogUIWindowID(Hlong id){m_logWindowID = id;};  //设定主界面显示的Wnd ID
	void SetLogWindowHID(Hlong LogWindowHID){m_LogWindowHID_Halcon = LogWindowHID;};  //设定错误显示界面的Halcon Wnd ID
	Hlong GetLogWindowHID(){return m_LogWindowHID_Halcon;}; //取错误显示界面显示的Halcon Wnd ID

	string GetProgramName(){return m_ProgramData.m_sProgramName;}; //取检测程式的名

	void SetImgSource(EMDATA_SOURCE ss){m_ProgramData.m_eSource=ss;}; // 设定检测的图像原
	EMDATA_SOURCE GetImgSource(){return m_ProgramData.m_eSource;}; // 获取当前设定的检测图像源

	void SetCameraName(string CameraName){m_ProgramData.m_CameraInfo.m_sCameraName = CameraName;}; //设定相机名
	string GetCameraName(){return m_ProgramData.m_CameraInfo.m_sCameraName;}; // 取相机名

	bool GetTriggerMode(){return m_ProgramData.m_CameraInfo.m_bTriggerMode;}; //取相机触发模式
	void SetTriggerMode(bool mode){ m_ProgramData.m_CameraInfo.m_bTriggerMode = mode;}; //设定相机触发模式. 开或关

	bool GetConnect2LightCtrlFlag() {return m_ProgramData.m_bConnect2LightCtrl;}
	void SetConnect2LightCtrlFlag(bool flag) { m_ProgramData.m_bConnect2LightCtrl = flag;}

	ETRIGGERACTIVATION GetTriggerEdge(){return m_ProgramData.m_CameraInfo.m_triggerEdge;};
	void SetTriggerEdge(ETRIGGERACTIVATION edge){m_ProgramData.m_CameraInfo.m_triggerEdge = edge;}; //设定相机触发方式的上升沿或下降沿

	bool GetRejectMode(){return m_ProgramData.m_RejectInfo.m_bRejectMode;};  //取是否要排盖
	void SetRejectMode(bool mod){m_ProgramData.m_RejectInfo.m_bRejectMode=mod;}; //设定排盖的使能开关 true 是排

	int GetRejectPort(){return m_ProgramData.m_RejectInfo.m_sRejectPort;}; //取程式排盖端口
	void SetRejectPort(int port ){m_ProgramData.m_RejectInfo.m_sRejectPort = port;}; //设定程式排盖端口

	bool GetSaveFailImageStatus(){return m_ProgramData.m_bSaveERRImage;}; //判断是否要保存Fail的图片
	void SetSaveFailImageStatus(bool bStatus){m_ProgramData.m_bSaveERRImage = bStatus;};

	bool GetSavePassImageStatus(){return m_ProgramData.m_bSavePassImage;}; //判断是否要保存PASS的图片
	void SetSavePassImageStatus(bool bStatus){m_ProgramData.m_bSavePassImage = bStatus;};

	void SetRecvFilesPath(string path){m_ProgramData.m_sFilePath = path;};  //设定从文件夹读图片时的文件夹路径
	string GetRecvFilesPath(){return m_ProgramData.m_sFilePath;}; //取从文件夹读图片时的文件夹路径

	void SaveProgramData(){m_ProgramData.SaveProgramData();}; //保存程式. 主界面上的Save.

	int GetGPort(){return m_ProgramData.m_AlarmInfo.m_Green;};
	int GetRPort(){return m_ProgramData.m_AlarmInfo.m_Red;};
	int GetYPort(){return m_ProgramData.m_AlarmInfo.m_Yellow;};

	void SetGPort(int p){m_ProgramData.m_AlarmInfo.m_Green=p;};
	void SetRPort(int p){m_ProgramData.m_AlarmInfo.m_Red=p;};
	void SetYPort(int p){m_ProgramData.m_AlarmInfo.m_Yellow=p;};
	void SetRecvFileName(string name){m_ProgramData.m_sFileName = name;}; //设定读取文件的文件名
	string GetRecvFileName(){return m_ProgramData.m_sFileName;}; //得到读取文件的文件名

	unsigned int GetCameraGain(){return m_ProgramData.m_CameraInfo.m_gain;};
	void SetCameraGain(unsigned int gain){m_ProgramData.m_CameraInfo.m_gain = gain;};

	unsigned int GetTriggerDelayAbs(){return m_ProgramData.m_CameraInfo.m_triggerDelayAbs ;};
	void SetTriggerDelayAbs(unsigned int triggerDelayAbs){m_ProgramData.m_CameraInfo.m_triggerDelayAbs=triggerDelayAbs ;};

	unsigned int GetCameraType()
	{
		return m_ProgramData.m_CameraInfo.m_cameraType;
	}
	void SetCameraType(unsigned int type)
	{
		m_ProgramData.m_CameraInfo.m_cameraType = type;
	}
	unsigned int GetLineCountPerFrame()
	{
		return m_ProgramData.m_CameraInfo.m_linesPerFrame;
	}
	void SetLineCountPerFrame(unsigned int linePerFrame)
	{
		m_ProgramData.m_CameraInfo.m_linesPerFrame = linePerFrame;
	}
	unsigned int GetFrameCountPerSheet()
	{
		return m_ProgramData.m_CameraInfo.m_framesPerSheet;
	}
	void SetFrameCountPerSheet(unsigned int framePerSheet)
	{
		m_ProgramData.m_CameraInfo.m_framesPerSheet = framePerSheet;
	}
	wstring GetLocalPath(){return m_sLocalPath;}; //当前程式所有的路径
	wstring GetTestProgramPath(){return m_sTestProgramPath;};

	void SetDebugModeFlag(bool mod){m_bDebugFlag = mod;};
	bool GetDebugModeFlag(){return m_bDebugFlag;};

	void SetHasFrameFlag(bool mod){m_bHasFrame = mod;};
	bool GetHasFrameFlag(){return m_bHasFrame;};

	void SetUserGroup(eUSER_GROUP UserGroup){m_UserGroup = UserGroup;};
	eUSER_GROUP GetUserGroup(){return m_UserGroup;};

	void SetReciveFilesTimeInterval(int m){m_TimeInterval = m;};
	int GetReciveFilesTimeInterval() {return m_TimeInterval;};

	int GetAlarmThreshold(){return m_nAlarmThreshold;};
	void SetAlarmThreshold(int count){m_nAlarmThreshold=count;};

	int GetEncoderDelaySingleCounts(){return m_EncoderDelaySingleCounts;};
	void SetEncoderDelaySingleCounts(int val){ m_EncoderDelaySingleCounts=val;};

	int GetTimeInterval()
	{
		return m_nTimeInterval;
	}
	void SetTimeInterval(int timeInterval)
	{
		m_nTimeInterval = timeInterval;
	}

	bool GetErrorImgPausedFlag()
	{
		return m_errorImgPaused;
	}

	void SetErrorImgPausedFlag(bool flag)
	{
		m_errorImgPaused = flag;
	}

	void UpdateDispWindowSetting(Hobject& image, Hlong& showWindowHID)
	{
		clear_window(showWindowHID);
		HTuple width, height;
		get_image_size(image, &width, &height);
		set_part(showWindowHID, 0, 0, height-1, width-1);
		
		SetImageSize(width[0].I(),height[0].I());
		set_part(m_LogWindowHID_Halcon,0,0,height-1, width-1);
	}
	private:
		static std::shared_ptr<CMConfigCenter> m_pSingletonConfigCenter;
};
