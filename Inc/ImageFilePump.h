#pragma once
#include "IMActiveObj.h"
#include "MData.h"
#include "MConfigCenter.h"
using namespace std;

class CMRecvCenter;
class CImageFilePump :public IMActiveObj
{
public:
	CImageFilePump(void);
	~CImageFilePump(void);

	BOOL Init();
	void SetRecvFileSearchPath(const char* filePath);
	virtual void Pause()
	{
		IMActiveObj::Pause();
	}
	virtual void Resume()
	{
		m_recvCount=0;
		m_iNCounter=0;
		m_bDebugMode = CMConfigCenter::GetSingletonConfigCenter()->GetDebugModeFlag();
		IMActiveObj::Resume();
	}
	void Stop();
	void UpdateSingleFrame() 
	{
		if (m_bHasFrame)
			CMConfigCenter::GetSingletonConfigCenter()->SetHasFrameFlag(true);
		else
			CMConfigCenter::GetSingletonConfigCenter()->SetHasFrameFlag(false);
		m_bDebugMode = CMConfigCenter::GetSingletonConfigCenter()->GetDebugModeFlag();
	}
	void RetrieveCurrentImage(Hobject *image)
	{
		if (m_bHasFrame)
		{
			CMConfigCenter::GetSingletonConfigCenter()->SetHasFrameFlag(true);
		}
		else
			CMConfigCenter::GetSingletonConfigCenter()->SetHasFrameFlag(false);
		*image = m_currentImg;
	};
protected:
	virtual UINT Main();
private:
	void Reset(CMData* pData)
	{
		pData->m_center_x = 0;
		pData->m_center_y = 0;
		pData->r_real     = 0;
#ifdef SHEET_INSPECTION
		pData->m_errorRgns.clear();
#endif
	}
	Hlong m_recvCount;
	Hobject m_currentImg;
	int   m_TimeInterval;
	bool  m_bHasFrame;
	bool  m_bDebugMode;
	bool  m_isExit;
	CString m_strFilePath;
	int m_iNCounter;
	HANDLE m_hSyncEvent;
	// only for Line Scan Camera. Project #8126
	Hobject m_topHalfImg;
	bool m_bFirstImage;
};
