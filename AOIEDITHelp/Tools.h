#ifndef __TOOLS_HEADER__
#define __TOOLS_HEADER__
#pragma once

#include <string>

#define WM_MI_ENTER_MESSAGE (WM_USER+1001)
#define WM_MI_PAUSE_MESSAGE (WM_USER+1002)
#define WM_MI_RUN_MESSAGE (WM_USER+1003)
#define WM_MI_STOP_MESSAGE (WM_USER+1004)
#define WM_MI_EXIT_MESSAGE (WM_USER+1005)

using namespace std;
enum eMI_ACTION {MI_HIDE=0,MI_SHOW,MI_CLOSE}; 

std::string WChar2Ansi(LPCWSTR pwszSrc);

string ws2s(wstring& inputws);



//Converting a Ansi string to WChar string

std::wstring Ansi2WChar(LPCSTR pszSrc, int nLen);


std::wstring s2ws(const string& s);



BOOL CALLBACK EnumThreadWndProc(HWND    hwnd,      LPARAM    lParam);


void ToolsButtonStarsUpdate(CMFCToolBar* tb,int index,UINT iButtonStyle);


//
DWORD   GetProcessIdFromName(LPCWSTR name);
BOOL	CheckProcess(LPCWSTR lpName, CString& strErrMsg);
#endif