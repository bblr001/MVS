#pragma once
#include "stdafx.h"
#include "ProcessComunicate.h"
#include "..\..\inc\tools.h"
#include "..\MainFrm.h"
#include <cstdlib>


//////////////////
CMCmd::CMCmd():m_pUiCmdProxy(nullptr)
{
	m_pUiCmdProxy = new IPC_CMD_BUS_DEPRECATED(_T("FTS2007MIDataCFG")); //读需要处理的文件和程式参数等
	m_isExit = false;
	Run();
}

CMCmd::~CMCmd()
{	
	m_isExit=true;	
	if (m_pUiCmdProxy!=NULL)
	{
		delete m_pUiCmdProxy;
		m_pUiCmdProxy = nullptr;
	}
}

void CMCmd::Close()
{
	m_isExit=true;
	WaitForSingleObject(m_Handle,INFINITE);
}

DWORD CMCmd::Main()
{
	char cmdData[CMDDATASIZE];
	char* buff = new char[MAX_PATH+1];
	m_isExit=false;
	CMainFrame* pMainFrm = (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
	while (!m_isExit)
	{
		if(!m_pUiCmdProxy->Read(cmdData,CMDDATASIZE))
		{
			Sleep(1);
			continue;
		}
		TCppML smlData;
		bool isOk=smlData.Parse(cmdData);
		if(!isOk)
		{
			continue;
		}
        strcpy_s(buff,MAX_PATH,smlData["processID"].GetString());
		string processID(buff);
		strcpy_s(buff,MAX_PATH,smlData["tls"].GetString());
		string tlsFileName(buff);
		strcpy_s(buff,MAX_PATH,smlData["image"].GetString());
		string imageFileName(buff);
		pMainFrm->ReciveImage(processID,tlsFileName,imageFileName);
		Sleep(10);
	}
	delete[] buff;
	return 0;
}

