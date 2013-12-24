#pragma once
#include "stdafx.h"

#include "workunit.h"
#include "ReportDisplayUI.h"

CWorkUnit::CWorkUnit()
{
	InitializeCriticalSection(&m_NewImageMutex);
	InitializeCriticalSection(&m_ReportDataMutex);
	m_fromCamera=false;
}

CWorkUnit::~CWorkUnit()
{
	this->Close();
}

void CWorkUnit::Init(bool fromCamera)
{
	m_fromCamera =fromCamera;
	m_ReportDataList = m_DisplayUI.GetDataList();
	m_ReciveDataList = m_Process.GetDataList();
	if (m_fromCamera)
	{
		this->m_Camera.Init(this);
	}
	this->m_RecvFile.Init(this);
	this->m_Process.Init(this);
}

void CWorkUnit::InitUI(Hlong wWindowID,int Width,int Height)
{
	this->m_DisplayUI.Init(this,wWindowID,Width,Height);
}

void CWorkUnit::Open(int IndexCamera)
{
	
	if (m_fromCamera)
	{
		this->m_Camera.Open(IndexCamera);
	}
}
void CWorkUnit::Start()
{

// 	this->m_DisplayUI.Start();
// 	this->m_Process.Start();

	if (m_fromCamera)
		this->m_Camera.Start();
	this->m_DisplayUI.InitWindow();

}


void CWorkUnit::Stop()
{

	if (m_fromCamera)
		this->m_Camera.Stop();
	else
		this->m_RecvFile.Stop();
	this->m_Process.Stop();
	this->m_DisplayUI.Stop();
}



void CWorkUnit::Close()
{
	this->Stop();
	//m_Camera.Close();
	
}

void CWorkUnit::RunThread()
{

	//#pragma omp parallel sections
	//{
		//#pragma omp section
			this->m_DisplayUI.Run();
		//#pragma omp section
			this->m_Process.Run();
		//#pragma omp section
		if (m_fromCamera)
			this->m_Camera.Run();
		else
			this->m_RecvFile.Run();
	//}


}

