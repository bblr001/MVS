#include "StdAfx.h"
#include "MRecvCenter.h"
#include "MCtrlCenter.h"
#include <new>

#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG

CMRecvCenter::CMRecvCenter(void)
{	
}

CMRecvCenter::~CMRecvCenter(void)
{
}

BOOL CMRecvCenter::Init()
{
	auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();
	if (pConfigCenter->GetImgSource() == IMG_FILES)
	{
		if (!m_imageFilePump.Init())
		{
			return FALSE;
		}
	}
	if (pConfigCenter->GetImgSource() == CAMERA_SOURCE)
	{
		if (!m_recvBaslerCamera.Init())
		{
			return FALSE;
		}

		if (!m_recvBaslerCamera.Open(pConfigCenter->GetCameraName()))
		{
			return FALSE;
		}
	}
	return TRUE;
}

void CMRecvCenter::Start()
{
	auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();
	if (pConfigCenter->GetImgSource() == IMG_FILES)
	{
		m_imageFilePump.Run();
	}
	if (pConfigCenter->GetImgSource() == CAMERA_SOURCE)
	{
		m_recvBaslerCamera.Run();
	}

	if (pConfigCenter->GetImgSource() == SINGLE_IMG_FILE)
	{
		this->RecvOneFrame();
	}
}

void CMRecvCenter::Stop()
{
	auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();
	if (pConfigCenter->GetImgSource() == CAMERA_SOURCE )
	{
		m_recvBaslerCamera.Stop();
	}
	if (pConfigCenter->GetImgSource() == IMG_FILES)
	{
		m_imageFilePump.Stop();
	}
}

void CMRecvCenter::Pause()
{
	auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();
	if (pConfigCenter->GetImgSource() == IMG_FILES)
	{
		m_imageFilePump.Pause();
	}
	if (pConfigCenter->GetImgSource() == CAMERA_SOURCE)
	{
		m_recvBaslerCamera.Pause();
	}
}

void CMRecvCenter::Resume()
{
	auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();
	if (pConfigCenter->GetImgSource() == IMG_FILES)
	{
		m_imageFilePump.Resume();
	}
	if (pConfigCenter->GetImgSource() == CAMERA_SOURCE)
	{
		m_recvBaslerCamera.Resume();
	}

	if (pConfigCenter->GetImgSource() == SINGLE_IMG_FILE)
	{
		RecvOneFrame();
	}
}

void CMRecvCenter::RecvOneFrame()
{
	Hobject tmpImage;
	auto pConfig = CMConfigCenter::GetSingletonConfigCenter();

	if (pConfig->GetImgSource() == IMG_FILES)
	{
		m_imageFilePump.RetrieveCurrentImage(&tmpImage);
	}
	if (pConfig->GetImgSource() == CAMERA_SOURCE)
	{
		m_recvBaslerCamera.RetrieveCurrentImage(&tmpImage);
	}
	CMData data;
	count_seconds(&data.m_reciveStartTime);

	if (pConfig->GetImgSource() == SINGLE_IMG_FILE)
	{
		string fileName = pConfig->GetRecvFileName();
		read_image(&tmpImage,fileName.c_str());
	}
	data.m_Image = tmpImage;
	data.m_reciveCount = 1;
	data.m_isDebug = true;
	data.m_ShowHWindow = pConfig->GetShowWindowHID();
	count_seconds(&data.m_reciveEndTime);
	disp_obj(data.m_Image,pConfig->GetShowWindowHID());
	
	auto pCtrlCenter = CMCtrlCenter::GetSingletonCtrlCenter();
	if(pCtrlCenter->m_r_buffer_f.is_not_full())
	{
		pCtrlCenter->m_r_buffer_f.push_front(data);
	}
}

void CMRecvCenter::TriggerCamera()
{
	if (CMConfigCenter::GetSingletonConfigCenter()->GetImgSource()== CAMERA_SOURCE)
	{
		m_recvBaslerCamera.GenSoftTrigger();
	}
}

void CMRecvCenter::UpdateSingleFrame()
{
	auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();
	if (pConfigCenter->GetImgSource() == CAMERA_SOURCE)
	{
		m_recvBaslerCamera.UpdateSingleFrame();
	}
	if (pConfigCenter->GetImgSource() == IMG_FILES)
	{
		m_imageFilePump.UpdateSingleFrame();
	}
}
