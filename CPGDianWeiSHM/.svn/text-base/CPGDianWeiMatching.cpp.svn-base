// CPGDianWeiSHM.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"



#include "CPGDianWeiMatching.h"
#include "..\Inc\MData.h"
#include <io.h>
#include <tchar.h>

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
	ShowObject=false;
	//m_ProcessName ="QinanHuanTest";
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
	if(parm=="Regional_Out")
		m_Parameters.Regional_Out = atoi(value.c_str());

	if(parm=="Minscore")
		m_Parameters.Minscore = (float)atoi(value.c_str())/10;

	if(parm=="Greediness")
		m_Parameters.Greediness = (float)atoi(value.c_str())/10;


	if(!_stricmp(parm.c_str(),"MODEL_REGIST_LOAD"))
	{
		m_Parameters.modelName = value+".shm";
		if (!_access(m_Parameters.modelName.c_str(),0))
			read_shape_model(m_Parameters.modelName.c_str(),&m_Parameters.ModelID);
		else
		{

		//#ifdef _ENGLISH

		//			wstring msg = _T("Model File Not find. Please  the right file");
		//			MessageBox(NULL,msg.c_str(),_T("ReadFile Error"),MB_OK);
		//			m_Parameters.ModelID=-1;
		//#else

		//			wstring msg = _T("请选择正确的模板文件");
		//			MessageBox(NULL,msg.c_str(),_T("读取文件错误"),MB_OK);
		//			m_Parameters.ModelID=-1;
		//#endif

		m_Parameters.ModelID=-1;

		}
	}
}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	
	try
	{
		Hobject  ModelCircle,ModelDomain;

		HTuple   OrientationPhi;
		if(m_Parameters.ModelID==-1)
		{
			pData->m_isFail =true;
			testItem->m_bFailSubTest = true;
			
		//#ifdef _ENGLISH
		//	set_color(pData->m_ShowHWindow,"red");
		//	HTuple msg  = HTuple("read model file error");
		//	set_tposition( pData->m_ShowHWindow, 55, 200);				
		//	write_string(pData->m_ShowHWindow,msg);
		//#else
		//	set_color(pData->m_ShowHWindow,"red");
		//	HTuple msg  = HTuple("读取模板文件错误");
		//	set_tposition( pData->m_ShowHWindow, 55, 200);				
		//	write_string(pData->m_ShowHWindow,msg);
		//#endif

			set_color(pData->m_ShowHWindow,"red");
			set_tposition( pData->m_ShowHWindow,160, 0);

#ifdef _ENGLISH
			write_string(pData->m_ShowHWindow,"CPGDianWeiMatching Model File Reading Error");
#else
			write_string(pData->m_ShowHWindow,"CPGDianWeiMatching模板文件读取错误");
#endif


		}


		gen_circle(&ModelCircle, pData->m_center_y, pData->m_center_x, pData->r_real+m_Parameters.Regional_Out);
		change_domain(pData->m_Image, ModelCircle, &ModelDomain);

		if (ShowObject&&pData->m_isDebug)
		{
			set_color(pData->m_ShowHWindow,"yellow");
			disp_obj(ModelCircle,pData->m_ShowHWindow);

		}

		HTuple RowModelFind,ColumnModelFind,Score;

		find_shape_model(ModelDomain, m_Parameters.ModelID, HTuple(0).Rad(), HTuple(360).Rad(), 
			m_Parameters.Minscore, 1, 0.1, "least_squares", 0, m_Parameters.Greediness, &RowModelFind, &ColumnModelFind, &OrientationPhi, 
			&Score);


		Hlong length;
		tuple_length(OrientationPhi,&length);
		if(0==length)
		{
			pData->m_isFail =true;
			testItem->m_bFailSubTest = true;
			
#ifdef _ENGLISH
			set_color(pData->m_ShowHWindow,"red");
			HTuple msg  = HTuple("Matching Fail");
			set_tposition( pData->m_ShowHWindow, 55, 200);				
			write_string(pData->m_ShowHWindow,msg);
#else
			set_color(pData->m_ShowHWindow,"red");
			HTuple msg  = HTuple("匹配失败");
			set_tposition( pData->m_ShowHWindow, 55, 200);				
			write_string(pData->m_ShowHWindow,msg);
#endif
			return;

		}

		pData->m_orientationPhi =OrientationPhi[0].D();
		pData->m_center_x2=pData->m_center_x;
		pData->m_center_y2=pData->m_center_y;

	  
	  
	}
	catch (HException &except) 
	{
		pData->m_isFail = true;
		pData->m_orientationPhi=0;
		testItem->m_bFailSubTest = true;
		if (pData->m_isDebug)
		{
			set_tposition( pData->m_ShowHWindow, 55, 230);	

#ifdef _ENGLISH
			write_string(pData->m_ShowHWindow,"CPGDianWeiMatching parameter values error,please re-adjust");
#else
			write_string(pData->m_ShowHWindow,"CPGDianWeiMatching程序参数值出错,请重新调节参数");
#endif

		}
		
	}
}
