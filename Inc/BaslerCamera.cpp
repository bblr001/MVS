#pragma once
#include "stdafx.h"
#include <float.h>
#include <genapi//NodeMapRef.h>

/*#include "pylon_utilities.h"*/
#include "BaslerCamera.h"
#include "..\Inc\MData.h"
#include "MCtrlCenter.h"
#include "MConfigCenter.h"
#include "AOIEdit.h"
#include "TLog.h"

static int callbackCounter(0);


// -----------------------------------------------------------------
//   Implementation of the CGrabBuffer class
// -----------------------------------------------------------------

// Constructor allocates the image buffer
CGrabBuffer::CGrabBuffer(const size_t ImageSize):m_pBuffer(NULL)
{
	m_pBuffer = new uint8_t[ ImageSize ];
	if (NULL == m_pBuffer)
	{
		GenICam::GenericException e("Not enough memory to allocate image buffer", __FILE__, __LINE__);
		throw e;
	}
};

// Freeing the memory
CGrabBuffer::~CGrabBuffer()
{
	if (NULL != m_pBuffer)
		delete[] m_pBuffer;
};


// Simple helper class to set the HeartbeatTimeout safely
class CHearbeatHelper
{
public:
	explicit CHearbeatHelper(IPylonDevice* pCamera)
		: m_pHeartbeatTimeout(NULL)
	{
		try
		{
			if (pCamera == NULL)
				return;

			GenApi::INodeMap* pTLNodeMap = pCamera->GetTLNodeMap();
			if (pTLNodeMap == NULL)
				return; // Nothing we can do, leave m_pHeartbeatTimeout NULL

			// m_pHeartbeatTimeout may be NULL
			m_pHeartbeatTimeout = pTLNodeMap->GetNode("HeartbeatTimeout");
		}
		catch (GenericException& e)
		{
			m_pHeartbeatTimeout = NULL;
		}
	}

	bool SetValue(int64_t NewValue)
	{
		// Do nothing if no heartbeat feature is avalable
		if (!m_pHeartbeatTimeout.IsValid())
			return false;

		// Apply the increment and cut off invalid values if neccessary
		int64_t correctedValue = NewValue - (NewValue % m_pHeartbeatTimeout->GetInc());

		m_pHeartbeatTimeout->SetValue(correctedValue);
		return true;
	}

	bool SetMax()
	{
		// Do nothing if no heartbeat feature is avalable
		if (!m_pHeartbeatTimeout.IsValid())
			return false;

		int64_t maxVal = m_pHeartbeatTimeout->GetMax();
		return SetValue(maxVal);
	}

protected:
	GenApi::CIntegerPtr m_pHeartbeatTimeout; // pointer to the node, will be NULL if no node exists
};



CBaslerCamera::CBaslerCamera()
{
	m_ixCamera = -1;
	m_pCamera = 0;
	ReciveCount=0;	
	m_TriggerMode=true;
	m_LiveGrabbing = false;
	m_strCameraName = "NONE";
	m_bHasFrame=NULL;

}
bool CBaslerCamera::Init()
{
	m_pReciveDataMutex = CMCtrlCenter::GetCtrlCenter().GetReciveDataMutex();
	m_TriggerMode = CMConfigCenter::GetConfigCenter().GetTriggerMode();
	ReciveCount=0;
	m_SingleFrame = false;
	m_ReciveFrame = false;
	return true;
}

CBaslerCamera::~CBaslerCamera()
{
}

// A class with a member function that can be registered for device removal notification
class AClass
{
public:
	// The member function to be registered
	void RemovalCallbackMemberFunction(IPylonDevice* pDevice)
	{
		string msg ="Device ";
		msg+= pDevice->GetDeviceInfo().GetFriendlyName().c_str();
		msg+= " Disconnect. Please Confirm.";
		callbackCounter++;
		theApp.GetMainWnd()->SendMessage(WM_MI_STOP_MESSAGE);		
		TLOG_NOTICE(s2ws(msg).c_str());
		AfxMessageBox(s2ws(msg).c_str());
		//MessageBox(,s2ws(msg).c_str(),theApp.m_strStaionID,MB_OK);
		//AfxGetMainWnd()->SendMessage(ID_BUTTON_STOP,NULL);
	}

};


// 
// void RemovalCallbackFunction(IPylonDevice* pDevice)
// {
// 	string msg ="Device ";
// 	msg+= pDevice->GetDeviceInfo().GetFriendlyName().c_str();
// 	msg+= " Disconnect. Please Confirm.";
// 	callbackCounter++;
// 
// 	TLOG_NOTICE(s2ws(msg).c_str());
// 	AfxMessageBox(s2ws(msg).c_str());
// 
// 	cout << endl << "Callback function for removal of device "
// 		<< pDevice->GetDeviceInfo().GetFullName().c_str() << " has been fired" << endl;
// 
// }

bool CBaslerCamera::Open(string CameraName)
{

	AClass a;		
	//Pylon::PylonAutoInitTerm autoInitTerm;

	try
	{
		m_pTlFactory = &CTlFactory::GetInstance ();
		m_devices.clear ();
		m_pTlFactory->EnumerateDevices (m_devices);
		if (m_devices.empty ())
		{
			//MessageBox("No camera present!", "CBaslerCamera::OnInitDialog", MB_OK|MB_ICONEXCLAMATION);
			return false;
		}
		m_strCameraName = CameraName;

		m_ixCamera=0;
		bool bFind=false;

		CString strCameraName=s2ws(m_strCameraName).c_str();
		for (DeviceInfoList_t::iterator it = m_devices.begin (); it != m_devices.end (); it++)
		{
			CString name((*it).GetFriendlyName().c_str());
			if (name == strCameraName)
			{
				bFind=true;
				break;
			}		
			m_ixCamera++;
		}
		if (!bFind)
		{
			//AfxMessageBox(_T("Nofind Camera Error"));
			MessageBox(NULL,_T("No find Camera Error"),theApp.m_strStaionID,MB_OK);
			return false;
		}
		


		//m_ixCamera = m_strCameraName;

		// Create the camera object of the first available camera
		// The camera object is used to set and get all available
		// camera features.
		m_pCamera = m_pTlFactory->CreateDevice (m_devices[m_ixCamera]);
		// Get the first stream grabber object of the selected camera
		m_pStreamGrabber = m_pCamera->GetStreamGrabber (0);

		// Open the camera
		m_pCamera->Open ();
		// Open the stream grabber
		m_pStreamGrabber->Open ();
		

		// Register a member function
		m_hCb1 = RegisterRemovalCallback(m_pCamera, a, &AClass::RemovalCallbackMemberFunction);

		// Register a "normal" function
		//m_hCb2 = RegisterRemovalCallback(m_pCamera, &RemovalCallbackFunction);


#ifdef _DEBUG
		// Before testing the callbacks, for GigE cameras we manually set the heartbeat timeout to a short value.
		// Since for debug versions the heartbeat timeout has been set to 5 minutes, it would take up to 5 minutes 
		// until detection of the device removal.
		CHearbeatHelper heartbeatHelper(m_pCamera);
		heartbeatHelper.SetValue(5000);  // 1000 ms timeout
#endif

		// get Node Map for device configuration
		m_pCameraNodeMap = m_pCamera->GetNodeMap ();

		// set color mode
		// is it a color camera?
		CEnumerationPtr ptrPixelFormat = m_pCameraNodeMap->GetNode ("PixelFormat");
		ptrPixelFormat->FromString ("Mono8");

		// Set AOI
		CIntegerPtr ptrOffsetX = m_pCameraNodeMap->GetNode ("OffsetX");
		CIntegerPtr ptrOffsetY = m_pCameraNodeMap->GetNode ("OffsetY");
		CIntegerPtr ptrAoiWidth = m_pCameraNodeMap->GetNode ("Width");
		CIntegerPtr ptrAoiHeight = m_pCameraNodeMap->GetNode ("Height");
		ptrOffsetX->SetValue (0);
		ptrOffsetY->SetValue (0);
		ptrAoiWidth->SetValue (ptrAoiWidth->GetMax ());
		ptrAoiHeight->SetValue (ptrAoiHeight->GetMax ());

		//Set exposure settings
// 		CEnumerationPtr(m_pCameraNodeMap->GetNode("ExposureMode"))->FromString("Timed");
// 		CIntegerPtr(m_pCameraNodeMap->GetNode("ExposureTimeRaw"))->SetValue(CMConfigCenter::GetConfigCenter().GetExposureTimeRaw());

		if (m_TriggerMode)
		{
			// Set the camera to continuous shot mode
			CEnumerationPtr ptrTriggerSelector = m_pCameraNodeMap->GetNode ("TriggerSelector");
			ptrTriggerSelector->FromString ("AcquisitionStart");
			CEnumerationPtr ptrTriggerMode = m_pCameraNodeMap->GetNode ("TriggerMode");
			ptrTriggerMode->FromString ("On");
			//ptrTriggerSelector->FromString ("FrameStart");
			//ptrTriggerMode = m_pCameraNodeMap->GetNode ("TriggerMode");
			//ptrTriggerMode->FromString ("On");

			CEnumerationPtr ptrTriggerActivation = m_pCameraNodeMap->GetNode ("TriggerActivation");
			if (CMConfigCenter::GetConfigCenter().GetProgramData()->GetTriggerEdge()==RISING_EDGE)
			{
				ptrTriggerActivation->FromString ("RisingEdge");
			}
			else
			{
				ptrTriggerActivation->FromString ("FallingEdge");
			}
		}
		else
		{
			// Set the camera to continuous shot mode
			CEnumerationPtr ptrTriggerSelector = m_pCameraNodeMap->GetNode ("TriggerSelector");
			ptrTriggerSelector->FromString ("AcquisitionStart");
			CEnumerationPtr ptrTriggerMode = m_pCameraNodeMap->GetNode ("TriggerMode");
			ptrTriggerMode->FromString ("Off");
			//ptrTriggerSelector->FromString ("FrameStart");
			//ptrTriggerMode = m_pCameraNodeMap->GetNode ("TriggerMode");
			//ptrTriggerMode->FromString ("Off");

		}
		CEnumerationPtr ptrTriggerSource = m_pCameraNodeMap->GetNode ("TriggerSource");
		ptrTriggerSource->FromString ("Line1");

		CEnumerationPtr ptrLineSource = m_pCameraNodeMap->GetNode ("LineSource");
		ptrLineSource->FromString ("ExposureActive");

		// 	CEnumerationPtr ptrAcquisitionMode = m_pCameraNodeMap->GetNode ("AcquisitionMode");
		// 	ptrAcquisitionMode->FromString ("Continuous");
		CEnumerationPtr ptrExposureMode = m_pCameraNodeMap->GetNode ("ExposureMode");
		ptrExposureMode->FromString ("Timed");

		// Get the image buffer size
		CIntegerPtr ptrPayloadSize = m_pCameraNodeMap->GetNode ("PayloadSize");
		m_ImageSize = (size_t) (ptrPayloadSize->GetValue ());

		// get Node Map for stream grabber configuration
		GenApi::INodeMap *pGrabberNodeMap = m_pStreamGrabber->GetNodeMap ();

		// We won't use image buffers greater than ImageSize
		CIntegerPtr ptrMaxBufferSize = pGrabberNodeMap->GetNode ("MaxBufferSize");
		ptrMaxBufferSize->SetValue (m_ImageSize);

		// We won't queue more than c_nBuffers image buffer at a time
		CIntegerPtr ptrMaxNumBuffer = pGrabberNodeMap->GetNode ("MaxNumBuffer");
		ptrMaxNumBuffer->SetValue (NUM_BUFFERS);

		// Allocate all resources for grabbing. Critical parameters like image
		// size now must not be changed until FinishGrab() is called.
		m_pStreamGrabber->PrepareGrab ();

	}
	catch (GenICam::GenericException &e)
	{
		// Error handling
		string msg ="Connect Camera exception occurred! ";
		msg+= e.GetDescription();
		TLOG_NOTICE(s2ws(msg).c_str());
		//MessageBox(NULL,s2ws(msg).c_str(),theApp.m_strStaionID,MB_OK);
		AfxMessageBox(s2ws(msg).c_str());
		return false;
	}
	return true;
}






UINT CBaslerCamera::Main()
{
	m_LiveGrabbing = true;
	m_pBufferList.clear ();
	// create and prepare the wait object container
	m_TerminationEvent.Reset();
	WaitObjects waitObjects;
	
	waitObjects.Add (m_pStreamGrabber->GetWaitObject ());  // getting informed about buffers
	waitObjects.Add (m_TerminationEvent); // getting informed about termination request

	for (uint32_t i = 0; i < NUM_BUFFERS; ++i)
	{
		CGrabBuffer *pGrabBuffer = new CGrabBuffer(m_ImageSize);
		pGrabBuffer->SetBufferHandle(m_pStreamGrabber->RegisterBuffer(
			pGrabBuffer->GetBufferPointer(), m_ImageSize));

		// Put the grab buffer object into the buffer list
		m_pBufferList.push_back(pGrabBuffer);
	}
	// Queue in all buffers from buffer list
	for (std::vector<CGrabBuffer*>::const_iterator x = m_pBufferList.begin(); x != m_pBufferList.end(); ++x)
	{
		// Put buffer into the grab queue for grabbing
		m_pStreamGrabber->QueueBuffer((*x)->GetBufferHandle(), NULL);
	}

	m_ShowWindowHID = CMConfigCenter::GetConfigCenter().GetShowWindowHID();
	try
	{
		// get Node Map for device configuration
		GenApi::INodeMap *pCameraNodeMap = m_pCamera->GetNodeMap ();

		// Start acquisition on the camera
		CCommandPtr ptrAcquisitionStart = pCameraNodeMap->GetNode ("AcquisitionStart");
		ptrAcquisitionStart->Execute ();

		unsigned int index;			// index of the wait object that has been signalled
		unsigned int nSucc = 0;		// number of successfully grabbed images
		GrabResult result;			// grab result
		bool terminate = false; 

		using namespace Halcon;
		Hobject	myImage;
		
		ReciveCount=0;

		while (!terminate)
		{
			if  (! waitObjects.WaitForAny (INFINITE, &index))
			{
				// timeout occurred, should never happen when using INFINITE

				m_pStreamGrabber->CancelGrab();

				// Get all buffers back
				for (GrabResult r; m_pStreamGrabber->RetrieveResult(r););


				string msg ="Timeout occurred???? CBaslerCamera::GrabThreadProc";
				TLOG_NOTICE(s2ws(msg).c_str());
				AfxMessageBox(_T("Timeout occurred???? CBaslerCamera::GrabThreadProc"), MB_OK|MB_ICONEXCLAMATION);
				break;
			}
			switch (index)
			{
			case 0:  // a grabbed buffer is available
				if (m_pStreamGrabber->RetrieveResult(result))
				{
					if (result.Succeeded ())
					{
						int idxGrabbedBuffer = (int) result.Context ();
						// -----------------  WAIT FOR EVENTS  -----------------------------
						//if (m_PreProcess(myImage))
						if (!m_ReciveFrame)
						{
							CMData *pData = new CMData();
							count_seconds(&pData->ReciveStartTime);
							// retrieve the index of ring buffer element, which was just exposed
							gen_image1(&myImage,"byte",result.GetSizeX(),result.GetSizeY(),(long)result.Buffer());

							EnterCriticalSection(m_pReciveDataMutex);        // CriticalSect
							pData->m_Image = myImage;
							ReciveCount++;
							pData->ReciveCount = ReciveCount;
							pData->m_ShowHWindow= m_ShowWindowHID;
							count_seconds(&pData->ReciveEndTime);
							IMRecv::RecvData(pData);
							LeaveCriticalSection(m_pReciveDataMutex);        // CriticalSect	
							disp_image(myImage,m_ShowWindowHID);
							if (m_SingleFrame)
							{
								m_ReciveFrame=true;
							}
							m_CurrentFrame=myImage;
							m_bHasFrame = true;
							//Sleep(5);
							
						}
 						else
 						{
							string msg ="Failed to retrieve m_ReciveFrame is true";
							TLOG_NOTICE(s2ws(msg).c_str());
 						}
						m_pStreamGrabber->QueueBuffer(result.Handle(),(void*)idxGrabbedBuffer);

					}
					break;

				}				
				else
				{
					string msg ="Failed to retrieve result in CBaslerCamera::GrabThreadProc";
					TLOG_NOTICE(s2ws(msg).c_str());
					//AfxMessageBox(_T("Failed to retrieve result in CBaslerCamera::GrabThreadProc"),  MB_OK|MB_ICONEXCLAMATION);
					terminate = true;
					break;
				}

			case 1:  // got a termination request
				{
					terminate = true;
					string msg ="Get a termination request!";
					TLOG_NOTICE(s2ws(msg).c_str());
					break;
				}
			}
		}
 		CCommandPtr ptrAcquisitionStop = pCameraNodeMap->GetNode ("AcquisitionStop");
 		ptrAcquisitionStop->Execute ();
		// Stop image acquisition

		string msg ="Grab Thread Proc Stop exit while loop";
		TLOG_NOTICE(s2ws(msg).c_str());
	}
	catch( GenICam::GenericException &e )
	{
		// Error handling
		string msg ="The grab thread encountered an exception: ";
		msg +=e.GetDescription();

		TLOG_NOTICE(s2ws(msg).c_str());
		

		return 1;
	}

	string msg ="Return Mail loop in recive thread:";
	TLOG_NOTICE(s2ws(msg).c_str());
	return 0;
}


//Step 3.1 Stop Thread
void CBaslerCamera::Stop()
{
	if (m_LiveGrabbing)
	{
		// Signal the thread to terminate
		m_TerminationEvent.Signal ();

		// Join with the thread, i.e., wait until it has terminated
		WaitObject woThread (m_hThread);
		woThread.Wait (1500);  // waits until the thread terminates

		// Get the pending buffer back (It is not allowed to deregister
		// buffers when they are still queued)
		m_LiveGrabbing = false;

		if (callbackCounter==0)
		{
			m_pStreamGrabber->CancelGrab ();
			for (GrabResult r; m_pStreamGrabber->RetrieveResult (r););
			// It is necessary to deregister buffer before freeing the memory
			for (std::vector<CGrabBuffer*>::iterator it = m_pBufferList.begin (); it != m_pBufferList.end (); it++)
			{
				m_pStreamGrabber->DeregisterBuffer ((*it)->GetBufferHandle ());
				delete *it;
				*it = NULL;
			}	
		}

		// Stop image acquisition
		if (callbackCounter==0)
		{
			GenApi::INodeMap *pCameraNodeMap = m_pCamera->GetNodeMap ();
			CCommandPtr ptrAcquisitionStop = pCameraNodeMap->GetNode ("AcquisitionStop");
			ptrAcquisitionStop->Execute ();
		}
	}     
	IMActiveObj::m_hThread=NULL;
}

//Step 3.2 CleanUpCamera
void CBaslerCamera::Close ()
{
	this->Stop();
	if (m_pCamera && m_pCamera->IsOpen ())
	{
		if (! m_pCamera->DeregisterRemovalCallback(m_hCb1))
			TLOG_NOTICE(_T("Failed to deregister the callback function"));

// 		if (! m_pCamera->DeregisterRemovalCallback(m_hCb2))
// 			cerr << "Failed to deregister the callback function" << endl;

		if (callbackCounter==0)
		{
			// Free all resources used for grabbing
			m_pStreamGrabber->FinishGrab ();
			// Close stream grabber
		}
		m_pStreamGrabber->Close ();
		// Close camera
		if (callbackCounter==0)
			m_pCamera->Close ();
	}
	// Delete camera object
	if (callbackCounter==0)
		m_pTlFactory->DestroyDevice (m_pCamera);
	m_pCamera = NULL;
	callbackCounter=0;
}


inline bool CBaslerCamera::m_PreProcess(Hobject tmpImage)
{
	//pre process 
	//the object is ok. return true than return false
	return true;
}