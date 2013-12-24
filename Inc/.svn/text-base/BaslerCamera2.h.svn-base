#pragma once

#include <stdlib.h>
#include "cpp/HalconCpp.h"
#include "MData.h"
#include "IMActiveObj.h"
#include "MConfigCenter.h"

// Include files to use the PYLON API.
#include <pylon/PylonIncludes.h>
#include <pylon/PylonGUI.h>

// Namespace for using pylon objects.
using namespace Pylon;

// Namespace for using cout.
using namespace std;

// Number of images to be grabbed.
static const uint32_t c_countOfImagesToGrab = 10;

static const uint32_t c_maxCamerasToUse = 2;
using namespace std;
using namespace Halcon;

#define CATCH_MSGBOX( Caption ) \
	catch( GenICam::GenericException &e ) \
{ \
	CString Buffer, B; \
	Buffer += (B.Format(_T("Exception 0x%X occurred\n"), e.what() ), B); \
	Buffer += (B.Format(_T("Message = %s\n"), s2ws(e.GetDescription()).c_str() ), B); \
	MessageBox(NULL,Buffer, _T(Caption), MB_OK | MB_ICONEXCLAMATION); \
	return false;\
} \
	catch (...) \
{ \
	GenICam::GenericException e (Caption, "CLiveViewPylonDlg", 0); \
	CString Buffer, B; \
	Buffer += (B.Format(_T("Exception 0x%X occurred\n"), e.what() ), B); \
	Buffer += (B.Format(_T("Message = %s\n"), s2ws(e.GetDescription()).c_str() ), B); \
	MessageBox(NULL,Buffer, _T(Caption), MB_OK | MB_ICONEXCLAMATION); \
	return false;\
}

class CBaslerCamera : public CImageEventHandler             // For receiving grabbed images.
	, public CConfigurationEventHandler     // For getting notified about device removal.
{
public:	
	CBaslerCamera();
	~CBaslerCamera();
	bool Init();
	bool Open(string CameraName);
	void Run();
	void Pause();
	void Resume();
	void Stop();
	void GenSoftTrigger();
	void UpdateSingleFrame();

	void RetrieveCurrentImage(Hobject *image)
	{
		CMConfigCenter::GetSingletonConfigCenter()->SetHasFrameFlag(m_bHasFrame);
		*image = m_currentImg;
	};

	virtual void OnImageGrabbed( CInstantCamera& camera, const CGrabResultPtr& ptrGrabResult);

	// Instant Camera Configuration Event.
	// This method is called from the Instant Camera grab loop thread.
	virtual void OnGrabError( CInstantCamera& camera, const char* errorMessage);

	// Instant Camera Configuration Event.
	// This method is called from additional Instant Camera thread.
	virtual void OnCameraDeviceRemoved( CInstantCamera& camera);
private:
	CImageFormatConverter m_Converter;
	CPylonImage m_TargetImage;
	Hobject m_topHalfImg; // Only for Project #8126
	Hobject m_currentImg;
	Hlong	m_rcvCount;
	Hlong m_ShowWindowHID;
	bool m_bHasFrame;
	// Device list.
	Pylon::DeviceInfoList_t m_devices;
	// Index of currently used camera.
	int m_ixCamera;
	// The CInstant camera.
	CInstantCamera m_camera;
	// The TransportLayer.
	Pylon::CTlFactory *m_pTlFactory;
	// Camera Node Map.
	GenApi::INodeMap *m_pCameraNodeMap;
	// The current pixel type.
	Pylon::PixelType m_PixelFormat;
	CRITICAL_SECTION*    m_pReciveDataMutex;
	CConfigurationEventHandler* m_AcquisitionConfig;
	bool m_bColorCamera;
	bool m_bArrayCamera; // True:Array Camera; False:Line Scan Camera
	int  m_nCounter;     // Only for Line Scan Camera
	int  m_nFrameCount;  // Only for Line Scan Camera
	Hobject m_tmpImg;
	bool m_bFisrtImage;
private:
	bool OpenArrayCamera(string CameraName);
	bool OpenLineScanCamera(string CameraName);
	void OnArrayCameraGrabbingImage(CInstantCamera& camera, const CGrabResultPtr& ptrGrabResult);
	void OnLineScanGrabbingImage(CInstantCamera& camera, const CGrabResultPtr& ptrGrabResult);
};

