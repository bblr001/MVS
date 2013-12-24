// CenterAlgorithm.h : CCenterAlgorithm 的声明

#pragma once
#include "resource.h"       // 主符号
#include <vector>


#include "CenterCOM_i.h"



//#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
//#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 //_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs //文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
//#endif
using namespace std;
using namespace ATL;


// CCenterAlgorithm

class ATL_NO_VTABLE CCenterAlgorithm :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCenterAlgorithm, &CLSID_CenterAlgorithm>,
	public IDispatchImpl<ICenterAlgorithm, &IID_ICenterAlgorithm, &LIBID_CenterCOMLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CCenterAlgorithm()
	{
		m_vParameters.reserve(4);
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CENTERALGORITHM)


BEGIN_COM_MAP(CCenterAlgorithm)
	COM_INTERFACE_ENTRY(ICenterAlgorithm)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
		m_vParameters.clear();
	}

	HRESULT STDMETHODCALLTYPE GetAlgorithmName(OLECHAR* algorithmName);
	HRESULT STDMETHODCALLTYPE SetParameter(short* paramIndex, CParameter* pParameter);
	HRESULT STDMETHODCALLTYPE ProcessImageData(CImageData* pImageData, short* parameterIndex, CResult* retResult);
	HRESULT STDMETHODCALLTYPE TrainPrameter(CImageData* pImageData);

private:
	std::vector<CParameter> m_vParameters;
};

OBJECT_ENTRY_AUTO(__uuidof(CenterAlgorithm), CCenterAlgorithm)
