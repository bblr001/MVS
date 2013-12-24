#pragma once
#include "ImageFilePump.h "
#include "BaslerCamera2.h"
#include "MData.h"

//接收中心，接收COM、Test、AAA信息
class CImageFilePump;
class CBaslerCamera;
class CMCtrlCenter;
class CMConfigCenter;

const int BUFF_SIZE  = sizeof(CMData);

#pragma warning(disable:4244)

class CMRecvCenter
{
public:	
	virtual ~CMRecvCenter(void);
public:
	BOOL Init();
	void RecvOneFrame();
	void UpdateSingleFrame();
	void TriggerCamera();
protected:
	void Start();
	void Pause();
	void Resume();
	void Stop();

protected:
	friend class CMCtrlCenter;
	CMRecvCenter(void);

public:
	CImageFilePump  m_imageFilePump;
	CBaslerCamera   m_recvBaslerCamera;
};
