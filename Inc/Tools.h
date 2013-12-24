#pragma once
#include <string>

#define WM_MI_ENTER_MESSAGE (WM_USER+1001)
#define WM_MI_PAUSE_MESSAGE (WM_USER+1002)
#define WM_MI_RUN_MESSAGE (WM_USER+1003)
#define WM_MI_STOP_MESSAGE (WM_USER+1004)
#define WM_MI_EXIT_MESSAGE (WM_USER+1005)
#define WM_MI_TLSUPDATE_MESSAGE (WM_USER + 1006)

#define WM_MI_ALARM_MESSAGE (WM_USER+1007)

#define WM_MI_QUERY_MESSAGE (WM_USER+1008)

#define WM_MI_RECOUNT_MESSAGE (WM_USER+1009)

using namespace std;
enum eMI_ACTION {MI_HIDE=0,MI_SHOW,MI_CLOSE}; 

string ws2s(wstring& inputws);

std::wstring s2ws(const string& s);

BOOL CALLBACK EnumThreadWndProc(HWND    hwnd,      LPARAM    lParam);

DWORD   GetProcessIdFromName(LPCWSTR name);

BOOL	CheckProcess(LPCWSTR lpName, CString& strErrMsg);