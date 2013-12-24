// CPGModelCreate.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <tchar.h>
#include <io.h>
#include "CPGShapeCreation.h"
#include "..\Inc\MData.h"

using namespace std;

std::wstring s2ws(const std::string& s)
{
	setlocale(LC_ALL, "chs"); 
	const char* _Source = s.c_str();
	size_t _Dsize = s.size() + 1;
	wchar_t *_Dest = new wchar_t[_Dsize];
	wmemset(_Dest, 0, _Dsize);
	mbstowcs(_Dest,_Source,_Dsize);
	std::wstring result = _Dest;
	delete []_Dest;
	setlocale(LC_ALL, "C");
	return result;
}



#ifndef   DLLEXPT
#define DLLEXPT __declspec (dllexport )
#endif

// exception handler
void MyHalconExceptionHandler(const Halcon::HException& except)
{
	throw except;	
}

CDoProcess::CDoProcess()
{
	//m_ProcessName ="QinanHuanTest";
	ShowObject=false;
	HException::InstallHHandler(&MyHalconExceptionHandler);
}


void CDoProcess::SetParmeter(string parm,string value)
{
	if(parm=="SHOWOBJECT")
		if (value=="YES")
		{
			ShowObject = true;
		}
		else
		{
			ShowObject = false;
		}
//=============================================================================================
		if(!_stricmp(parm.c_str(),"TEST_REGIST"))
		{
			string regname = value+".reg";
			if (!_access(regname.c_str(),0))
				read_region(&m_Parameters.Test_Regist,value.c_str());
			else
			{
				Hobject  EmptyRegion;
				gen_empty_region(&EmptyRegion);
				m_Parameters.Test_Regist=EmptyRegion;

			}

		}

//=============================================================================================
	if(!_stricmp(parm.c_str(),"MODEL_REGIST_CREATE"))
	{
		m_Parameters.modelName = value+".shm";
	}

}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	

	try

	{
		Hobject LoadRegion;
		HTuple Num;

		Hobject Test_Regist;
		Test_Regist = m_Parameters.Test_Regist;

		select_shape(Test_Regist, &LoadRegion, "area", "and", 1, 9999999);
		count_obj(LoadRegion, &Num);
		if(Num==0)
		{
			pData->m_isFail =true;
			testItem->m_bFailSubTest = true;

			set_color(pData->m_ShowHWindow,"red");
			set_tposition( pData->m_ShowHWindow,200, 0);

#ifdef _ENGLISH
			write_string(pData->m_ShowHWindow,"CPGShapeCreation region file reading error.Redraw the model region or load the existing one");
#else
			write_string(pData->m_ShowHWindow,"CPGShapeCreation区域文件读取错误.重画或者载入已有模板区域");
#endif
			return;
		}

	
//=============================================================================================		
	  Hobject MianXinDomain;
	  HTuple  ModelID;

	  Hobject image = pData->m_Image;

	  change_domain(image, Test_Regist, &MianXinDomain);

	  //*inspect_shape_model (MianXinDomain22, ModelImages1, ModelRegions1, 4, 30)
	  create_shape_model(MianXinDomain, "auto", 0, HTuple(360).Rad(), "auto", "auto", 
		  "use_polarity", "auto", "auto", &ModelID);

	  write_shape_model(ModelID,m_Parameters.modelName.c_str());

	  
	}
	catch (HException &except) 
	{
		if (pData->m_isDebug)
		{
			set_color(pData->m_ShowHWindow,"green");
			set_tposition( pData->m_ShowHWindow,25, 145);
			#ifdef _ENGLISH 
						write_string(pData->m_ShowHWindow,"CPGShapeCreation error");
			#else
						write_string(pData->m_ShowHWindow,"轮廓模板创建出错");
			#endif
		}
		pData->m_isFail = true;
		pData->m_orientationPhi=0;
		testItem->m_bFailSubTest = true;

	}
}
