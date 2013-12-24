#include "stdafx.h" 
#include "IMActiveObj.h" 
#include <process.h>    /* _beginthread, _endthread */ 
 
#define WINAPI __stdcall 

IActiveObj::IActiveObj() 
{ 
        m_ThreadID = 0; 
        m_Handle = NULL; 
} 
IActiveObj::~IActiveObj() 
{ 
	
} 
bool IActiveObj::Run() 
{ 
	m_Handle   =   (HANDLE)_beginthreadex(NULL, 0, (PBEGINTHREADEX_THREADFUNC) IActiveObj::WorkThread, 
		(LPVOID)this,0,(PBEGINTHREADEX_THREADID) &m_ThreadID   );    
	return true; 
} 

DWORD WINAPI IActiveObj::WorkThread(IActiveObj *lpthis) 
{ 
	DWORD uRet=lpthis->Main(); 
	return uRet; 
}