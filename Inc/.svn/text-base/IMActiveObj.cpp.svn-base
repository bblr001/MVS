#pragma once

#include "stdafx.h"
#include "IMActiveObj.h"

IMActiveObj::IMActiveObj(void)
{
	m_hThread=NULL;
}

IMActiveObj::~IMActiveObj(void)
{
	//_endthread automatically closes the thread handle (whereas _endthreadex does not).
	::CloseHandle(m_hThread);
	m_hThread = nullptr;
}

HANDLE IMActiveObj::Run()
{
	m_hThread = (HANDLE)_beginthreadex(
		NULL,
		0,
		(unsigned (__stdcall *)(void*))&WorkThread,
		this,					
		0,					
		&m_iThreadId);			
	return m_hThread;
}

UINT  IMActiveObj::WorkThread( IMActiveObj* lpthis )
{
	unsigned int  uRet=lpthis->Main();
	return uRet;
}