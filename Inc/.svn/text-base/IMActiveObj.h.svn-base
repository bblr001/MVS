#pragma once

///<summary>
///通用主动类接口
///</summary>
#include <stdio.h>
#include <iostream>
#include "process.h"

class IMActiveObj
{

public:
	IMActiveObj(void);
	virtual ~IMActiveObj(void);

	HANDLE Run();
	virtual void Pause() = 0
	{
		::SuspendThread(m_hThread);
	}
	virtual void Resume() = 0
	{
		::ResumeThread(m_hThread);
	}

	//TODO: Active对象的暂停、停止操作	

protected:
	static UINT WorkThread(IMActiveObj* lpthis);
	virtual UINT Main()=0;

public:
	HANDLE   m_hThread;
private:
	unsigned int m_iThreadId;
};
