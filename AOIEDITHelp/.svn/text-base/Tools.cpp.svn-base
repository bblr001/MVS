#pragma once
#include "stdafx.h"
#include "Tools.h"
#include <string>

#include "Tlhelp32.h"
#include <dbghelp.h>

//#pragma comment( lib, "dbghelp.lib" )


using namespace std;


std::string WChar2Ansi(LPCWSTR pwszSrc)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);

	if (nLen<= 0) return std::string("");

	char* pszDst = new char[nLen];
	if (NULL == pszDst) return std::string("");

	WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
	pszDst[nLen -1] = 0;

	std::string strTemp(pszDst);
	delete [] pszDst;

	return strTemp;
}


string ws2s(wstring& inputws)
{ 
	return WChar2Ansi(inputws.c_str()); 
}



//Converting a Ansi string to WChar string

std::wstring Ansi2WChar(LPCSTR pszSrc, int nLen)

{
	int nSize = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pszSrc, nLen, 0, 0);
	if(nSize <= 0) return NULL;

	WCHAR *pwszDst = new WCHAR[nSize+1];
	if( NULL == pwszDst) return NULL;

	MultiByteToWideChar(CP_ACP, 0,(LPCSTR)pszSrc, nLen, pwszDst, nSize);
	pwszDst[nSize] = 0;

	if( pwszDst[0] == 0xFEFF)                    // skip Oxfeff
		for(int i = 0; i < nSize; i ++) 
			pwszDst[i] = pwszDst[i+1]; 

	wstring wcharString(pwszDst);
	delete pwszDst;

	return wcharString;
}


std::wstring s2ws(const string& s)
{
	return Ansi2WChar(s.c_str(),s.size());
}



BOOL CALLBACK EnumThreadWndProc(HWND    hwnd,      LPARAM    lParam)
{   

	//ShowWindow(hwnd,SW_SHOW);

	if (MI_SHOW==lParam)//1
	{
		//SetWindowPos(hwnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);   
		SetWindowPos(hwnd,HWND_TOP,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW|SWP_DRAWFRAME);   
		//SetWindowPos(hwnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);   
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
	
	return    TRUE;   
}  
void ToolsButtonStarsUpdate(CMFCToolBar* tb,int index,UINT iButtonStyle)
{
	UINT iButtonID;
	UINT oldButtonStyle; 
	int  iButtonImage;
	tb->GetButtonInfo(index, iButtonID, oldButtonStyle,iButtonImage);
	//iButtonStyle = TBBS_DISABLED; //无效
	tb->SetButtonInfo(index, iButtonID, iButtonStyle,iButtonImage);
}




DWORD   GetProcessIdFromName(LPCWSTR name)
{   
	PROCESSENTRY32   pe;
	DWORD   id   =   0;   
	HANDLE   hSnapshot   =   CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);   
	pe.dwSize   =   sizeof(PROCESSENTRY32);   
	if(   !Process32First(hSnapshot,&pe)   )   
		return   0;   
	while(1)   
	{   
		pe.dwSize   =   sizeof(PROCESSENTRY32);   
		if(   Process32Next(hSnapshot,&pe)==FALSE   )   
			break;  
		if(_wcsicmp(pe.szExeFile,name)   ==   0)   
		{   
			id   =   pe.th32ProcessID;   
			break;   
		}
	};   
	CloseHandle(hSnapshot);   
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
			CloseHandle(handle);
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