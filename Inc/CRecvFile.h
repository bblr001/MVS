#pragma once
#include "IMActiveObj.h"
#include "MData.h"
#include "IMRecv.h"
#include "MConfigCenter.h"
using namespace std;

class CMRecvCenter;
class CMRecvFile :public IMActiveObj,public IMRecv
{
public:
	CMRecvFile(void);
	~CMRecvFile(void);

	BOOL Init();
	void SetRecvFileSearchPath(const char* filePath);
	void Stop();

	void UpdateSingleFrame() 
	{
		if (m_bHasFrame)
			CMConfigCenter::GetConfigCenter().SetHasFrame(true);
		else
			CMConfigCenter::GetConfigCenter().SetHasFrame(false);
		m_SingleFrame = CMConfigCenter::GetConfigCenter().GetSingleFrameModel();
	}

	void SaveFrameToFile(Hobject *image)
	{

		if (m_bHasFrame)
		{
			CMConfigCenter::GetConfigCenter().SetHasFrame(true);
		}
		else
			CMConfigCenter::GetConfigCenter().SetHasFrame(false);
		*image = m_CurrentFrame;
	};

protected:
	virtual UINT Main();
private:
	void RecvData();
	bool m_PreProcess(CMData* pData);
	Hlong	ReciveCount;
	int m_TimeInterval;
	bool m_bHasFrame;
	bool m_SingleFrame;
	bool m_ReciveFrame;

	Hobject m_CurrentFrame;

private:
	bool m_isExit;
	CString m_strFilePath;
	CString m_strSearchPath;

	CRITICAL_SECTION*    m_pReciveDataMutex;
};
