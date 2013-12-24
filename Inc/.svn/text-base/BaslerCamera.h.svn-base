#pragma once

#include <pylon/PylonIncludes.h>
//#include "pylon_utilities.h"
#include "cpp/HalconCpp.h"
#include "MData.h"
#include "MRecvCenter.h"

#include "IMActiveObj.h"
#include "IMRecv.h"
#include "MConfigCenter.h"
using namespace Pylon;
using namespace GenApi;
using namespace GenICam; 
using namespace std;

//! Number of buffers used for grabbing
const unsigned int NUM_BUFFERS = 3;
const unsigned int MAX_DISPLAY_NUM_BUFFERS = 5;
const int TIMER = 100;
//! Message fired by the GrabThread if the grab is finished
const UINT WM_GRAB_FINISHED = WM_USER;

using namespace Halcon;

class CGrabBuffer
{
public:
	CGrabBuffer(const size_t ImageSize);
	~CGrabBuffer();
	uint8_t* GetBufferPointer(void) { return m_pBuffer; }
	StreamBufferHandle GetBufferHandle(void) { return m_hBuffer; }
	void SetBufferHandle(StreamBufferHandle hBuffer) { m_hBuffer = hBuffer; };

protected:
	uint8_t *m_pBuffer;
	StreamBufferHandle m_hBuffer;
};


class CMRecvCenter;
class CBaslerCamera :public IMActiveObj,public IMRecv
{
private:
	// device list
	DeviceInfoList_t m_devices;
	// index of currently used camera
	int m_ixCamera;
	string m_strCameraName;
	// The camera
	IPylonDevice *m_pCamera;
	// The StreamGrabber
	IStreamGrabber *m_pStreamGrabber;
	// The TransportLayer
	CTlFactory *m_pTlFactory;
	// Camera Node Map
	GenApi::INodeMap *m_pCameraNodeMap;
	// indicates, that we're grabbing
	bool m_LiveGrabbing;
	
	// List to maintain ring buffer
	std::vector<CGrabBuffer*> m_pBufferList;
	//! Used to measure the frame rate

	// Aoi size
	//CSize m_AoiSize;
	// Image size
	size_t m_ImageSize;

	bool m_TriggerMode;
	// CleanUp
	// Event used to synchronize with thread
	AlertableWaitObject m_TerminationEvent;

	Hobject m_CurrentFrame;

public:	
	CBaslerCamera();
	bool Init();
	~CBaslerCamera();
	bool Open(string CameraName);
	void Start();
	void Stop();
	void Close();

	void AbnormalClose (CBaslerCamera* pCamera);
	//! Fired if the GrabThread sends a messages indicating that the grab is finished
	LRESULT OnGrabFinished(WPARAM wParam, LPARAM lParam);
	void UpdateSingleFrame() 
	{
		if (m_bHasFrame)
			CMConfigCenter::GetConfigCenter().SetHasFrame(true);
		else
			CMConfigCenter::GetConfigCenter().SetHasFrame(false);
		m_SingleFrame = CMConfigCenter::GetConfigCenter().GetSingleFrameModel();
		//if (m_SingleFrame)
		m_ReciveFrame=false;
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
	// is it a 8/12/16 bit image?
private:
	bool m_PreProcess(Hobject tmpImage);
	list<CMData*>* p_DataList;
	bool	    m_ThreadsAreRunning;
	Hlong	ReciveCount;
	Hlong m_ShowWindowHID;
	CMRecvCenter* m_pReciveCent;
	bool m_SingleFrame;
	bool m_ReciveFrame;
	bool m_bHasFrame;




public:
	void RegistRecvCent(CMRecvCenter* pReciveCent){m_pReciveCent = pReciveCent;};

protected:
	virtual UINT Main();
private:
	void RecvData(string fileName );
	CRITICAL_SECTION*    m_pReciveDataMutex;

	DeviceCallbackHandle m_hCb1;
	DeviceCallbackHandle m_hCb2;
	
};


