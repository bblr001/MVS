#pragma once
#include "StdAfx.h"
#include "CRecvFile.h"
#include "MCtrlCenter.h"
#include "MConfigCenter.h"


using namespace Halcon;

CMRecvFile::CMRecvFile(void)
{
	m_isExit=false;
	ReciveCount=0;
	m_TimeInterval=20;
}

CMRecvFile::~CMRecvFile(void)
{
	m_isExit=true;
}

BOOL CMRecvFile::Init()
{
	m_pReciveDataMutex = CMCtrlCenter::GetCtrlCenter().GetReciveDataMutex();
	//string tmp="";
	string tmp(CMConfigCenter::GetConfigCenter().GetRecvFilesPath());
	//tmp = CMConfigCenter::GetConfigCenter().GetRecvFileSearchPath();

	m_TimeInterval =CMConfigCenter::GetConfigCenter().GetReciveFilesTimeInterval(); 


	m_strFilePath= (s2ws(tmp)).c_str();
	m_strSearchPath=(s2ws(tmp)).c_str();

	m_strSearchPath+="\\*.tiff";
	m_isExit = CMConfigCenter::GetConfigCenter().GetRecvFilesIsOn();
	ReciveCount=0;
	m_SingleFrame = false;
	m_ReciveFrame = false;
	return TRUE;
}

UINT CMRecvFile::Main()
{
	m_isExit = false;
	HTuple tmpReciveStartTime;
	
	bool tmpBool;
	tmpBool=false;
	Hobject	tmpImage;
	ReciveCount=0;
	Hlong showWindowHID = CMConfigCenter::GetConfigCenter().GetShowWindowHID();
	m_SingleFrame=false;

	while (!m_isExit)
	{
		CFileFind ff;
		BOOL bRet;	
		if (ff.FindFile(m_strSearchPath))
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

					//while (!m_isExit)
					{
						CStringW strTmp =m_strFilePath + (CStringW)ff.GetFileName();
						CStringA strTmpa(strTmp.GetBuffer(0)); 
						strTmp.ReleaseBuffer();
						string fileName = strTmpa.GetBuffer(0);					
						tmpReciveStartTime.Reset();
						// retrieve the index of ring buffer element, which was just exposed
						//while (!m_isExit)
						{
							count_seconds(&tmpReciveStartTime);
							//if (!tmpBool)
							{
								read_image(&tmpImage,fileName.c_str());
								//tmpBool=true;
							}
							CMData *pData = new CMData();
							pData->ReciveStartTime=tmpReciveStartTime;
							pData->m_Image = tmpImage;
							ReciveCount++;
							pData->ReciveCount = ReciveCount;
							m_PreProcess(pData);
							pData->isDebug=true;
							pData->m_ShowHWindow= CMConfigCenter::GetConfigCenter().GetShowWindowHID();
							count_seconds(&pData->ReciveEndTime);
							//EnterCriticalSection(m_pReciveDataMutex);    // CriticalSect
							IMRecv::RecvData(pData);
							//LeaveCriticalSection(m_pReciveDataMutex);        // CriticalSect
							disp_image(tmpImage,showWindowHID);
							m_CurrentFrame=tmpImage;
							m_bHasFrame = true;

							Sleep(m_TimeInterval);
							Sleep(300);
							while(m_SingleFrame)
							{
								if (m_isExit)
								{
									break;
								}
								Sleep(10);
							}
						}
					}
				}
			}while (bRet);		
		}	
		//return 0; //loop once
	}
	return 0;
}


inline bool CMRecvFile::m_PreProcess(CMData *data)
{
	data->Center_x = 0;
	data->Center_y = 0;
	data->r_real = 0;
	return true;
}

void CMRecvFile::Stop()
{
	m_isExit=true;
	//WaitForSingleObject(m_hThread,INFINITE);

	m_hThread=NULL;
}