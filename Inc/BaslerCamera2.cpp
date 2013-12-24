#pragma once

#include "stdafx.h"
// Include files to use the PYLON API
#include <pylon/PylonIncludes.h>
#include <stdlib.h>
#include "BaslerCamera2.h"
#include "CameraConfiguration.h"

#include "..\Inc\MData.h"
#include "MCtrlCenter.h"
#include "MConfigCenter.h"
#include "AOIEditVer3.h"
#include "TLog.h"

#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG

using namespace Pylon;

#include <pylon/gige/BaslerGigEInstantCamera.h>
typedef Pylon::CBaslerGigEInstantCamera Camera_t;
using namespace Basler_GigECameraParams;

// Namespace for using cout
using namespace std;

CBaslerCamera::CBaslerCamera():m_pCameraNodeMap(nullptr)
{
	m_ixCamera = -1;
	m_rcvCount = 0;	
	m_bHasFrame = false;
	m_bColorCamera = false;
	m_camera.RegisterConfiguration(new CSoftwareTriggerConfiguration, RegistrationMode_ReplaceAll, Ownership_TakeOwnership);
	m_camera.RegisterConfiguration(new CAcquireContinuousConfiguration, RegistrationMode_ReplaceAll, Ownership_TakeOwnership);
	m_camera.RegisterConfiguration( new CameraConfiguration, RegistrationMode_Append, Ownership_TakeOwnership);
	//// In order the Device Removal Callback to work well for GigE cameras, you should Start the application
	//// Without Debugging, i.e. Ctrl+F5.
	//// If you started the application with the debugger being enabled, i.e. F5, the Device Removal Callback
	//// will detect a disconnected GigE camera after 5 minutes due to the HeartBeat Timeout being automatically 
	//// set to 5 minutes by the debugger.
	m_camera.RegisterConfiguration( this, RegistrationMode_Append, Ownership_ExternalOwnership);
	m_camera.RegisterImageEventHandler( this, RegistrationMode_Append, Ownership_ExternalOwnership);
	m_bArrayCamera = true;
	m_nCounter = 0;
	m_nFrameCount = 8;
	m_bFisrtImage = true;
}

CBaslerCamera::~CBaslerCamera()
{
}

bool CBaslerCamera::Init()
{
	if(m_camera.IsOpen())
	{
		return true;
	}
	Pylon::PylonAutoInitTerm autoInitTerm;
	m_rcvCount = 0;
	return true;
}


bool CBaslerCamera::OpenArrayCamera(string CameraName)
{
	using namespace GenApi;
	// Get the parameters for setting the image area of interest (Image AOI).
	const CIntegerPtr width = m_pCameraNodeMap->GetNode("Width");
	const CIntegerPtr height = m_pCameraNodeMap->GetNode("Height");
	const CIntegerPtr offsetX = m_pCameraNodeMap->GetNode("OffsetX");
	const CIntegerPtr offsetY = m_pCameraNodeMap->GetNode("OffsetY");

	CEnumerationPtr ptrPixelFormat = m_pCameraNodeMap->GetNode ("PixelFormat");
 	if (17301505 == ptrPixelFormat->GetIntValue()) //对应的是 PixelFormat_Mono8 灰度
 	{
 		m_bColorCamera = false; //
 	}
	else if (17301515 == ptrPixelFormat->GetIntValue() )//对应的是 PixelFormat_Mono8 彩色
	{
		m_bColorCamera = true; //
	}
 	if (CMConfigCenter::GetSingletonConfigCenter()->GetTriggerMode())
 	{
		CEnumerationPtr  ptrTrigger  = m_pCameraNodeMap->GetNode ("TriggerMode");
		ptrTrigger->SetIntValue(TriggerMode_On);
		CEnumerationPtr  ptrTriggerActivation  = m_pCameraNodeMap->GetNode ("TriggerActivation");
 		if (CMConfigCenter::GetSingletonConfigCenter()->GetTriggerEdge()==RISING_EDGE)
		{
			ptrTriggerActivation->SetIntValue(TriggerActivation_RisingEdge);
		}
		else
		{
			ptrTriggerActivation->SetIntValue(TriggerActivation_FallingEdge);
		}
 	}
 	else  //Disable acquisition start trigger if available
 	{
		CEnumerationPtr  ptrTrigger  = m_pCameraNodeMap->GetNode ("TriggerMode");
		ptrTrigger->SetIntValue(TriggerMode_Off);
	}
	//if (CMConfigCenter::GetSingletonConfigCenter()->GetCameraGain()!=0)
	{
		CIntegerPtr  ptrGainRaw  = m_pCameraNodeMap->GetNode ("GainRaw");
		if (ptrGainRaw!=NULL)
		{
			ptrGainRaw->SetValue(CMConfigCenter::GetSingletonConfigCenter()->GetCameraGain());
		}
	}

	//if (CMConfigCenter::GetSingletonConfigCenter()->GetTriggerDelayAbs()!=0) //Add camera delay time setting
	{
		CFloatPtr  ptrTriggerDelayAbs  = m_pCameraNodeMap->GetNode ("TriggerDelayAbs");
		if (ptrTriggerDelayAbs!=NULL)
		{
			ptrTriggerDelayAbs->SetValue(CMConfigCenter::GetSingletonConfigCenter()->GetTriggerDelayAbs());
		}
	}

	return true;
}

bool CBaslerCamera::OpenLineScanCamera(string CameraName)
{
	// set colour mode
	CEnumerationPtr ptrPixelFormat = m_pCameraNodeMap->GetNode ("PixelFormat");
	ptrPixelFormat->FromString ("Mono8");
	m_PixelFormat = PixelType_Mono8;

	using namespace GenApi;
	// Get the parameters for setting the image area of interest (Image AOI).
	const CIntegerPtr width = m_pCameraNodeMap->GetNode("Width");
	const CIntegerPtr height = m_pCameraNodeMap->GetNode("Height");
	const CIntegerPtr offsetX = m_pCameraNodeMap->GetNode("OffsetX");
	const CIntegerPtr offsetY = m_pCameraNodeMap->GetNode("OffsetY");

	// Maximize the Image AOI.
	if (IsWritable(offsetX))
	{
		offsetX->SetValue(offsetX->GetMin());
	}
	if (IsWritable(offsetY))
	{
		offsetY->SetValue(offsetY->GetMin());
	}

	auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();
	const CIntegerPtr frameCount = m_pCameraNodeMap->GetNode("AcquisitionFrameCount");
	m_nFrameCount = pConfigCenter->GetFrameCountPerSheet();
	if(m_nFrameCount <=0)
	{
		m_nFrameCount = 8; // default value
	}
	frameCount->SetValue(m_nFrameCount);
	height->SetValue(pConfigCenter->GetLineCountPerFrame());

 	if (pConfigCenter->GetTriggerMode())
 	{
		CEnumerationPtr  ptrTrigger  = m_pCameraNodeMap->GetNode ("TriggerSelector");
		ptrTrigger->SetIntValue(TriggerSelector_AcquisitionStart);

		ptrTrigger  = m_pCameraNodeMap->GetNode ("TriggerMode");
		ptrTrigger->SetIntValue(TriggerMode_On);

		CEnumerationPtr  ptrTriggerActivation  = m_pCameraNodeMap->GetNode ("TriggerActivation");
 		if (pConfigCenter->GetTriggerEdge()==RISING_EDGE)
		{
			ptrTriggerActivation->SetIntValue(TriggerActivation_RisingEdge);
		}
		else
		{
			ptrTriggerActivation->SetIntValue(TriggerActivation_FallingEdge);
		}
 	}
 	else //Disable acquisition start trigger if available
 	{
		CEnumerationPtr  ptrTrigger  = m_pCameraNodeMap->GetNode ("TriggerMode");
		ptrTrigger->SetIntValue(TriggerMode_Off);
	}    

	if (CMConfigCenter::GetSingletonConfigCenter()->GetCameraGain()!=0) //增加线扫相机的灰度值
	{
		CIntegerPtr  ptrGainRaw  = m_pCameraNodeMap->GetNode ("GainRaw");
		if (ptrGainRaw!=NULL)
		{
			ptrGainRaw->SetValue(CMConfigCenter::GetSingletonConfigCenter()->GetCameraGain());
		}
	}

	
	return true;
}
// -----------------------------------------------------------------
// -----------------------------------------------------------------
// The application's main thread
bool CBaslerCamera::Open(string CameraName)
{
	try
	{
		m_pTlFactory = &CTlFactory::GetInstance ();
		// Get all attached cameras and exit application if no camera is found
		m_devices.clear ();
		m_pTlFactory->EnumerateDevices (m_devices);
		if (m_devices.empty ())
		{
			MessageBox(NULL,_T("No camera present!"), _T("CBaslerCamera::Open. EnumerateDevices"), MB_OK|MB_ICONEXCLAMATION);
			return false;
		}
		// Create and attach all Pylon Devices.
		m_ixCamera = 0;
		bool bFind = false;
		CString strCameraName = s2ws(CameraName).c_str();
		for (DeviceInfoList_t::iterator it = m_devices.begin (); it != m_devices.end (); it++)
		{
			CString name((*it).GetFriendlyName().c_str());
			if (name == strCameraName)
			{
				bFind = true;
				break;
			}		
			m_ixCamera++;
		}
		if (!bFind)
		{
			MessageBox(NULL,_T("Channel #%d cannot connect to camera."),theApp.m_strStaionID,MB_OK);
			return false;
		}
		// Stop the grab; close the pylon device; destroy the pylon device.
		// DestroyDevice does not throw C++ exceptions.
		m_camera.DestroyDevice();
		// Now a new device can be connected.
		
		// Create the camera
		m_camera.Attach( m_pTlFactory->CreateDevice(m_devices[m_ixCamera]));		
		// Open the camera
		m_camera.Open();
		// Get the camera node map
		m_pCameraNodeMap = &m_camera.GetNodeMap();
		CEnumerationPtr pDeviceScanType = m_pCameraNodeMap->GetNode("DeviceScanType");
		if(pDeviceScanType != nullptr)
		{
			int type =  pDeviceScanType->GetIntValue();
			m_bArrayCamera = (type == DeviceScanType_Areascan);
			CMConfigCenter::GetSingletonConfigCenter()->SetCameraType(type);
		}

		if(m_bArrayCamera)
		{
			 return OpenArrayCamera(CameraName);
		}
		else
		{
			return OpenLineScanCamera(CameraName);
		} 
	}

	CATCH_MSGBOX("CBaslerCamera::Open" ); 
	return false;
}

void CBaslerCamera::Run()
{
	m_rcvCount=0;
	
	m_nCounter=0;

	m_ShowWindowHID = CMConfigCenter::GetSingletonConfigCenter()->GetShowWindowHID();
	if (m_camera.IsPylonDeviceAttached())
	{
		m_camera.StartGrabbing(GrabStrategy_OneByOne, GrabLoop_ProvidedByInstantCamera);
	}
}

void CBaslerCamera::OnArrayCameraGrabbingImage(CInstantCamera& camera, const CGrabResultPtr& ptrGrabResult)
{
	if (m_camera.IsGrabbing()) 
	{
		CMData data;
		count_seconds(&data.m_reciveStartTime);

		int iWidth  = ptrGrabResult->GetWidth();
		int iHeight = ptrGrabResult->GetHeight();
		if (m_bColorCamera)
 		{
			m_Converter.OutputPixelFormat = PixelType_RGB8planar ;
			m_Converter.Convert(m_TargetImage,ptrGrabResult);
			Hlong redPlaneBuff   = (Hlong)m_TargetImage.GetPlane(0).GetBuffer();
			Hlong greenPlaneBuff = (Hlong)m_TargetImage.GetPlane(1).GetBuffer();
			Hlong bluePlaneBuff  = (Hlong)m_TargetImage.GetPlane(2).GetBuffer();

			gen_image3(&m_currentImg,"byte",iWidth,iHeight,redPlaneBuff, greenPlaneBuff, bluePlaneBuff);
		}
		else
		{
			gen_image1(&m_currentImg,"byte",iWidth, iHeight,(long)ptrGrabResult->GetBuffer());
		}
		if(m_bFisrtImage == true)
		{
			CMConfigCenter::GetSingletonConfigCenter()->UpdateDispWindowSetting(m_currentImg,m_ShowWindowHID);
			m_bFisrtImage = false;
		}
		m_rcvCount++;
		data.m_Image       = m_currentImg;
		data.m_reciveCount = m_rcvCount;
		data.m_ShowHWindow = m_ShowWindowHID;

		count_seconds(&data.m_reciveEndTime);
		CMCtrlCenter::GetSingletonCtrlCenter()->m_r_buffer_f.push_front(data);
		disp_obj(m_currentImg, m_ShowWindowHID);
		m_bHasFrame = true;
	}
}

void CBaslerCamera::OnLineScanGrabbingImage(CInstantCamera& camera, const CGrabResultPtr& ptrGrabResult)
{
	if (m_camera.IsGrabbing()) 
	{
		CMData data;
		count_seconds(&data.m_reciveStartTime);

		gen_image1(&m_currentImg,"byte",ptrGrabResult->GetWidth(),ptrGrabResult->GetHeight(),(long)ptrGrabResult->GetBuffer());
		if(m_bFisrtImage == true)
		{
			CMConfigCenter::GetSingletonConfigCenter()->UpdateDispWindowSetting(m_currentImg,m_ShowWindowHID);
			m_bFisrtImage = false;
		}
		m_nCounter++;
		if(m_nCounter == 1)
		{
			m_topHalfImg = m_currentImg;
			return;
		}
		else
		{
			m_tmpImg = m_currentImg;
			concat_obj( m_topHalfImg,m_currentImg, &m_currentImg);
			tile_images(m_currentImg, &m_currentImg, 1, "vertical");
			m_topHalfImg = m_tmpImg;

			m_rcvCount++;
			data.m_Image       = m_currentImg;
			data.m_reciveCount = m_rcvCount;
			data.m_ShowHWindow = m_ShowWindowHID;

			count_seconds(&data.m_reciveEndTime);

			CMCtrlCenter::GetSingletonCtrlCenter()->m_r_buffer_f.push_front(data);
			//set_part(m_ShowWindowHID,0,0,ptrGrabResult->GetWidth()-1,ptrGrabResult->GetHeight()*2-1);
			disp_obj(m_currentImg,m_ShowWindowHID);
			m_bHasFrame = true;
		}
		if(m_nCounter % m_nFrameCount == 0) // Reset the counter.
		{
			m_nCounter = 0;
		}
	}
}

// This method is called from the Instant Camera grab loop thread.
void CBaslerCamera::OnImageGrabbed( CInstantCamera& camera, const CGrabResultPtr& ptrGrabResult) 
{
	if (ptrGrabResult->GrabSucceeded())
	{
		if(m_bArrayCamera)
		{
			OnArrayCameraGrabbingImage(camera, ptrGrabResult);
		}
		else
		{
			OnLineScanGrabbingImage(camera, ptrGrabResult);
		}
	}
	else  // The image was incompletely grabbed
	{
		// Do not handle errors caused by device removal.
		if ( !camera.IsCameraDeviceRemoved())
		{
			// Grabbing an image can fail if the used network hardware, i.e. network adapter, 
			// switch or Ethernet cable, experiences performance problems.
			// Increase the Inter-Packet Delay to reduce the required bandwidth.
			// It is recommended to enable Jumbo Frames on the network adapter and switch.
			// Adjust the Packet Size on the camera to the highest supported frame size.
			// If this did not resolve the problem, check if the recommended hardware is used.
			// Aggressive power saving settings for the CPU can also cause the image grab to fail.
			string msg = "Image grab failed";
			msg += ptrGrabResult->GetErrorDescription();			
			TLOG_ERROR(_T("ERROR:Channel %s cannot grab image !"),theApp.m_strStaionID);
		}
	}
}

// Instant Camera Configuration Event.
// This method is called from additional Instant Camera thread.
void CBaslerCamera::OnCameraDeviceRemoved( CInstantCamera& camera)
{
	// The WM_DEVICE_REMOVED message will call CLiveViewPylonDlg::OnDeviceRemoved,
	// informing the GUI thread, that the GUI can now be updated.
	// Stop the grab; close the pylon device; destroy the pylon device.
	// DestroyDevice does not throw C++ exceptions.
	m_camera.DestroyDevice();
	// Reset the viewer.
	// Force CBitmapControl to repaint its client area.
	MessageBox(NULL, _T("The camera device has been removed."), _T("CBaslerCamera::OnDeviceRemoved"), MB_OK | MB_ICONEXCLAMATION);
	return ;
}

// Instant Camera Configuration Event.
// This method is called from the Instant Camera grab loop thread.
void CBaslerCamera::OnGrabError( CInstantCamera& camera, const char* errorMessage)
{
	// Do not handle errors caused by device removal.
	if ( !camera.IsCameraDeviceRemoved())
	{
		string message;
		message ="An error occurred during grabbing = ";
		message+= errorMessage;
		MessageBox(NULL, s2ws(message).c_str(), _T("CBaslerCamera::OnGrabError"), MB_OK | MB_ICONEXCLAMATION);

		Stop();
	}
}

void CBaslerCamera::Pause()
{
	if (m_camera.IsGrabbing())
	{
		m_camera.StopGrabbing();
	}
}

void CBaslerCamera::Resume()
{
	m_rcvCount=0;
	m_nCounter = 0;
	if (!m_camera.IsGrabbing())
	{
		m_camera.StartGrabbing(GrabStrategy_OneByOne, GrabLoop_ProvidedByInstantCamera);
	}
}

//Step 3.1 Stop Thread
void CBaslerCamera::Stop()
{
	if (m_camera.IsGrabbing())
	{
		m_camera.StopGrabbing();
	}
	::SetEvent(CMCtrlCenter::GetSingletonCtrlCenter()->m_hCameraStopEvent);
	
	m_camera.Close();
	m_camera.DestroyDevice();
}

void CBaslerCamera::UpdateSingleFrame() 
{
	CMConfigCenter::GetSingletonConfigCenter()->SetHasFrameFlag(m_bHasFrame);
	if(CMConfigCenter::GetSingletonConfigCenter()->GetDebugModeFlag())
	{
		m_camera.StopGrabbing();
	}
	else
	{
		m_nCounter = 0; //单张后再开会出现拼接错位的问题
		m_camera.StartGrabbing(GrabStrategy_OneByOne, GrabLoop_ProvidedByInstantCamera);	
	}		
}

void CBaslerCamera::GenSoftTrigger()
{
	bool bDebugFlag = CMConfigCenter::GetSingletonConfigCenter()->GetDebugModeFlag();
	if(!bDebugFlag) // 
		return;

	using namespace GenApi;
	m_camera.StartGrabbing(GrabStrategy_OneByOne, GrabLoop_ProvidedByInstantCamera);

	CEnumerationPtr  ptrTriggerSource  = m_pCameraNodeMap->GetNode ("TriggerSource");
	int64_t ts = ptrTriggerSource->GetIntValue();
	ptrTriggerSource->SetIntValue(TriggerSource_Software);

	while(m_camera.IsGrabbing())
	{
		if ( m_camera.WaitForFrameTriggerReady(300, TimeoutHandling_ThrowException))
		{
			m_camera.ExecuteSoftwareTrigger();
			Sleep(50);
			break;
		}
	}
	m_camera.StopGrabbing();
	ptrTriggerSource->SetIntValue(ts);
}
