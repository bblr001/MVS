#pragma once
#include "StdAfx.h"
#include "ImageFilePump.h"
#include "MCtrlCenter.h"
#include "MConfigCenter.h"
#include <atlconv.h>


using namespace Halcon;

CImageFilePump::CImageFilePump(void)
{
	m_isExit=false;
	m_recvCount=0;
	m_TimeInterval=20;
	m_bHasFrame = false;
#ifdef SHEET_INSPECTION
	m_iNCounter=0;
	m_hSyncEvent   = CreateEvent(NULL, TRUE, FALSE, _T("SyncEventForTest"));
#endif
	m_bFirstImage = true;
}

CImageFilePump::~CImageFilePump(void)
{
	m_isExit=true;
}

BOOL CImageFilePump::Init()
{
	//auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();
	
	m_recvCount = 0;
	m_bDebugMode = false;
	return TRUE;
}

UINT CImageFilePump::Main()
{
	m_isExit = false;
	HTuple tmpReciveStartTime;
	
	m_bDebugMode = false;
	Hobject	tmpImage;
	m_recvCount = 0;

	auto pCtrlCenter   = CMCtrlCenter::GetSingletonCtrlCenter();
	auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();
	Hlong showWindowHID = pConfigCenter->GetShowWindowHID();

	m_TimeInterval = pConfigCenter->GetReciveFilesTimeInterval(); 
	m_strFilePath = s2ws(pConfigCenter->GetRecvFilesPath()).c_str();



	unsigned int framePerSheet = 0;

	bool bArrayCamera = (pConfigCenter->GetCameraType() == ARRAY_CAMERA);
	if(bArrayCamera)
	{
		framePerSheet = pConfigCenter->GetLineCountPerFrame();
		if(framePerSheet == 0)
		{
			framePerSheet = 8; // default value
		}
	}
	CFileFind ff;
	BOOL bRet;	
	CMData data;
	Hobject tmpImg;
	CString strSearchPath = m_strFilePath + _T("\\*.tiff");
	m_iNCounter = 0;
	USES_CONVERSION;
	while (!m_isExit)
	{
		if (ff.FindFile(strSearchPath))
		{
			do
			{
				bRet=ff.FindNextFile();
				if (!ff.IsDirectory())
				{	
					if(m_isExit)
					{
						ff.Close();
						break;
					}
					tmpReciveStartTime.Reset();
					count_seconds(&tmpReciveStartTime);
#ifdef SHEET_INSPECTION
					//::WaitForSingleObject(m_hSyncEvent, INFINITE);
					OutputDebugString(m_strFilePath + ff.GetFileName());
					OutputDebugString(_T("\n"));
					read_image(&m_currentImg,T2CA(m_strFilePath + ff.GetFileName()));
					//if(!bArrayCamera) 
					if(true) // Debug code
					{
						m_iNCounter++;
						if(m_iNCounter  == 1) // concat tow images into a big one
						{
							m_topHalfImg = m_currentImg;
							continue;
						}
						
#if 0                  
						// For debug  读2张时使用
						if(m_iNCounter == 2)
						{
							concat_obj( m_topHalfImg,m_currentImg, &m_currentImg);
						    tile_images(m_currentImg, &m_currentImg, 1, "vertical");
							m_iNCounter = 0;
						}
#endif
#if 1                   
						// End Test  读8张时使用
						else
						{
							tmpImg = m_currentImg;
							concat_obj( m_topHalfImg,m_currentImg, &m_currentImg);
							tile_images(m_currentImg, &m_currentImg, 1, "vertical");
							m_topHalfImg = tmpImg;
						}
						if(m_iNCounter % 8 == 0) // Debug
						////if(nCounter % framePerSheet == 0) 
						{
							m_iNCounter = 0;
						}
#endif

					}
#else
					m_currentImg.Reset();
					try
					{
						CString fileName = m_strFilePath + ff.GetFileName();
						string aFileName = CT2A(fileName.GetString());
						read_image(&m_currentImg,aFileName.c_str());
					}
					catch(...)
					{
						m_currentImg.Reset();
					}
#endif
					if(m_bFirstImage == true)
					{
                        pConfigCenter->UpdateDispWindowSetting(m_currentImg,showWindowHID);
						m_bFirstImage = false;
					}
					if(pConfigCenter->GetProgramChangedFlag() == true)
					{
						pConfigCenter->UpdateDispWindowSetting(m_currentImg,showWindowHID);
						pConfigCenter->SetProgramChangedFlag(false);
					}
					data.m_reciveStartTime = tmpReciveStartTime;
					data.m_Image = m_currentImg;
					data.m_reciveCount = (++m_recvCount);
					Reset(&data);
					data.m_ShowHWindow = showWindowHID;
					count_seconds(&data.m_reciveEndTime);
					disp_obj(m_currentImg,showWindowHID);
					if(pCtrlCenter->m_r_buffer_f.is_not_full())
					{
						pCtrlCenter->m_r_buffer_f.push_front(data);
					}
					m_bHasFrame = true;
					Sleep(m_TimeInterval);
					Sleep(50);
					while(m_bDebugMode)
					{
						if (m_isExit)
						{
							break;
						}
						Sleep(10);
					}
				}
			}while (bRet);		
		}
		ff.Close();
	}
	return 0;
}

void CImageFilePump::Stop()
{
	m_isExit = true;
	CloseHandle(m_hThread);
	m_hThread = nullptr;
}