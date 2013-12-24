// DllTestMain.cpp : 定义控制台应用程序的入口点。
//
#pragma once
#include "stdafx.h"
#include "stdio.h"
#include "iostream"
#include "TestItemManage.h"
#include "Mergemod.h"
#include "MConfigCenter.h"
#include <io.h>

std::vector<CString> CTestItemManage::GetCurrentCheckedDllName(std::vector<int>& retIndex)
{
	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0; //删除文件名，只获得路径

	std::vector<CString> retNames;
	int index = 0;
	for (auto testIt = m_pTestItemList->begin();testIt != m_pTestItemList->end(); testIt++)
	{
		STLSDATA_SUBTEST* ptr = (*testIt).GetDataSubtest();
		if (ptr != nullptr &&(0 == _stricmp(ptr->RunTest.c_str(),"Yes")))
		{
			CString exename(ptr->exeName.c_str());
			CString dllName;
			dllName.Format(_T("%s\\%s.dll"),szFilePath,exename);
			retNames.push_back(dllName);
			retIndex.push_back(index);
		}
		index++;
	}
	return retNames;
}

void CTestItemManage::InsertProcessDlls(CString& dllName,int index)
{
	HMODULE hInst = NULL;
	hInst = ::LoadLibrary(dllName);
	if(hInst != NULL)
	{
		m_setModuleHandles.insert(hInst);

		STDoProcess stSTDoPorceess;
		stSTDoPorceess.process = (DllDoProcess)GetProcAddress(hInst, "SLACDllDoProcess");
		stSTDoPorceess.order = index;
		if (NULL != stSTDoPorceess.process)
		{
			stSTDoPorceess.m_hDllHandle = hInst;
			stSTDoPorceess.m_dllName = dllName;
			m_pDoProcessList.push_back(stSTDoPorceess);
		}
	}
	else
	{
		CString msg = _T("Error. Load Dll ") + dllName + _T("Error");
		AfxMessageBox(msg);
	}
}

void CTestItemManage::LoadNewDlls(std::vector<CString>& checkedDllName, std::vector<int>& TestItemListIndex)
{
	int index = 0;
	m_pDoProcessList.clear();
	std::for_each(checkedDllName.begin(), checkedDllName.end(), [&](CString& dllName)
	{
		int til_index = TestItemListIndex[index]; // test item list index;
		auto subtestPtr = (*m_pTestItemList)[til_index].GetDataSubtest();

		InsertProcessDlls(dllName,subtestPtr->order);
		index++;
	});
}

void CTestItemManage::UpdateSetParameterList(std::vector<int>& TestItemListIndex)
{
	int index = 0;
	for(auto it = m_pDoProcessList.begin(); it != m_pDoProcessList.end(); ++it)
	{
		int til_index = TestItemListIndex[index]; // test item lsit index;
		auto subtestPtr = (*m_pTestItemList)[til_index].GetDataSubtest();


		DLLSetParameter pfDllFuncSetParameter  = (DLLSetParameter)GetProcAddress((*it).m_hDllHandle, "SetParameter");
		if (NULL != pfDllFuncSetParameter)
		{
			auto parameter = subtestPtr->m_vParameters;
			for (auto parameterIt = parameter.begin();parameterIt!=parameter.end();parameterIt++)
			{
				string parameterName((*parameterIt).parameterName);
				string value((*parameterIt).settingValue);
				
				(*pfDllFuncSetParameter)(subtestPtr->order,parameterName,value);
			}
			if ((subtestPtr->ShowObject)&&(CMConfigCenter::GetSingletonConfigCenter()->GetDebugModeFlag()))
			{
				(*pfDllFuncSetParameter)((*it).order,"SHOWOBJECT","YES");
			}
			else
			{
				(*pfDllFuncSetParameter)((*it).order,"SHOWOBJECT","NO");
			}
			(*it).parameter = pfDllFuncSetParameter;
		}
			index++;
	}
}

bool CTestItemManage::SetTestItemList(std::vector<CTlsData>* pProcessItemList)
{
	m_pTestItemList = pProcessItemList ;
	std::vector<int> retIndex;
	std::vector<CString> checkedItemName = GetCurrentCheckedDllName(retIndex);

	LoadNewDlls(checkedItemName, retIndex);
	UpdateSetParameterList(retIndex);

	return true;
}

void CTestItemManage::UpdateTestItemParameter(int order, string paramName)
{
	auto pTestList = CMConfigCenter::GetSingletonConfigCenter()->GetTestItemList();
	if(pTestList == nullptr)
		return;

	auto itSubtest = std::find_if(pTestList->begin(), pTestList->end(),[&](CTlsData& data)->bool
	{
		STLSDATA_SUBTEST* pSubtestInfo = data.GetDataSubtest();
		return order == pSubtestInfo->order;
	});

	std::list<STDoProcess>::iterator itProcList;
	if(itSubtest != pTestList->end())
	{
		itProcList = std::find_if(m_pDoProcessList.begin(), m_pDoProcessList.end(),[&](STDoProcess& processor)->bool
		{
			return processor.order == order;
		});
	}
	if(itProcList != m_pDoProcessList.end())
	{
		auto pSubTest = (*itSubtest).GetDataSubtest();
		if(pSubTest == nullptr) return;

		bool flag = (pSubTest->ShowObject)&&(CMConfigCenter::GetSingletonConfigCenter()->GetDebugModeFlag());
		string str = (flag == true ? "YES" : "NO");
		((*itProcList).parameter)(order, "SHOWOBJECT", str.c_str());
		auto vParam = pSubTest->m_vParameters;
		auto itParam = std::find_if(vParam.begin(), vParam.end(), [&](STLSDATA_PARAMETER& param)->bool
		{
			return param.parameterName == paramName;
		});
		if(itParam != vParam.end())
		{
			((*itProcList).parameter)(order, paramName, (*itParam).settingValue);
		}
	}
}

void CTestItemManage::UpdateTestItemParameter()
{
	auto pTestList = CMConfigCenter::GetSingletonConfigCenter()->GetTestItemList();
	if(pTestList == nullptr)
		return;

	for (auto it = m_pDoProcessList.begin();it!=m_pDoProcessList.end();it++)
	{
		int order = it->order;
		auto itTestList = std::find_if(pTestList->begin(),pTestList->end(),[&](CTlsData& data)->bool
		{
			auto pSubtest = data.GetDataSubtest();
			return (pSubtest != nullptr) && (pSubtest->order == order);
		});
		if(itTestList != pTestList->end())
		{
			auto pSubtest = (*itTestList).GetDataSubtest();
			auto vParam = pSubtest->m_vParameters;
			std::for_each(vParam.begin(), vParam.end(), [&](STLSDATA_PARAMETER& param)
			{
				((*it).parameter)(order, param.parameterName, param.settingValue);
			});
			bool flag = (pSubtest->ShowObject)&&(CMConfigCenter::GetSingletonConfigCenter()->GetDebugModeFlag());
			string str = (flag == true ? "YES" : "NO");
			((*it).parameter)(order, "SHOWOBJECT", str);
		}
	}
}