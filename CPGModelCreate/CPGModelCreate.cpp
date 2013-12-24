// CPGModelCreate.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <tchar.h>
#include <io.h>
#include "CPGModelCreate.h"
#include "..\Inc\MData.h"

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
	if(parm=="Regional_Internal")
		m_Parameters.Regional_Internal = atoi(value.c_str());

	if(parm=="Regional_Out")
		m_Parameters.Regional_Out = atoi(value.c_str());


	if(!_stricmp(parm.c_str(),"MODEL_REGIST_CREATE"))
	{
		m_Parameters.modelName = value+".shm";
	}

}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	

	try

	{
	  Hobject  MianXinCircle1, MianXinCircle2, MianXinCircle;
	  Hobject  MianXinDomain;


	  // Local control variables 
	  HTuple  Width, Height, CenterRow, CenterColumn;
	  HTuple  CenterRadius, ModelID;
  
	  gen_circle(&MianXinCircle1, pData->m_center_y, pData->m_center_x, pData->r_real+m_Parameters.Regional_Out);
	  gen_circle(&MianXinCircle2, pData->m_center_y, pData->m_center_x, pData->r_real+m_Parameters.Regional_Internal);

	  set_color(pData->m_ShowHWindow,"green");
	  disp_obj(MianXinCircle2,pData->m_ShowHWindow);

	  set_color(pData->m_ShowHWindow,"blue");
	  disp_obj(MianXinCircle1,pData->m_ShowHWindow);

	  difference(MianXinCircle1, MianXinCircle2, &MianXinCircle);
	  change_domain(pData->m_Image, MianXinCircle, &MianXinDomain);

	  //*inspect_shape_model (MianXinDomain22, ModelImages1, ModelRegions1, 4, 30)
	  create_shape_model(MianXinDomain, "auto", 0, HTuple(360).Rad(), "auto", "auto", 
		  "use_polarity", "auto", "auto", &ModelID);
	  write_shape_model(ModelID,m_Parameters.modelName.c_str());

	  //if (!_access(m_Parameters.modelName.c_str(),0))
	  //{
		 // wstring msg = _T("Set Model already Exit.OverWrite or Not?");

		 // if (MessageBox(NULL,msg.c_str(),_T("ReadFile Error"),MB_OK||MB_CANCELTRYCONTINUE)==IDOK)
		 // {
			//  write_shape_model(ModelID,m_Parameters.modelName.c_str());
		 // }

	  //}
	  //else
		 // write_shape_model(ModelID,m_Parameters.modelName.c_str());
	}
	catch (HException &except) 
	{
		pData->m_isFail = true;
		pData->m_orientationPhi=0;
		testItem->m_bFailSubTest = true;
		//if (pData->m_isDebug)
		{
			set_color(pData->m_ShowHWindow,"green");
			set_tposition( pData->m_ShowHWindow,25, 200);
			write_string(pData->m_ShowHWindow,"CPGModelCreate程序参数值出错,请重新调节参数");
		}

	}
}