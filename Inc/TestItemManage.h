// DllTestMain.cpp : 定义控制台应用程序的入口点。
//
#pragma once

//#include "stdafx.h"
#include "stdio.h"
#include <iostream>
#include <vector>
#include <list>
#include <assert.h>
#include <algorithm>
#include <set>
#include "TlsFileParser.h"
#include "MData.h"

using namespace std;

class CTestItemManage
{
public:
	CTestItemManage()
	{
	};
	~CTestItemManage()
	{
		CleanupModuleHandle();
	}
	std::list<STDoProcess>* GetDoProcessList() 
	{
		return &m_pDoProcessList;
	}

	bool SetTestItemList(std::vector<CTlsData>* pProcessItemList);
	void UpdateTestItemParameter(int order, string paramName = "");
	void UpdateTestItemParameter();
	int AutoConfig();
private:
	std::vector<CTlsData>* m_pTestItemList;
	std::list<STDoProcess> m_pDoProcessList;
	std::set<HMODULE> m_setModuleHandles;

private:
	void CleanupModuleHandle()
	{
		std::for_each(m_setModuleHandles.begin(), m_setModuleHandles.end(), [](HMODULE hModule)
		{
			if(hModule != NULL)
			{
				::FreeLibrary(hModule);
				hModule = NULL;
			}
		});
		m_setModuleHandles.clear();
	}
	std::vector<CString> GetCurrentCheckedDllName(std::vector<int>& retIndex);
	void LoadNewDlls(std::vector<CString>& checkedDllName, std::vector<int>& TestItemListIndex);
	void UpdateSetParameterList(std::vector<int>& TestItemListIndex);

	void InsertProcessDlls(CString& dllName,int index);
};
