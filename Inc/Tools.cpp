#pragma once
#include "stdafx.h"
#include "Tools.h"
#include <string>
#include <vector>

#include "Tlhelp32.h"
#include <dbghelp.h>
#include <atlconv.h>

using namespace std;

string ws2s(wstring& inputws)
{ 
	USES_CONVERSION;
	return W2CA(inputws.c_str()); 
}

std::wstring s2ws(const string& s)
{
	USES_CONVERSION;
	return A2CW(s.c_str());
}

BOOL CALLBACK EnumThreadWndProc(HWND    hwnd,      LPARAM    lParam)
{   
	if (MI_SHOW==lParam)//1
	{
		SetWindowPos(hwnd,HWND_TOP,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW|SWP_DRAWFRAME);  
		SendMessage(hwnd,SW_RESTORE,NULL,NULL);
	}
	if (MI_HIDE==lParam)//0
	{
		SetWindowPos(hwnd,HWND_TOPMOST,0,0,0,0,SWP_HIDEWINDOW);   
	}
	if (MI_CLOSE==lParam)//2
	{
		SendMessage(hwnd,WM_CLOSE,NULL,NULL);
		::CloseWindow(hwnd);
	}
	if (WM_MI_EXIT_MESSAGE==lParam)//2
	{
		SendMessage(hwnd,WM_CLOSE,NULL,NULL);
		::CloseWindow(hwnd);
	}
	return TRUE;   
}  

DWORD   GetProcessIdFromName(LPCWSTR name)
{   
	PROCESSENTRY32   pe;
	DWORD   id   =   0;   
	HANDLE   hSnapshot   =   CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);   
	pe.dwSize = sizeof(PROCESSENTRY32);   
	if(!Process32First(hSnapshot,&pe))
	{
		::CloseHandle(hSnapshot);
		hSnapshot = NULL;
		return  0;
	}
	while(1)   
	{   
		pe.dwSize   =   sizeof(PROCESSENTRY32);   
		if(Process32Next(hSnapshot,&pe)==FALSE)   
			break;  
		if(_wcsicmp(pe.szExeFile,name) == 0)   
		{   
			id   =   pe.th32ProcessID;   
			break;   
		}
	};   
	CloseHandle(hSnapshot); 
	hSnapshot = NULL;
	return   id;   
}   

BOOL CheckProcess(LPCWSTR lpName, CString& strErrMsg)
{
	BOOL bRet = TRUE;
	DWORD   dwProcessId = 0;   
	LPCWSTR lppName = _tcsrchr(lpName, _T('\\'));
	__try
	{
		if (lppName == NULL)
		{
			lppName = lpName;
		}
		else
		{
			lppName++;
		}
		//   得到该窗口的进程ID 
		dwProcessId = GetProcessIdFromName(lppName);
		while (dwProcessId)
		{
			//从进程ID打开进程句柄
			HANDLE   handle=OpenProcess(PROCESS_TERMINATE,FALSE,dwProcessId);
			//强制终止进程
			TerminateProcess(handle,PROCESS_TERMINATE);   
			CloseHandle(handle); handle = NULL;
			dwProcessId = GetProcessIdFromName(lppName);
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		strErrMsg.Format(_T("Load %s fail. Please ensure the file exists in current directory"), lpName);
		bRet = FALSE;
	}
	return bRet;
}